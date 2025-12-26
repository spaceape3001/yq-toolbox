////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/xg/XGDocNode.hpp>
#include <yq/xg/XGDocText.hpp>
#include <yq/xg/XGDocLine.hpp>

namespace yq {
    struct XGDocDoc : public XGDocBase {
        std::vector<XGDocNode>  nodes;
        std::vector<XGDocText>  texts;
        std::vector<XGDocLine>  lines;
    };
}
