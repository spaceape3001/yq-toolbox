////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


namespace yq {

    /*
        Toolbox graph is about graph data structures, algorithms.  
        There shouldn't be a "fixed" data structure, should be about adapters
        to inspect and operate... maybe
    */

    template <typename T>
    concept has_edge = requires {
        { &T::edge };
    };
    
    template <typename T>
    concept has_edge_id_type  = requires {
        { T::edge_id_type };
    };
    template <typename T>
    concept has_edge_type  = requires {
        { T::edge_type };
    };

    template <typename T>
    concept has_graph  = requires {
        { &T::graph };
    };

    template <typename T>
    concept has_graph_id_type  = requires {
        { T::graph_id_type };
    };

    template <typename T>
    concept has_graph_type  = requires {
        { T::graph_type };
    };

    template <typename T>
    concept has_node  = requires {
        { &T::node };
    };

    template <typename T>
    concept has_node_id_type  = requires {
        { T::node_id_type };
    };

    template <typename T>
    concept has_node_type  = requires {
        { T::node_type };
    };
        
    template <typename T>
    concept has_port  = requires {
        { &T::port };
    };

    template <typename T>
    concept has_port_id_type  = requires {
        { T::port_id_type };
    };
        
    template <typename T>
    concept has_port_type  = requires {
        { T::port_type };
    };
    
    template <typename T>
    concept graph_c     = (has_node<T> || has_node_type<T>) && (has_edge<T> || has_edge_type<T>);
    

}

