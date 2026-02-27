////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GNode.hpp>
#include <yq/graph/GNodeObject.hpp>
#include <yq/graph/GNodeTemplate.hpp>

namespace yq {
    struct GNodeObject::InitAPI {
        GNode               node;
        GNodeTemplateCPtr   node_template;
    };
}
