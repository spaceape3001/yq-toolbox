////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGRuntime.hpp"

#include <yq/errors.hpp>
#include <yq/xg/errors.hpp>
#include <yq/xg/XGContext.hpp>
#include <yq/xg/XGDocument.hpp>
#include <yq/xg/XGElement.hpp>

#include <cassert>

namespace yq::xg {
    bool    is_continue(const result_t& r)
    {
        return std::get_if<std::monostate>(&r) || std::get_if<continue_k>(&r);
    }
    
    bool    is_wait(const result_t& r)
    {
        return static_cast<bool>(std::get_if<wait_k>(&r));
    }
    
    bool    is_done(const result_t&r)
    {
        return static_cast<bool>(std::get_if<done_k>(&r));
    }
    
    bool    is_error(const result_t&r)
    {
        return std::get_if<error_k>(&r) || std::get_if<std::error_code>(&r);
    }

    XGRuntime::XGRuntime()
    {
        m_elements.push_back(nullptr);
    }
    
    XGRuntime::~XGRuntime()
    {
    }

  //struct pri_uint32_t {
        //uint32_t    idx = 0;
        //float       pri = 0.;
    //};
    
    std::error_code         XGRuntime::compile(const XGDocumentCPtr&)
    {
        return errors::todo();
    }

    XGElement*              XGRuntime::element(id_t n) 
    {
        if(n>=m_elements.size())
            return nullptr;
        return m_elements[n];
    }

    const XGElement*        XGRuntime::element(id_t n) const
    {
        if(n>=m_elements.size())
            return nullptr;
        return m_elements[n];
    }

    result_t                XGRuntime::execute(XGContext&ctx, const XGRuntimeOptions& options)
    {
        for(size_t n = 0; n<options.iterations; ++n){
            auto r  = step(ctx);
            if(options.history)
                options.history(element(m_current));
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
    
    uint32_t                XGRuntime::size() const
    {
        if(m_elements.empty())  
            return 0;
        return (uint32_t)(m_elements.size() - 1);
    }

    void    XGRuntime::reset()
    {
        m_current   = 0;
    }


    result_t                XGRuntime::step(XGContext& ctx)
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
        const std::vector<execute_t>&   m_always;
        const std::vector<execute_t>&   m_next;
        float                           m_thresh;
        std::vector<execute_t>::const_iterator  m_a, m_aEnd, m_b, m_bEnd;
        
        ExecuteBlender(
            const std::vector<execute_t>&   always,
            const std::vector<execute_t>&   next,
            float                           thresh
        ) : m_always(always), m_next(next), m_thresh(thresh)
        {
            m_a     = always.begin();
            m_aEnd  = always.end();
            
            if(!std::isnan(m_thresh) && (m_a != m_aEnd)){
                auto i = std::find_if(m_a, m_aEnd, [&](const execute_t&v) -> bool {
                    return v.pri > thresh;
                });
                if(i != m_aEnd)
                    m_aEnd  = i;
            }
            
            m_b     = next.begin();
            m_bEnd  = next.end();
        }
        
        const execute_t*    operator++()
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
    
    result_t                XGRuntime::stepstep(XGContext&ctx, const std::vector<execute_t>& next)
    {
        ExecuteBlender eb{ next, m_always, ctx.always };
        while(const execute_t* n = ++eb){
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
            result_t r   = xgExecElement -> execute(ctx);
            if(is_continue(r) || is_done(r))
                return r;
            if(is_wait(r) || is_error(r))
                continue;
            return errors::xg_invalid_result();
        }
        return WAIT;
    }
}
