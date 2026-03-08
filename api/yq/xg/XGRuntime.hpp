////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/Map.hpp>
#include <yq/container/Stack.hpp>
#include <yq/core/Flags.hpp>
#include <yq/graph/GGraph.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/xg/types.hpp>

namespace yq {
    struct XGContext;

    using XGHistoryFN       = std::function<void(const GNode&,const xg_result_t&)>;
    
    struct XGRuntimeOptions {
        XGHistoryFN     history;
        unsigned        max_steps   = 10000;
    };
    
    class XGRuntime {
    public:
    
        enum class Mode {
            Uninit      = 0,
            Start,
            Run,
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
        //std::error_code             add(int, GGraph);
        //std::error_code             add(const std::string&, GGraph);

        const auto&                 always() const { return m_always; }

        //! Push the current always chain
        void                        always(push_k);
        
        //! Push the specified document's always chain
        void                        always(push_k, uint64_t);

        //! Set the always chain
        void                        always(set_k, std::span<const uint64_t>);

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
        void                        primary(set_k, uint64_t);

        //! Resets to the start (and wipes results)
        void                        reset();
        
    
        //! Last result for element
        //! \note Do NOT hold onto a reference, copy for permanent retention.
        const xg_result_t&          result(const xg_cursor_t&) const;
        
        void                        starts(push_k);
        void                        starts(push_k, uint64_t);

        //! Executes *ONE* node
        xg_result_t                 step(XGContext&, const XGRuntimeOptions& opts={});
        
        bool                        valid() const;
        
        
    private:
        //GGraph                          m_primary;
        
        struct File {
            GGraph                      graph;
            Map<uint64_t,XGElement*>    elements;
            Vector<xg_next_t>           starts;
            Vector<xg_next_t>           always;
        };
        
        struct State {
            xg_next_t                   next        = {};
            xg_next_span_t              span        = {};
            size_t                      index       = 0ULL;
            int32_t                     priority    = INT32_MIN;
            
            bool interrupt() const;
            bool iterate() const;
            bool advance();
            
            State(bool fInterrupt=false);
            State(const xg_next_t&, bool fInterrupt=false);
            State(xg_next_span_t, bool fInterrupt=false);
        };
        
        void    _push(const State&);
        void    _replace(const State&);
        
        uint64_x                        compile(GGraph);
        Expect<XGElement*>              compile(const GNode&);
        
        // Will support auxillary (ie reflexes)
        //  
        //Map<unsigned,uint64_t>              m_byRoleID;
        //Map<std::string,uint64_t,IgCase>    m_byRoleKey;
        Map<xg_cursor_t,XGElement*>         m_elements;
        Map<xg_cursor_t,xg_result_t>        m_results;
        Map<uint64_t,File>                  m_files;
        uint64_t                            m_primary   = 0ULL;
        Mode                                m_mode      = Mode::Uninit;
        Stack<State>                        m_state;
        Vector<xg_next_t>                   m_always;
        //State                               m_current   = {};
        
        // Stack
    };
}
