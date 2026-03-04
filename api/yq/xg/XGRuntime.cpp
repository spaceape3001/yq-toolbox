////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGRuntime.hpp"
#include <yq/errors.hpp>
#include <yq/graph/GDocument.hpp>
#include <yq/graph/GEdge.hpp>
#include <yq/graph/GNode.hpp>
#include <yq/graph/GPort.hpp>
#include <yq/util/AutoReset.hpp>
#include <yq/util/Safety.hpp>
#include <yq/xg/logging.hpp>
#include <yq/xg/XGContext.hpp>
#include <yq/xg/XGLogic.hpp>

#include <yq/xg/XGElement.hxx>

namespace yq {
    bool    is_continue(const xg_result_t& r)
    {
        return std::get_if<std::monostate>(&r) || std::get_if<continue_k>(&r);
    }
    
    bool    is_done(const xg_result_t&r)
    {
        return static_cast<bool>(std::get_if<done_k>(&r));
    }
    
    bool    is_error(const xg_result_t&r)
    {
        return std::get_if<error_k>(&r) || std::get_if<std::error_code>(&r);
    }

    bool    is_limit(const xg_result_t& r)
    {
        return static_cast<bool>(std::get_if<limit_k>(&r));
    }

    bool    is_wait(const xg_result_t& r)
    {
        return static_cast<bool>(std::get_if<wait_k>(&r));
    }
    
    int32_t priority_of(const GEdge& ge)
    {
        //  TODO
        return 0;
    }

//////////////////

    // seems zero point in dedicated C++ source
    XGContext::XGContext() = default;
    XGContext::~XGContext() = default;

//////////////////

    XGRuntime::State::State(){}
    XGRuntime::State::State(const xg_next_t& nxt) : next(nxt), iterate(false)
    {
    }
    
    XGRuntime::State::State(xg_next_span_t spn) : span(spn), iterate(true)
    {
        if(!spn.empty())
            next    = spn[0];
    }

//////////////////

    XGRuntime::XGRuntime()
    {
    }
    
    XGRuntime::~XGRuntime()
    {
        kill();
    }
    
    XGRuntime::XGRuntime(GGraph g)
    {
        std::error_code ec  = initialize(g);
        if(ec != std::error_code())
            xgError << "Cannot initialize graph: " << ec.message();
    }
    
    void    XGRuntime::_push(State st, Tristate interrupt)
    {
        switch(interrupt){
        case Tristate::Yes:
            st.interrupt    = true;
            break;
        case Tristate::No:
            st.interrupt    = false;
            break;
        case Tristate::Inherit:
        default:
            if(m_state.empty()){
                st.interrupt    = false;
            } else {
                st.interrupt    = m_state.top().interrupt;
            }
            break;
        }
        if(st.interrupt && !m_state.empty())
            st.priority = m_state.top().priority;
        m_state << st;
    }
    
    std::error_code             XGRuntime::add(GGraph)
    {
        return errors::todo();
    }
    
    std::error_code             XGRuntime::add(int, GGraph)
    {
        return errors::todo();
    }
    
    std::error_code             XGRuntime::add(const std::string&, GGraph)
    {
        return errors::todo();
    }

    void                        XGRuntime::always(push_k)
    {
        always(PUSH, m_primary);
    }

    void                        XGRuntime::always(push_k, uint64_t docId)
    {
        auto x = m_files.find(docId);
        if(x == m_files.end())
            return;
        if(x->second.always.empty())
            return;
        _push(State(x->second.always), Tristate::YES);
    }

