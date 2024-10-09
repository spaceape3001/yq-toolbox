////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//#include <yq-0/graph/preamble.hpp>

#include <yq/trait/always_false.hpp>
#include <yq/trait/argument_type.hpp>
#include <yq/trait/function_arguments.hpp>
#include <yq/trait/return_type.hpp>

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
    concept has_pin  = requires {
        { &T::pin };
    };

    template <typename T>
    concept has_pin_id_type  = requires {
        { T::pin_id_type };
    };
        
    template <typename T>
    concept has_pin_type  = requires {
        { T::pin_type };
    };
    

    template <typename T>
    struct GraphTraits {
    
        //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //  EDGE TRAITS
        
            //! Detects for presence of an edge member
        static constexpr bool isEdgeMember()
        {
            if constexpr (has_edge<T>){
                static_assert(function_argument_count(&T::edge) >= 1, "Graph definition issue: edge() needs to take at least one argument");
                return std::is_member_function_pointer_v<decltype(&T::edge)>;
            }
            return false;
        }
        
            //! TRUE if this trait uses a member function for edge lookups
        static constexpr bool is_edge_member  = isEdgeMember();

            //! Detects for prescene of edge function 
            //! Note, edge member trumps function
        static constexpr bool isEdgeFunction()
        {
            if constexpr (has_edge<T> && !is_edge_member)
                return std::is_function_v<decltype(T::edge)>;
            return false;
        }

            //! TRUE if this trait uses a static function for edge lookups
        static constexpr bool is_edge_function  = isEdgeFunction();
        
            //! Detects the edge type... this cannot fail
        static constexpr auto deduceEdgeType() 
        {
            if constexpr (is_edge_member){
                return return_type_t<decltype(&T::edge)>();
            } else if constexpr (is_edge_function){
                return return_type_t<decltype(T::edge)>();
            } else if constexpr (has_edge_type<T>)
                return T::edge_type();
        }
        
            //! Our edge type
        using edge_type = decltype(deduceEdgeType());
        
        static_assert(!std::is_same_v<edge_type, void>, "Graph definition issue: edge_type or edge() is required");
        
            //! TRUE if the edge type is a pointer type
        static constexpr bool is_edge_pointer = std::is_pointer_v<edge_type>;
        
        static constexpr auto deduceEdgeId()
        {
            if constexpr (has_edge_id_type<T>){
                return T::edge_id_type();
            } else if constexpr (is_edge_member) {
                using arg_type  = decltype(function_first_argument(&T::edge));
                return std::remove_cvref_t<arg_type>();
            } else if constexpr (is_edge_function){
                using arg_type  = decltype(function_first_argument(T::edge));
                return std::remove_cvref_t<arg_type>();
            } else if constexpr (is_edge_pointer) {
                return edge_type();
            }
        }
        
        using edge_id_type  = decltype(deduceEdgeId());
        
        static_assert(!std::is_same_v<edge_id_type, void>, "Graph definition issue: edge_id_type is undefined and cannot be deduced");

        
        //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //  GRAPH TRAITS

            //! Detects for presence of an graph member
        static constexpr bool isGraphMember()
        {
            if constexpr (has_graph<T>)
                return std::is_member_function_pointer_v<decltype(&T::graph)>;
            return false;
        }

            //! TRUE if this trait uses a member function for graph lookups
        static constexpr bool is_graph_member = isGraphMember();

            //! Detects if trait's edge is a static function
        static constexpr bool isGraphFunction()
        {
            if constexpr (has_graph<T> && !is_graph_member)
                return std::is_function_v<decltype(T::graph)>;
            return false;
        }
        
            //! TRUE if this trait uses a static function for graph lookups
        static constexpr bool is_graph_function = isGraphFunction();
        
            //! Detects the edge type... this cannot fail
        static constexpr auto deduceGraphType() 
        {
            if constexpr (is_graph_member)
                return return_type_t<decltype(&T::graph)>();
            if constexpr (is_graph_function)
                return return_type_t<decltype(T::graph)>();
            if constexpr (has_graph_type<T>)
                return T::graph_type();
        }
        
            //! Our graph type
        using graph_type = decltype(deduceGraphType());
        
            //! TRUE if graphs can be called up (implies sub or multiple graphs)
        static constexpr const bool is_graph_enabled  = !std::is_same_v<graph_type, void>;
        
        static_assert(is_graph_enabled || !has_graph<T> || !has_graph_type<T>, "Graph definition issue: graph detected but has no type");
        

            //! TRUE if the graph type is a pointer type
        static constexpr bool is_graph_pointer = std::is_pointer_v<graph_type>;
        
        static auto deduceGraphId()
        {
            if constexpr (is_graph_enabled){
                if constexpr (has_graph_id_type<T>){
                    return T::graph_id_type();
                } else if constexpr (is_graph_member) {
                    using arg_type  = decltype(function_first_argument(&T::graph));
                    return std::remove_cvref_t<arg_type>();
                } else if constexpr (is_graph_function){
                    using arg_type  = decltype(function_first_argument(T::graph));
                    return std::remove_cvref_t<arg_type>();
                } else if constexpr (is_graph_pointer) {
                    return graph_type();
                }
            }
        }

        using graph_id_type = decltype(deduceGraphId());

        static_assert(!is_graph_enabled || !std::is_same_v<graph_id_type, void>, "Graph definition issue: graph_id_type is undefined and cannot be deduced");

        //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //  NODE TRAITS

            //! Detects for presence of an node member
        static consteval bool isNodeMember()
        {
            if constexpr (has_node<T>)
                return std::is_member_function_pointer_v<decltype(&T::node)>;
            return false;
        }

        static constexpr bool   is_node_member  = isNodeMember();

        static consteval bool isNodeFunction()
        {
            if constexpr (has_node<T> && !is_node_member)
                return std::is_function_v<decltype(T::node)>;
            return false;
        }

            //! TRUE if this trait uses a static function for node lookups
        static constexpr bool is_node_function = isNodeFunction();

            //! Detects the node type... this cannot fail
        static consteval auto deduceNodeType() 
        {
            if constexpr (is_node_member)
                return return_type_t<decltype(&T::node)>();
            if constexpr (is_node_function)
                return return_type_t<decltype(T::node)>();
            if constexpr (has_node_type<T>)
                return T::node_type();
        }
        
            //! Our node type
        using node_type = decltype(deduceNodeType());

        static_assert(!std::is_same_v<edge_type, void>, "Graph definition issue: node_type or node() is required");

        
            //! TRUE if the node type is a pointer type
        static constexpr bool is_node_pointer = std::is_pointer_v<node_type>;

        static constexpr auto deduceNodeId()
        {
            if constexpr (has_node_id_type<T>){
                return T::node_id_type();
            } else if constexpr (is_node_member) {
                using arg_type  = decltype(function_first_argument(&T::node));
                return std::remove_cvref_t<arg_type>();
            } else if constexpr (is_node_function){
                using arg_type  = decltype(function_first_argument(T::node));
                return std::remove_cvref_t<arg_type>();
            } else if constexpr (is_node_pointer) {
                return node_type();
            }
        }
        
        using node_id_type  = decltype(deduceNodeId());
        
        static_assert(!std::is_same_v<node_id_type, void>, "Graph definition issue: node_id_type is undefined and cannot be deduced");

        //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //  PIN TRAITS


            //! Detects for presence of an pin member
        static consteval bool isPinMember()
        {
            if constexpr (has_pin<T>)
                return std::is_member_function_pointer_v<decltype(&T::pin)>;
            return false;
        }

        static constexpr bool   is_pin_member  = isPinMember();

        static consteval bool isPinFunction()
        {
            if constexpr (has_pin<T> && !is_pin_member)
                return std::is_function_v<decltype(T::pin)>;
            return false;
        }

            //! TRUE if this trait uses a static function for pin lookups
        static constexpr bool is_pin_function = isPinFunction();

            //! Detects the pin type... this cannot fail
        static consteval auto deducePinType() 
        {
            if constexpr (is_pin_member)
                return return_type_t<decltype(&T::pin)>();
            if constexpr (is_pin_function)
                return return_type_t<decltype(T::pin)>();
            if constexpr (has_pin_type<T>)
                return T::pin_type();
        }
        
            //! Our pin type
        using pin_type = decltype(deducePinType());
        
            //! TRUE if this suppins pins
        static constexpr const bool is_pin_enabled     = !std::is_same_v<pin_type, void>;

            //! TRUE if the pin type is a pointer type
        static constexpr bool is_pin_pointer = std::is_pointer_v<pin_type>;

        static auto deducePinId()
        {
            if constexpr (is_pin_enabled){
                if constexpr (has_pin_id_type<T>){
                    return T::pin_id_type();
                } else if constexpr (is_pin_member) {
                    using arg_type  = decltype(function_first_argument(&T::pin));
                    return std::remove_cvref_t<arg_type>();
                } else if constexpr (is_pin_function){
                    using arg_type  = decltype(function_first_argument(T::pin));
                    return std::remove_cvref_t<arg_type>();
                } else if constexpr (is_pin_pointer) {
                    return pin_type();
                }
            }
        }

        using pin_id_type = decltype(deducePinId());

        static_assert(!is_pin_enabled || !std::is_same_v<pin_id_type, void>, "Graph definition issue: pin_id_type is undefined and cannot be deduced");

        //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    };
}

