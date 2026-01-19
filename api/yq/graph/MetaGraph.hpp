////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/math/Range.hpp>
#include <yq/typedef/color.hpp>
#include <map>
#include <string>
#include <vector>

namespace yq::graph {
    using icon_map_t    = std::map<uint16_t,std::string>;

    struct MetaBase {
        color_spec      color;
        std::string     description;
        std::string     key;
    };

    struct MetaPin : public MetaBase {
        std::string attach;                 //!< Where it attaches to on the symbol
        RangeU      count       = {1, 1};   //!< Count {0,0} implies unlimited, and {N,0} implies N...unlimited
        bool        input       = true;     //!< Input permitted
        bool        output      = true;     //!< Ouptut permitted
    };
    
    /*! \brief Information to a node
    */
    struct MetaNode : public MetaBase {
        color_spec              bgcolor;
        std::string             category;

        icon_map_t              icons;
        std::string             label;              //!< Display label for a palette

        std::vector<MetaPin>    pins;
        std::string             specification;

        std::string             symbol;
    };
    
    struct MetaEdge : public MetaBase {
        bool    bidir   = false;    //!< Bidirectional
    };
    
    struct MetaGraph : public MetaBase  {
        //! Bidirectional edge support
        Tristate                    bidirectional       = Tristate::Inherit;
        
        //! Nodes defined
        std::vector<MetaNode>       nodes;                      //!< Recognized node types

        //!< Unidirectional edge support
        Tristate                    unidirectional      = Tristate::Inherit;
    };
}