    uint64_x                    XGRuntime::compile(GGraph g)
    {
        if(!g.document())
            return unexpected<"null graph">();
            
        uint64_t    docId   = g.document()->id();
        if(m_files.contains(docId))
            return unexpected<"Already compiled">();
        
        Map<uint64_t,XGElement*>    elems;
        Vector<xg_next_t>           starts, always;
        
        auto safe   = safety([&](){
            for(auto& itr : elems)
                delete itr.second;
        });
        
        for(GNode gn : g.nodes()){
            auto xx  = compile(gn);
            if(!xx)
                return unexpected(xx.error());
            
            XGElement* x    = *xx;
            if(!x)
                return errors::null_pointer();
                
            x -> m_cursor   = { docId, gn.id() };
            
            switch(x -> metaInfo().node_type()){
            case XGNodeType::Always:
                always.push_back({ .cursor = x->m_cursor, .priority=x->m_priority });
                break;
            case XGNodeType::Start:
                always.push_back({ .cursor = x->m_cursor, .priority=x->m_priority });
                break;
            default:
                break;
            }
            
            elems[gn.id()]  = x;
        }
        
        for(GEdge ge : g.edges()){
            GPort       sp  = ge.source(PORT);
            GNode       sn  = ge.source(NODE);
            
            XGElement*  sx  = elems.get(sn.id(), nullptr);
            XGLogic*    sl  = dynamic_cast<XGLogic*>(sx);
            
            if(sn && !sx)
                return unexpected<"Edge has bad source">();
            
            GPort       tp  = ge.target(PORT);
            GNode       tn  = ge.target(NODE);

            XGElement*  tx  = elems.get(tn.id(), nullptr);
            if(tn && !tx)
                return unexpected<"Edge has bad target">();

            xg_next_t   nx{}; 
            nx.priority     = priority_of(ge);
            if(tx){
                nx.cursor   = tx->cursor();
                nx.subpri   = tx->priority();
            }

            if(sp && !sp.key().empty()){
                if(sl && (sp.key() == "?")){
                    sl -> m_logic.push_back(nx);
                } else {
                    return unexpected<"Edge has bad source specifier">();
                }
            }
        }
        
        //  TODO... sort the edges
        
        safe.disarm();

        File& file = m_files[docId];
        file.graph      = g;
        file.elements   = std::move(elems);
        file.starts     = std::move(starts);
        file.always     = std::move(always);

        for(auto& itr : file.elements)
            m_elements[itr.second->cursor()] = itr.second;
        
        
        return docId;
    }

    Expect<XGElement*>          XGRuntime::compile(const GNode&gn)
    {
        const XGElementMeta*    xm  = nullptr;
        std::string_view   type = gn.type();
        
        XGElement::InitAPI  api;
        api.node    = gn;
        
        xm  = XGElementMeta::find(type);
        if(!xm){
            api.node_template   = GNodeTemplate::IO::load(type);
            if(!api.node_template)
                return unexpected<"Cannot resolve node type">();
            xm  = XGElementMeta::find(api.node_template -> meta);
        }
        
        if(!xm)
            return unexpected<"Cannot find XGElement">();
        
        Object* obj = xm -> create();
        if(!obj)
            return unexpected<"Cannot create XGElement">();
        
        XGElement* x    = dynamic_cast<XGElement*>(obj);
        if(!x) [[unlikely]] {
            delete obj;
            return unexpected<"Created object is not an XGElement">();
        }
        
        std::error_code ec  = x->initialize(api);
        if(ec != std::error_code()){
            delete x;
            return unexpected(ec);
        }
    
        return x;
    }

    XGElement*                  XGRuntime::element(const xg_cursor_t&k)
    {
        return m_elements.get(k, nullptr);
    }
    
    const XGElement*            XGRuntime::element(const xg_cursor_t&k) const
    {
        return m_elements.get(k, nullptr);
    }

    size_t          XGRuntime::elements(count_k) const
    {
        return m_elements.size();
    }

    xg_result_t  XGRuntime::execute(const XGRuntimeOptions& opts)
    {
        XGContext ctx;
        return execute(ctx, opts);
    }
    
