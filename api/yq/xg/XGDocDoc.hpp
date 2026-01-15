////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/xg/XGDocEdge.hpp>
#include <yq/xg/XGDocNode.hpp>
#include <yq/xg/XGDocText.hpp>
#include <yq/xg/XGDocLine.hpp>

namespace yq {
    struct XGDocDoc : public XGDocBase {
        std::vector<XGDocEdge>  edges;
        std::vector<XGDocLine>  lines;
        std::vector<XGDocNode>  nodes;
        std::vector<XGDocText>  texts;
    };
}
