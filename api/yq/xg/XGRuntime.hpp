////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/Stack.hpp>
#include <yq/typedef/g_document.hpp>
#include <yq/graph/GGraph.hpp>
#include <yq/graph/GraphEngine.hpp>
#include <yq/typedef/graph.hpp>
#include <yq/xg/types.hpp>
#include <functional>
#include <system_error>
#include <vector>

namespace yq {
    class XGDocument;
    class XGElement;
    struct XGContext;
    class GGraph;
    
    struct XGRuntimeOptions {
        std::function<void(gid_t)>     history;
        size_t                          iterations = 1000;
    };
    
    class XGRuntime : public GraphEngine {
    public:
    
        XGRuntime();
        ~XGRuntime();
        
        std::error_code             compile(const GGraph&);
        void                        clear();
        gid_t                       current() const { return m_current; }
        
        XGElement*                  element(gid_t);
        const XGElement*            element(gid_t) const;
        
        bool                        empty() const;
        xg_result_t                 execute(XGContext&, const XGRuntimeOptions& options={});

        //! Reset the runtime to the start
        void                        reset();
        size_t                      size() const;
        xg_result_t                 step(XGContext&, const XGRuntimeOptions& options={});
        
        
    private:
        
        struct Node;
        
        std::error_code                 _compile(const GGraph&);
        Expect<XGElement*>              _compile(const GNode&);
        
        gid_t                           m_current   = 0ULL;
        
        //std::vector<GDocumentCPtr> m_documents;    // keep documents alive
        std::vector<xg_execute_t>       m_always;        // start elements
        std::vector<xg_execute_t>       m_start;        // start elements
        Stack<gid_t>                    m_stack;
        
        xg_result_t         stepstep(XGContext&, const std::vector<xg_execute_t>&);
    };
}
