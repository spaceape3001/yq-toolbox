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
    namespace {
        void    _sort(std::vector<xg_next_t>& data)
        {
            std::stable_sort(data.begin(), data.end(), [](const xg_next_t&a, const xg_next_t& b){
                if(a.priority != b.priority)
                    return a.priority > b.priority;
                return a.subpri > b.subpri;
            });
        }


        constexpr bool is_starter(XGNodeType v)
        {
            switch(v){
            case XGNodeType::Always:
            case XGNodeType::Start:
                return true;
            default:
                return false;
            }
        }
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
        } else if(std::get_if<done_k>(&v)){
            str << "{DONE}";
        } else if(std::get_if<end_k>(&v)){
            str << "{END}";
        } else if(std::get_if<error_k>(&v)){
            str << "{ERROR}";
        } else if(std::get_if<limit_k>(&v)){
            str << "{LIMIT}";
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

    XGRuntime::State::State(const State&) = default;
    XGRuntime::State::State(State&&) = default;
    XGRuntime::State& XGRuntime::State::operator=(const State&) = default;
    XGRuntime::State& XGRuntime::State::operator=(State&&) = default;

    XGRuntime::State::operator bool() const
    {
        return next.cursor != xg_cursor_t{};
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
    

    void XGRuntime::_advance()
    {
        if(!m_state.empty()){
            m_state.top().advance();
            if(!m_state.top())
                _pop();
        }
    }
    
    bool    XGRuntime::_at_end() const
    {
        if(m_state.empty())
            return true;
        return !m_state.top().next.cursor.gid;
    }

    void XGRuntime::_next()
    {
        XGElement *elem = element(m_last);
        assert(elem);
        if(!elem)   
            return;

        if(elem->m_next.empty()){
            _pop();
        } else if(is_starter(elem->metaInfo().node_type())){
            _push(State(elem->m_next));
            m_state.peek(1)->advance();
        } else {
            _replace(State(elem->m_next));
        }
    }

    void    XGRuntime::_pop()
    {
        if(m_state.empty())
            return;
        m_state.pop();
        while(!m_state.empty() && !m_state.top())
            m_state.pop();
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
    
    std::error_code             XGRuntime::add(GGraph g)
    {
        auto x = compile(g);
        if(!x)
            return x.error();
        if(m_mode == Mode::Uninit){
            m_mode      = Mode::Start;
            m_primary   = *x;
        }
        return {};
    }
    
    //std::error_code             XGRuntime::add(int, GGraph)
    //{
        //return errors::todo();
    //}
    
    //std::error_code             XGRuntime::add(const std::string&, GGraph)
    //{
        //return errors::todo();
    //}

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

    void                        XGRuntime::always(set_k, std::span<const uint64_t> docs)
    {
        Vector<xg_next_t>  nodes;
        for(auto docId : docs){
            auto x = m_files.find(docId);
            if(x == m_files.end())
                continue;
            nodes += x->second.always;
        }
        _sort(nodes);
        m_always    = std::move(nodes);
    }

    uint64_x                    XGRuntime::compile(GGraph g)
    {
        if(!g.document())
            return unexpected<"null graph">();
            
        uint64_t    docId   = g.document()->id();
        if(m_files.contains(docId))
            return unexpected<"Already compiled">();
            
        if(g.document()->kind() != "executive")
            return unexpected<"Not an executive graph">();
        
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
            } else if(sx && tx){
                sx -> m_next.push_back(nx);
            }
        }
        
        //  TODO... sort the edges
        
        safe.disarm();

        File& file = m_files[docId];
        file.graph      = g;
        file.elements   = std::move(elems);
        file.starts     = std::move(starts);
        file.always     = std::move(always);
        

        for(auto& itr : file.elements){
            _sort(itr.second->m_next);
            m_elements[itr.second->cursor()] = itr.second;
        }
        
        _sort(file.always);
        _sort(file.starts);
        
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

    XGElement*                  XGRuntime::element(const GNode& gn)
    {
        if(!gn.document())
            return nullptr;
        return element(xg_cursor_t{gn.document()->id(), gn.id()});
    }
    
    const XGElement*            XGRuntime::element(const GNode& gn) const
    {
        if(!gn.document())
            return nullptr;
        return element(xg_cursor_t{gn.document()->id(), gn.id()});
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

    bool                        XGRuntime::interrupting() const
    {
        if(m_state.empty())
            return false;
        return m_state.top().priority != INT32_MIN;
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

    xg_cursor_t                 XGRuntime::next() const
    {
        if(m_state.empty())
            return {};
        return m_state.top().next.cursor;
    }

    GGraph                      XGRuntime::primary() const
    {
        if(auto itr = m_files.find(m_primary); itr != m_files.end())
            return itr->second.graph;
        return {};
    }

    void    XGRuntime::primary(set_k, uint64_t docId)
    {
        if(m_files.contains(docId)){
            m_primary   = docId;
            m_mode      = Mode::Start;
        }
    }

    int32_t                     XGRuntime::priority() const
    {
        if(m_state.empty())
            return INT32_MIN;
        return m_state.top().priority;
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
        if(itr == m_results.end())  
            return s_null_result;
        return itr->second;
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
            return END;
        }
        
        xg_result_t res = xnode(ctx, m_state.top().next.cursor, opts);

        if(std::get_if<std::monostate>(&res)){
            _next();
        } else if(auto p = std::get_if<std::error_code>(&res)){
            if(*p == std::error_code()){
                _next();
            } else {
                m_mode  = Mode::Error;
            }
        } else if(auto p = std::get_if<bool>(&res)){
            if(*p){
                _next();
            } else {
                _advance();
            }
        } else if(std::get_if<done_k>(&res)){
            m_mode  = Mode::Done;
        } else if(std::get_if<end_k>(&res)){
            xgAlert << "Unexpected END from XGElement";
            m_mode  = Mode::Done;
        } else if(std::get_if<error_k>(&res)){
            m_mode  = Mode::Error;
        } else if(std::get_if<limit_k>(&res)){
            xgAlert << "Unexpected limit from XGElement";
            m_mode  = Mode::Error;
        } else if(std::get_if<wait_k>(&res)){
            // TODO (currently, wait...wait...wait...)
        } else if(auto p = std::get_if<xg_cursor_t>(&res)){
            if(m_elements.contains(*p)){
                _push(State({.cursor=*p}));
            } else {
                xgError << "Invalid cursor result from XGElement";
                m_mode  = Mode::Error;
            }
        } else {
            m_mode  = Mode::Error;
            xgAlert << "Unexpected/unhandled result type from XGElement";
        }
        
        return res;
    }
    
    xg_result_t XGRuntime::xnode(XGContext& ctx, const xg_cursor_t& cur, const XGRuntimeOptions& opts)
    {
        XGElement*elem  = element(cur);
        if(!elem){
            xgError << "XGRuntime::xnode(" << cur << "): bad element";
            return create_error<"XGRuntime encountered a bad element">();
        }
            

        auto _runtime       = auto_reset(ctx.runtime, this);
        //auto _interrupt     = auto_reset(ctx.interrupt, st.interrupt());
        //auto _priority      = auto_reset(ctx.priority, st.priority);
        
        xg_result_t res;
        
        #ifdef NDEBUG
        try {
        #endif
        
            res          = elem -> execute(ctx);
            
        #ifdef NDEBUG
        } 
        catch(...){
            res          = ERROR;
        }
        #endif
        
        m_last  = elem->cursor();
        m_results[m_last]   = res;
        if(opts.history)
            opts.history(elem->node(), res);
        return res;
    }

    bool                        XGRuntime::valid() const
    {
        return m_primary != 0ULL;
    }
    
}
