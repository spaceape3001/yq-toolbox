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
#include <yq/util/AutoReset.hpp>
#include <yq/util/Safety.hpp>
#include <yq/xg/logging.hpp>
#include <yq/xg/XGContext.hpp>

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

//////////////////

    // seems zero point in dedicated C++ source
    XGContext::XGContext() = default;
    XGContext::~XGContext() = default;

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

    uint64_x                    XGRuntime::compile(GGraph g)
    {
        if(!g.document())
            return unexpected<"null graph">();
            
        uint64_t    docId   = g.document()->id();
        if(m_files.contains(docId))
            return unexpected<"Already compiled">();
        
        Map<uint64_t,XGElement*>   elems;
        
        auto safe   = safety([&](){
            for(auto& itr : elems)
                delete itr.second;
        });
        
        for(GNode gn : g.nodes()){
            auto x  = compile(gn);
            if(!x)
                return unexpected(x.error());
            if(!*x)
                return errors::null_pointer();
            (*x) -> m_cursor = { docId, gn.id() };
            elems[gn.id()]  = *x;
        }
        
        for(GEdge ge : g.edges()){
            // todo
        }
        
        safe.disarm();

        File& file = m_files[docId];
        file.graph      = g;
        file.elements   = std::move(elems);

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
        auto me = auto_reset(ctx.runtime, this);
        
        for(unsigned n=0;n<opts.max_steps;++n){
            xg_result_t r = step(ctx);
            
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
    
    xg_result_t                 XGRuntime::step(XGContext& ctx)
    {
        switch(m_mode){
        case Mode::Uninit:
            return create_error<"XGUnit has not been properly initialized">();
        case Mode::Error:
            return create_error<"XGUnit is in an error state">();
        case Mode::Done:
            return create_error<"XGUnit is already done">();
        case Mode::Run:
            // chase the next 
        
            break;
            
        case Mode::Interrupt:
        
            // interrupt in progress
            break;
            
        case Mode::Start:
            //  find start element
            break;
            
        default:
            break;
        }

        return errors::todo();
    }
    
    bool                        XGRuntime::valid() const
    {
        return m_primary != 0ULL;
    }
    
}
