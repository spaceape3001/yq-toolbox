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
        Vector2D            position    = NAN;
        Size2D              size        = NAN;
        std::string         type;  // URL/etc to the node template
        
        GNodeData(gid_t);
        GNodeData(const GNodeData&);
        virtual ~GNodeData();
        virtual GBaseData*  clone() const override;
        virtual bool is_node() const override { return true; }
    };
}