    xg_result_t  XGRuntime::execute(XGContext& ctx, const XGRuntimeOptions& opts)
    {
        switch(m_mode){
        case Mode::Uninit:
            return create_error<"XGRuntime is not initialized">();
        case Mode::Error:
            return create_error<"XGRuntime is in error state">();
        case Mode::Done:
            return create_error<"XGRuntime is already done">();
        default:
            break;
        }
    
        always(PUSH);
        for(unsigned n=0;n<opts.max_steps;++n){
            xg_result_t r = step(ctx, opts);
            if(is_error(r))
                return r;
            if(is_done(r))
                return r;
            if(is_wait(r))
                return r;
        }
        return LIMIT;
    }

    std::error_code XGRuntime::initialize(GGraph g)
    {
        if(m_primary)
            return create_error<"XGRuntime already initialized">();
        
        auto x  = compile(g);
        if(!x)
            return x.error();
        
        m_primary   = *x;
        m_mode     = Mode::Start;
        return {};
    }
    
    void                        XGRuntime::kill()
    {
        m_results.clear();
        for(auto& itr : m_elements)
            delete itr.second;
        m_elements.clear();
        m_files.clear();
        //  Roles/alts/etc...
        
        m_primary   = 0ULL;
        m_mode     = Mode::Uninit;
    }

    GGraph                      XGRuntime::primary() const
    {
        if(auto itr = m_files.find(m_primary); itr != m_files.end())
            return itr->second.graph;
        return {};
    }

    void    XGRuntime::reset()
    {
        m_results.clear();
        
        //  cursor back to zero
        
        for(auto& itr : m_elements)
            itr.second -> reset();
            
        m_mode     = Mode::Start;
    }
    
    const xg_result_t&          XGRuntime::result(const xg_cursor_t&k) const
    {
        static const xg_result_t    s_null_result;
        auto itr = m_results.find(k);
        if(itr != m_results.end())
            return itr->second;
        return s_null_result;
    }

    void                        XGRuntime::starts(push_k)
    {
        starts(PUSH, m_primary);
    }
    
    void                        XGRuntime::starts(push_k, uint64_t docId)
    {
        auto x = m_files.find(docId);
        if(x == m_files.end())
            return ;
        if(x->second.starts.empty())
            return;
        _push(State(x->second.starts), Tristate::NO);
    }
    
    xg_result_t                 XGRuntime::step(XGContext& ctx, const XGRuntimeOptions& opts)
    {
        switch(m_mode){
        case Mode::Uninit:
            return create_error<"XGRuntime has not been properly initialized">();
        case Mode::Error:
            return create_error<"XGRuntime is in an error state">();
        case Mode::Done:
            return create_error<"XGRuntime is already done">();
        case Mode::Run:
            break;
        case Mode::Start:
            starts(PUSH);
            break;
        default:
            break;
        }
        
        if(m_state.empty()){
            m_mode  = Mode::Done;
            return DONE;
        }
        
        xg_result_t     result;
        XGElement*      elem    = nullptr;
        
        {
            auto& st    = m_state.top();

            elem    = element(st.next.cursor);
            if(!elem){
                assert(elem && "XGRuntime encountered a null element");
                m_mode  = Mode::Error;
                return create_error<"XGRuntime encountered a null element">();
            }
            
            auto _runtime       = auto_reset(ctx.runtime, this);
            auto _interrupt     = auto_reset(ctx.interrupt, st.interrupt);
            auto _priority      = auto_reset(ctx.priority, st.priority);
            
            #ifdef NDEBUG
            try {
            #endif
            
                result          = elem -> execute(ctx);
                
            #ifdef NDEBUG
            } 
            catch(...){
                result          = ERROR;
            }
            #endif
        }
        
        m_results[elem->cursor()]   = result;
        if(opts.history)
            opts.history(elem->node(), result);
        
        if(is_error(result)){
            m_mode  = Mode::Error;
            return result;
        }

        return errors::todo();
    }
    
    bool                        XGRuntime::valid() const
    {
        return m_primary != 0ULL;
    }
    
}
