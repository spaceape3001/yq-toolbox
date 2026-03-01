////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/Map.hpp>
#include <yq/container/Stack.hpp>
#include <yq/graph/GGraph.hpp>
#include <yq/xg/types.hpp>

namespace yq {
    class XGRuntime {
    public:
    
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

        //! The "primary" graph
        GGraph                      primary() const;
    
        //! Last result for element
        //! \note Do NOT hold onto a reference, copy for permanent retention.
        const xg_result_t&          result(const xg_cursor_t&) const;
        
        bool                        valid() const;
        
        //! Clear & kill the runtime (all results...elements...etc)
        void                        kill();
        
        //! Resets to the start
        void                        reset();
        
    private:
        //GGraph                          m_primary;
        
        struct File {
            GGraph              graph;
            //AllLocal<xg_cur>  always;
            //AllLocal<xg_cur>  starts;
        };
        
        // Will support auxillary (ie reflexes)
        //  
        //Map<unsigned,GGraph>            m_byRoleID;
        //Map<std::string,GGraph,IgCase>  m_byRoleKey;
        Map<xg_cursor_t,XGElement*>     m_elements;
        Map<xg_cursor_t,xg_result_t>    m_results;
        Map<uint64_t,File>              m_files;
        uint64_t                        m_primary   = 0ULL;
        
        // Stack
    };
}
