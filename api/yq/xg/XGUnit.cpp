////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGContext.hpp"
#include "XGUnit.hpp"

#include <yq/errors.hpp>
#include <yq/graph/GNodeTemplate.hpp>
#include <yq/xg/errors.hpp>
#include <yq/xg/logging.hpp>
#include <yq/xg/XGContext.hpp>
//#include <yq/xg/XGDocument.hpp>
#include <yq/xg/XGElement.hpp>

#include <yq/graph/GNodeObject.hxx>

#include <cassert>

namespace yq {
    bool    is_continue(const xg_result_t& r)
    {
        return std::get_if<std::monostate>(&r) || std::get_if<continue_k>(&r);
    }
    
    bool    is_wait(const xg_result_t& r)
    {
        return static_cast<bool>(std::get_if<wait_k>(&r));
    }
    
    bool    is_done(const xg_result_t&r)
    {
        return static_cast<bool>(std::get_if<done_k>(&r));
    }
    
    bool    is_error(const xg_result_t&r)
    {
        return std::get_if<error_k>(&r) || std::get_if<std::error_code>(&r);
    }

//////////////////

    // seems zero point in dedicated C++ source
    XGContext::XGContext() = default;
    XGContext::~XGContext() = default;

//////////////////
    
    XGUnit::XGUnit()
    {
    }
    
    XGUnit::~XGUnit()
    {
        clear();
    }
    
    Expect<XGElement*>  XGUnit::_compile(const GNode&gn)
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
        
        std::error_code ec  = GraphEngine::_initialize(*x, api);
        if(ec != std::error_code()){
            delete x;
            return unexpected(ec);
        }
    
        return x;
    }
    
    std::error_code     XGUnit::_compile(const GGraph& g)
    {
        for(GNode gn : g.nodes()){ 
            auto x  = _compile(gn);
            if(!x)
                return x.error();
            
            XGElement*  xg  = *x;
            switch(xg->metaInfo().node_type()){
            case XGNodeType::Always:
                
                break;
            case XGNodeType::Start:
                break;
            default:
                break;
            }
            
            m_nodes[gn.id()]    = *x;
        }
        
        return {};
    }

  //struct pri_uint32_t {
        //uint32_t    idx = 0;
        //float       pri = 0.;
    //};
    
    void  XGUnit::clear()
    {
        GraphEngine::clear();
    }

    std::error_code         XGUnit::compile(const GGraph& g)
    {
        if(m_graph.valid()) 
            return create_error<"XGUnit already has a graph, clear first">();
        
        m_graph     = g;
        m_current   = 0ULL;
        
        if(std::error_code ec = _compile(g); ec != std::error_code()){
            clear();
            return ec;
        }
            
        m_state     = State::Start;
        return {};
    }
    
    XGElement*              XGUnit::element(gid_t i)
    {
        return static_cast<XGElement*>(m_nodes.get(i,nullptr));
    }
    
    const XGElement*        XGUnit::element(gid_t i) const
    {
        return static_cast<XGElement*>(m_nodes.get(i,nullptr));
    }

    bool  XGUnit::empty() const
    {
        return m_nodes.empty();
    }

    xg_result_t             XGUnit::execute(XGContext&ctx, const XGUnitOptions& options)
    {
        for(size_t n = 0; n<options.iterations; ++n){
            auto r  = step(ctx, options);
            if(options.history)
                options.history(m_current);
            if(is_continue(r))
                continue;
            if(is_error(r))
                return r;
            if(is_done(r))
                return DONE;
            if(is_wait(r))
                return WAIT;
            return errors::xg_invalid_result();
        }
        return WAIT;
    }
    
    void    XGUnit::reset()
    {
        m_current   = 0;
    }

    size_t                XGUnit::size() const
    {
        return m_nodes.size();
    }


    xg_result_t             XGUnit::step(XGContext& ctx, const XGUnitOptions& options)
    {
        if(!m_current)
            return stepstep(ctx, m_start);

        XGElement* xgExecElement    = element(m_current);
        assert(xgExecElement);
        if(!xgExecElement)
            return errors::xg_invalid_element();
        return stepstep(ctx, xgExecElement->m_next);
    }
    
    struct ExecuteBlender {
        const std::vector<xg_execute_t>&   m_always;
        const std::vector<xg_execute_t>&   m_next;
        float                           m_thresh;
        std::vector<xg_execute_t>::const_iterator  m_a, m_aEnd, m_b, m_bEnd;
        
        ExecuteBlender(
            const std::vector<xg_execute_t>&   always,
            const std::vector<xg_execute_t>&   next,
            float                           thresh
        ) : m_always(always), m_next(next), m_thresh(thresh)
        {
            m_a     = always.begin();
            m_aEnd  = always.end();
            
            if(!std::isnan(m_thresh) && (m_a != m_aEnd)){
                auto i = std::find_if(m_a, m_aEnd, [&](const xg_execute_t&v) -> bool {
                    return v.pri > thresh;
                });
                if(i != m_aEnd)
                    m_aEnd  = i;
            }
            
            m_b     = next.begin();
            m_bEnd  = next.end();
        }
        
        const xg_execute_t*    operator++()
        {
            if(m_a != m_aEnd){
                if(m_b == m_bEnd)
                    return nullptr;
                return &*(m_b++);
            } else {
                if(m_b == m_bEnd)
                    return &*(m_a++);
            
            }
            
            return nullptr;
        }
    };
    
    xg_result_t            XGUnit::stepstep(XGContext&ctx, const std::vector<xg_execute_t>& next)
    {
        switch(m_state){
        case State::Uninit:
            return create_error<"XGUnit has not been properly initialized">();
        case State::Error:
            return create_error<"XGUnit is in an error state">();
        case State::Start:
            //  find start element
        default:
            break;
        }
    
        ExecuteBlender eb{ next, m_always, ctx.always };
        while(const xg_execute_t* n = ++eb){
            if(!n){
                if(!is_nan(ctx.always) && !m_stack.empty()){
                    m_current   = m_stack.pop();
                    return CONTINUE;
                } else {
                    return DONE;
                }
            }

            m_current                   = n->idx;
            XGElement* xgExecElement    = element(n->idx);
            assert(xgExecElement);
            if(!xgExecElement)
                return errors::xg_invalid_element();
            xg_result_t r   = xgExecElement -> execute(ctx);
            if(is_continue(r) || is_done(r))
                return r;
            if(is_wait(r) || is_error(r))
                continue;
            return errors::xg_invalid_result();
        }
        return WAIT;
    }
}
