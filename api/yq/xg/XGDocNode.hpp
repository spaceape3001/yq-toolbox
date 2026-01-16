////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Tristate.hpp>
#include <yq/xg/XGBitBox.hpp>
#include <yq/xg/XGBitPri.hpp>
#include <yq/xg/XGDocBase.hpp>
#include <yq/xg/XGNodeType.hpp>
#include <yq/xg/XGSpecType.hpp>

namespace yq {
    struct XGDocNode : public XGDocBase, public XGBitBox, public XGBitPri {
    
        //! If unspecified, will use inherited (either meta or template)
        XGNodeType      node_type   = XGNodeType::Unspecified;
        
        XGSpecType      spec_type   = XGSpecType::Unknown;
        
        std::string     spec_data;

        std::string     label;
    };
}
