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
    
    struct XGUnitOptions {
        std::function<void(gid_t, const xg_result_t&)>      history;
        size_t                                              iterations = 1000;
    };
    
    /*! \brief Single graph file execution
    
        This runs a *SINGLE* executive graph file... 
    */
    class XGUnit : public GraphEngine {
    public:

        enum class State {
            Uninit,
            Start,
            Run,            // normal running
            Logic,          // logic running
            Interrupt,      // always
            Done,
            Error
        };
    
        XGUnit();
        XGUnit(const GGraph&);
        ~XGUnit();
        
        void                        clear();
        const xg_execute_t&         current() const { return m_current; }
        
        XGElement*                  element(gid_t);
        const XGElement*            element(gid_t) const;
        
        bool                        empty() const;
        
        //! Steps until there's a done/wait/error
        xg_result_t                 execute(const XGUnitOptions& options={});

        //! Steps until there's a done/wait/error
        xg_result_t                 execute(XGContext&, const XGUnitOptions& options={});

        std::error_code             initialize(const GGraph&);
        
        bool                        ready() const;

        //! Reset the runtime to the start
        void                        reset();
        size_t                      size() const;
        xg_result_t                 step(XGContext&, const XGUnitOptions& options={});
        
        State                       state() const { return m_state; }
        
        //! Odometer to total number of steps taken (note, if a lot, rollover might happen)
        size_t                      steps() const { return m_steps; }
        
    private:
    
        static void _sort(std::vector<xg_execute_t>&);
    
        
        struct Node;
        
        std::error_code                 _compile(const GGraph&);
        Expect<XGElement*>              _compile(const GNode&);
        
        
        //std::vector<GDocumentCPtr> m_documents;    // keep documents alive
        std::vector<xg_execute_t>       m_always;   //< always elements
        std::vector<xg_execute_t>       m_starts;   //< start elements
        Stack<xg_execute_t>             m_stack;
        State                           m_state             = State::Uninit;
        xg_execute_t                    m_current           = {};   // priority only matters once we're in interrupts
        size_t                          m_steps             = 0;
        
        xg_result_t         stepstep(XGContext&, const std::vector<xg_execute_t>&);
    };
}
