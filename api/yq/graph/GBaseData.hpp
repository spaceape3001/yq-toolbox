////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/graph_types.hpp>

namespace yq {

    /*! \brief Base Data
    
        Base to the data classes... just enough complexity in the data
        structure that we can't go for simpleness.  It's point is to 
        render & import into whatever clever graph-like problem.
    */
    struct GBaseData {
        virtual bool    is_edge() const { return false; }
        virtual bool    is_graph() const { return false; }
        virtual bool    is_line() const { return false; }
        virtual bool    is_node() const { return false; }
        virtual bool    is_port() const { return false; }
        virtual bool    is_shape() const { return false; }
        virtual bool    is_text() const { return false; }
        virtual bool    is_view() const { return false; }
    
        GBaseData(gid_t _id) : id(_id) {}
        virtual ~GBaseData(){}
    
        const gid_t     id;
        
        //! We won't be deleting at runtime, so this will be the marker
        bool            deleted = false;
    };
}
