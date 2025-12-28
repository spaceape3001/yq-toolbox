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

namespace yq {
    struct XGDocNode : public XGDocBase, public XGBitBox, public XGBitPri {

        //! Notes an "ALWAYS" node, ie, always check it (based on priority)
        Tristate        always      = Tristate::Inherit;

        //! Notes a decision node (more for rendering than not)
        Tristate        decision    = Tristate::Inherit;

        //! Notes a start node, so check on start (based on priority)
        Tristate        start       = Tristate::Inherit;

        //! Node's element meta name
        std::string     element;

    };
}
