////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/Map.hpp>
#include <yq/container/Stack.hpp>
#include <yq/graph/GGraph.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/xg/types.hpp>

namespace yq {
    struct XGContext;

    using XGHistoryFN       = std::function<void(const GNode&,const xg_result_t&)>;
    
    struct XGRuntimeOptions {
        XGHistoryFN     history;
        unsigned        max_steps   = 1000;
    };

    class XGRuntime {
    public:
    
        enum class Mode {
            Uninit      = 0,
            Start,
            Run,
            Interrupt,
            Done,
            Error
        };
        
        XGRuntime();
        ~XGRuntime();
        XGRuntime(GGraph);
    
        //  Initialize a graph
        std::error_code             initialize(GGraph);

        /*
            Future support: 
            1) Roles
            2) Auxillary (reflexes)
        */

        std::error_code             add(GGraph);
        std::error_code             add(int, GGraph);
        std::error_code             add(const std::string&, GGraph);

        XGElement*                  element(const xg_cursor_t&);
        const XGElement*            element(const xg_cursor_t&) const;

        size_t                      elements(count_k) const;

        xg_result_t                 execute(const XGRuntimeOptions& opts={});
        xg_result_t                 execute(XGContext&, const XGRuntimeOptions& opts={});

        //! Clear & kill the runtime (all results...elements...etc)
        void                        kill();
        
        Mode                        mode() const { return m_mode; }

        //! The "primary" graph
        GGraph                      primary() const;

        //! Resets to the start
        void                        reset();
    
        //! Last result for element
        //! \note Do NOT hold onto a reference, copy for permanent retention.
        const xg_result_t&          result(const xg_cursor_t&) const;
        
        xg_result_t                 step(XGContext&);
        
        bool                        valid() const;
        
        
    private:
        //GGraph                          m_primary;
        
        struct File {
            GGraph                      graph;
            Map<uint64_t,XGElement*>    elements;
            //AllLocal<xg_cur>  always;
            //AllLocal<xg_cur>  starts;
        };
        
        enum class X {
            Uninit,
            Iterate
        };
        
        struct State {
            Vector<XGElement*>          eval;
            xg_cursor_t                 cursor      = {};
            size_t                      index       = 0ULL;
            int32_t                     priority    = 0;
            X                           x           = X::Uninit;
        };
        
        uint64_x                        compile(GGraph);
        Expect<XGElement*>              compile(const GNode&);
        
        // Will support auxillary (ie reflexes)
        //  
        //Map<unsigned,GGraph>            m_byRoleID;
        //Map<std::string,GGraph,IgCase>  m_byRoleKey;
        Map<xg_cursor_t,XGElement*>     m_elements;
        Map<xg_cursor_t,xg_result_t>    m_results;
        Map<uint64_t,File>              m_files;
        uint64_t                        m_primary   = 0ULL;
        Mode                            m_mode      = Mode::Uninit;
        Stack<State>                    m_stack;
        State                           m_current   = {};
        
        // Stack
    };
}
