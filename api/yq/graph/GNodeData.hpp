////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GTextData.hpp>

namespace yq {
    class GNodeTemplate;
    struct GNodeData : public GTextData {
        std::string         node_template;  // URL/etc to the node template
        
        virtual bool is_node() const override { return true; }
        GNodeData(gid_t _id) : GTextData(_id) {}
        virtual ~GNodeData(){}
    };
}
