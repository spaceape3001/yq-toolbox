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
#include <yq/net/Url.hpp>

namespace yq::xg {
    struct XGDocNode : public XGDocBase, public XGBitBox, public XGBitPri {
    
        std::string     label;

        //! If unspecified, will use inherited (either meta or template) 
        //! \note DEPRECATED
        XGNodeType      node_type   = XGNodeType::Unspecified;
        
        Url             node_template;
        
        // DEPRECATED
        XGSpecType      spec_type   = XGSpecType::Unknown;
        
        // DEPRECATED
        std::string     spec_data;

    };
}
