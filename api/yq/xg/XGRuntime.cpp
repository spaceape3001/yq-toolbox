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

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&str, const xg_cursor_t& v)
    {
        str << "{" << v.file << "," << v.gid << "}";
        return str;
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&str, const xg_next_t& v)
    {
        str << "{" << v.cursor.file << "," << v.cursor.gid << "/" << v.priority << "." << v.subpri << "}";
        return str;
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&str, const xg_result_t& v)
    {
        if(std::get_if<std::monostate>(&v)){
            str << "{DEFAULT}";
        } else if(auto p = std::get_if<std::error_code>(&v)){
            if(*p == std::error_code()){
                str << "{NO ERROR}";
            } else {
                str << "{ERROR: " << p->message() << "}";
            }
        } else if(auto p = std::get_if<bool>(&v)){
            if(*p){
                str << "{TRUE}";
            } else {
                str << "{FALSE}";
            }
        } else if(std::get_if<continue_k>(&v)){
            str << "{CONTINUE}";
        } else if(std::get_if<done_k>(&v)){
            str << "{DONE}";
        } else if(std::get_if<error_k>(&v)){
            str << "{ERROR}";
        } else if(std::get_if<limit_k>(&v)){
            str << "{LIMIT}";
        } else if(std::get_if<resume_k>(&v)){
            str << "{RESUME}";
        } else if(std::get_if<wait_k>(&v)){
            str << "{WAIT}";
        } else if(auto p = std::get_if<xg_cursor_t>(&v)){
            str << "{" << p->file << "," << p->gid << "}";
        } else {
            str << "{UNSUPPORTED}";
        }
        return str;
    }

//////////////////

    // seems zero point in dedicated C++ source
    XGContext::XGContext() = default;
    XGContext::~XGContext() = default;

//////////////////

    XGRuntime::State::State(bool fInterrupt)
    {
        if(fInterrupt)
            ++priority;
    }
    
    XGRuntime::State::State(const xg_next_t& nxt, bool fInterrupt) : State(fInterrupt)
    {
        next    = nxt;
    }
    
    XGRuntime::State::State(xg_next_span_t spn, bool fInterrupt) : State(fInterrupt)
    {
        span    = spn;
        if(!spn.empty())
            next    = spn[0];
    }

    bool XGRuntime::State::interrupt() const 
    { 
        return priority != INT32_MIN; 
    }
    
    bool XGRuntime::State::iterate() const 
    { 
        return !span.empty(); 
    }
    
    bool XGRuntime::State::advance()
    
    {
        if(!span.empty()){
            if(++index < span.size()){
                next    = span[index];
                return next.priority >= priority;
            }
        }
        next    = {};
        return false;
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
    
    void    XGRuntime::_push(const State& st)
    {
        if(m_state.empty()){
            m_state << st;
        } else {
            int32_t pri = std::max(st.priority, m_state.top().priority);
            m_state << st;
            m_state.top().priority  = pri;
        }
    }

    void    XGRuntime::_replace(const State& st)
    {
        if(m_state.empty()){
            m_state << st;
        } else {
            auto& top       = m_state.top();
            int32_t pri     = std::max(st.priority, top.priority);
            top             = st;
            top.priority    = pri;
        }
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
        _push(State(x->second.always, true));
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
        _push(State(x->second.starts, false));
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
            auto _interrupt     = auto_reset(ctx.interrupt, st.interrupt());
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

        State   st;
        
        bool next_      = false;
        bool advance_   = false;
        bool push_      = false;
        bool replace_   = false;
        bool done_      = false;
        bool wait_      = false;
        bool pop_       = false;
        bool continue_  = false;
        
        if(std::get_if<std::monostate>(&result)){
            next_       = true;
            advance_    = true;
            replace_    = true;
        } else if(auto p = std::get_if<bool>(&result)){
            if(*p){
                next_       = true;
                advance_    = true;
                replace_    = true;
            } else {
                advance_    = true;
            }
        } else if(auto p = std::get_if<std::error_code>(&result)){
            if(*p == std::error_code()){
                return result;
            } else {
                next_       = true;
                advance_    = true;
                replace_    = true;
            }
        } else if (std::get_if<continue_k>(&result)){
            continue_   = true;
        } else if(std::get_if<done_k>(&result)){
            done_       = true;
        } else if(std::get_if<error_k>(&result)){
            return result;
        } else if(std::get_if<limit_k>(&result)){
            xgError << "Unexpected limit from XGElement " << elem->metaInfo().name();
            return result;
        } else if(std::get_if<resume_k>(&result)){
            pop_        = true;
        } else if(std::get_if<wait_k>(&result)){
            wait_       = true;
        } else if(auto p = std::get_if<xg_cursor_t>(&result)){
            if(m_elements.contains(*p)){
                st      = State({.cursor=*p});
                push_   = true;
            } else {
                xgError << "Invalid cursor result from XGElement " << elem->metaInfo().name(); 
                m_mode  = Mode::Error;
                return result;
            }
        } else {
            m_mode  = Mode::Error;
            xgAlert << "Unexpected/unhandled result type from XGElement " << elem->metaInfo().name();
            return result;
        }
        
        //  done as if's as the action can change
        
        if(next_ && elem->m_next.empty()){
            st  = State(elem->m_next);
        }
        
        if(advance_){
            
        }
        
        if(m_elements.contains(st.next.cursor)){
            if(push_)
                _push(st);
            if(replace_)
                _replace(st);
            return result;
        }

#if 0        
        
        while(!m_state.empty()){
            switch(action){
            case Action::Next:
                if(!elem->next.empty()){
                    st      = State(elem->next);
                    action  = Push;
                } else {
                    action  = Advance;
                }
                
                
            case Action::Done:
                //  TODO: multigraph logic here... (for now...)
                m_mode  = Mode::Done;
                break;
            case Action::Error:
                m_mode  = Mode::Error;
                break;
            }
        }
        
        return result;
        
        if(action == Next){
            if(!elem->next.empty()){
                st      = State(elem->next);
                action  = Push;
            } else {
                action  = Advance;
            }
        }
        
        if(action == Advance){
        }
        
        if(action == Pop){
        }
        
        if(action == Push){
            // priority/interrupt adjustment
            m_state.push(st);
        }
        
        if(action == Done){
            m_mode  = Mode::Done;
        }
        
        if(action == Error){
            m_mode  = Mode::Eror;
        }
#endif
        
        return result;
    }
    
    bool                        XGRuntime::valid() const
    {
        return m_primary != 0ULL;
    }
    
}
