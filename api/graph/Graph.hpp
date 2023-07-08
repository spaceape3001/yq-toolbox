////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/preamble.hpp>

#include <basic/Any.hpp>
#include <basic/Enum.hpp>
#include <basic/Flag.hpp>
#include <basic/Map.hpp>
#include <basic/MinMaxDef.hpp>

namespace yq {
    /*! \brief Graph Descriptor Language
    
    
        This is a data-based graph descriptor language, for the purposes of 
        display & I/O.
        
        \note All structures can double as either definition or meta/generic
    */
    namespace g { 
        YQ_ENUM(Option, , 
            /*! \brief Marks the target as informational
            
                This means it's meta-data defining a property/node that *CAN* 
                be added.
            */
            INFO = 0,
            
            //! Pin support
            PINS,
            
            //! Supports multiple items
            MULTI
        );
    
    
        /*! \brief Type/Name/Description
        
            Base type/name/description descriptor block.
        */
        struct TND {
        
            //! Type of thing
            std::string     type;
            
            //! Name of thing
            std::string     name;
            
            //! Description of thing
            std::string     description;
            
            //! Miscellaneous notes
            std::string     notes;
            
            //! Flags for thing
            Flag<Option>    options       = {};
        };
        
        /*! \brief Generic property
        */
        struct Property : public TND {
        
            //! Value of the property (or default for info)
            Any                 value;
            
            //! COUNT of the property
            MinMaxDef<unsigned> count   = {0, 0, 0};
        };
        
        /*! \brief Base thing, has properties
        */
        struct Base : public TND {
            std::vector<Property>       properties;
        };
        
        /*! \brief Pin
        
            Pin to a node, maps inputs/outputs for the
            object.
        */
        struct Pin : public Base {
            Flow                flow;
            MinMaxDef<unsigned> count   = {0, 0, 0};
        };
        
        struct Pinned : public Base {
            std::vector<Pin>        pins;
        };
        
        /*! \brief Node
        */
        struct Node : public Pinned {
        };
    
        /*! \brief Socket
        
            used to represent endpoints
        */
        struct Socket {
            std::string     node;       //!< Node (empty implies graph-scoped pins)
            std::string     pin, sub;
            string_vector_t nodes;      //!< Type of nodes to restrict to
        };
        
        /*! \brief Edge
        
            Edge between nodes.
            
            Note, it'll be ILLEGAL for edges to jump graphs w/o hitting a pin.
        */
        struct Edge : public Base {
            Socket          source, target;
            string_vector_t datas;      //!< Type of datas permissible
        };

        /*! \brief Graph
            
            Graph (pins, nodes, & edges)
        */
        struct Graph : public Pinned {
            std::vector<Node>   nodes;
            std::vector<Edge>   edges;
        };

        /*! \brief Document
        
            Document has graphs.
        */
        struct Document : public Base {
            std::vector<Graph>  graphs;
        };
        

        std::error_code  load(Document&, const std::filesystem::path&, std::string_view rootTagName);
        std::error_code  load(Document&, const XmlDocument&, std::string_view rootTagName, std::string_view fileName=std::string_view());

        std::error_code  save(const std::filesystem::path&, const Document&, std::string_view rootTagName);
        std::error_code  save(XmlDocument&, const Document&, std::string_view rootTagName);
        
    }
}

YQ_TYPE_DECLARE(yq::g::Option)

