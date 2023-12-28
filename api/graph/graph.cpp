////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphIO.ipp"
#include "GraphTraits.hpp"
#include <cstdint>
#include <0/meta/Init.hpp>


#ifndef NDEBUG
        /*
            Following are for testing the syntax of the traits, etc.
        */
    namespace {
        using namespace yq;
        
        struct TestGraph1 {

            struct Graph;
            struct Node;
            struct Edge;
            struct Pin;
            
            Edge*   edge(uint64_t) const;
            Graph*  graph(uint64_t) const;
            Node*   node(uint64_t) const;
            Pin*    pin(uint64_t) const;
        };
        
        static_assert( has_edge<TestGraph1> );
        static_assert( has_graph<TestGraph1> );
        static_assert( has_node<TestGraph1> );
        static_assert( has_pin<TestGraph1> );

        [[maybe_unused]] GraphTraits<TestGraph1>      tg1;

        struct TestGraph1a {

            struct Node;
            struct Edge;
            
            Edge*   edge(uint64_t) const;
            Node*   node(uint64_t) const;
        };

        static_assert( has_edge<TestGraph1a> );
        static_assert( !has_graph<TestGraph1a> );
        static_assert( has_node<TestGraph1a> );
        static_assert( !has_pin<TestGraph1a> );

        [[maybe_unused]] GraphTraits<TestGraph1a>    tg1a;

        struct TestGraph2 {

            struct Graph;
            struct Node;
            struct Edge;
            struct Pin;
            
            static Edge*   edge(uint64_t);
            static Graph*  graph(uint64_t);
            static Node*   node(uint64_t);
            static Pin*    pin(uint64_t);
        };

        static_assert( has_edge<TestGraph2> );
        static_assert( has_graph<TestGraph2> );
        static_assert( has_node<TestGraph2> );
        static_assert( has_pin<TestGraph2> );

        [[maybe_unused]] GraphTraits<TestGraph2>     tg2;
        
        struct TestGraph2a {

            struct Node;
            struct Edge;
            
            static Edge*   edge(uint64_t);
            static Node*   node(uint64_t);
        };
     
        static_assert( has_edge<TestGraph2a> );
        static_assert( !has_graph<TestGraph2a> );
        static_assert( has_node<TestGraph2a> );
        static_assert( !has_pin<TestGraph2a> );

        [[maybe_unused]] GraphTraits<TestGraph2a>    tg2a;
    }
    
#endif

YQ_TYPE_IMPLEMENT(yq::g::Flow)
YQ_TYPE_IMPLEMENT(yq::g::Option)


