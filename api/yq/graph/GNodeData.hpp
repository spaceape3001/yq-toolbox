////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GTextData.hpp>

namespace yq {
    struct GNodeData : public GTextData {
        std::string         specification;  // URL/etc to the node template
        std::vector<gid_t>  ports;
        
        virtual bool is_node() const override { return true; }
        GNodeData(gid_t _id) : GTextData(_id) {}
        virtual ~GNodeData(){}
    };
}
