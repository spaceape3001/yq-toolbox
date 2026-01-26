////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/vector/Vector2.hpp>

#ifdef NAN
#undef NAN
#endif

namespace yq {
    class GNodeTemplate;
    struct GNodeData : public GBaseData {
        std::string         node_template;  // URL/etc to the node template
        Vector2F            position    = NAN;
        Size2F              size        = NAN;
        
        GNodeData(gid_t);
        GNodeData(const GNodeData&);
        virtual ~GNodeData();
        virtual GBaseData*  clone() const override;
        virtual bool is_node() const override { return true; }
    };
}
