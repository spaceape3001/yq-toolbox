////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/Stack.hpp>
#include <yq/xg/types.hpp>
#include <functional>
#include <system_error>
#include <vector>

namespace yq::xg {
    class XGDocument;
    class XGElement;
    struct XGContext;
    
    struct XGRuntimeOptions {
        std::function<void(const XGElement*)>   history;
        size_t                                  iterations = 1000;
    };
    
    class XGRuntime {
    public:
    
        XGRuntime();
        ~XGRuntime();
        
        std::error_code             compile(const XGDocumentCPtr&);
        result_t                    step(XGContext&);
        result_t                    execute(XGContext&, const XGRuntimeOptions& options={});
        
        uint32_t                    current() const { return m_current; }
        
        //! Returns the element [1...count]
        const XGElement*            element(uint32_t) const;
        
        uint32_t                    size() const;
        
        //! Reset the runtime to the start
        void                        reset();
        
    private:
        //! Returns the element [1...count]
        XGElement*                  element(uint32_t);
        
        std::vector<XGDocumentCPtr> m_documents;    // keep documents alive
        std::vector<XGElement*>     m_elements;     // all elements... 
        std::vector<execute_t>      m_always;        // start elements
        std::vector<execute_t>      m_start;        // start elements
        Stack<id_t>                 m_stack;
        id_t                        m_current   = 0;
        
        result_t                    stepstep(XGContext&, const std::vector<execute_t>&);
    };
}
