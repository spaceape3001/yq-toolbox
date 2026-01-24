////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/graph_types.hpp>

namespace yq::graph {
    class GBaseImpl {
    public:
    
    
        
        virtual bool    is_annotation() const { return false; }
        virtual bool    is_edge() const { return false; }
        virtual bool    is_graph() const { return false; }
        virtual bool    is_line() const { return false; }
        virtual bool    is_node() const { return false; }
        virtual bool    is_port() const { return false; }
        virtual bool    is_shape() const { return false; }
        virtual bool    is_text() const { return false; }
    
        GBaseImpl(id_t _id) : id(_id) {}
        virtual ~GBaseImpl(){}
    
        const id_t      id;
        bool            deleted = false;
    };
}
