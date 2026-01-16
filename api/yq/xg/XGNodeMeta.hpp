////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGBA.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/xg/XGNodeType.hpp>
#include <yq/xg/XGSpecType.hpp>

namespace yq {

    struct XGDocNode;

    //! Abstract type of node... could be from URL, the element Meta
    struct XGNodeMeta {
        using icon_map_t    = std::map<uint16_t,std::string>;
    
        RGBA4F          bgcolor     = kInvalidColor;
        std::string     category;
        RGBA4F          color       = kInvalidColor;
        std::string     description;
        icon_map_t      icons;
        std::string     label;
        XGNodeType      node_type   = XGNodeType::Unspecified;
        std::string     spec_data;
        XGSpecType      spec_type   = XGSpecType::Unknown;
        
        bool        operator==(const XGNodeMeta&) const;
        
        XGDocNode       spawn() const;
    };
}

YQ_TYPE_DECLARE(yq::XGNodeMeta);
