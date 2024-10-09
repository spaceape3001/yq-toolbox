////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#error "This file is *NOT* meant to be included, it's here as an example."

namespace yq::example {

    struct Definition_Simple {
        MyGraph*    graph(uint64_t) const;
        MyNode*     node(uint64_t) const;
        MyEdge*     edge(uint64_t) const;
        MyPin*      pin(uint64_t) const;
    };


    struct Definition_Pointer_No_ID {
        using graph_type = MyGraph*;        // Enables the sub-graph features
        using node_type  = MyNode*;         // Enables the node features (required)
        using edge_type  = MyEdge*;         // Enables the edge features (required)
        using pin_type   = MyPin*;          // Enables the pin features
    };
    
    struct Definition_Pointer_With_U64_ID {
        using graph_type = MyGraph*;        // Enables the graph features
        using graph_id   = uint64_t;
        
        using node_type  = MyNode*;         // Enables the node features
        using node_id    = uint64_t;
        
        using edge_type  = MyEdge*;         // Enables the edge features
        using edge_id    = uint64_t;
        
        using pin_type   = MyPin*;          // Enables the pin features
        using pin_id     = uint64_t;
    };
    
        /*
            NOTE... if types are NOT pointers, then IDs must be specified.
        */
    
    struct Definition_Struct_With_U64_ID {
        using graph_type = MyGraph;         // Enables the graph features
        using graph_id   = uint64_t;
        
        using node_type  = MyNode;          // Enables the node features
        using node_id    = uint64_t;
        
        using edge_type  = MyEdge;          // Enables the edge features
        using edge_id    = uint64_t;
        
        using pin_type   = MyPin;           // Enables the pin features
        using pin_id     = uint64_t;
    };
}
