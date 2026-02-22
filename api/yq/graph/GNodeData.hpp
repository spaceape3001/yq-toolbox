////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>
#include <yq/symbol/transform.hpp>

namespace yq {
    class GNodeTemplate;
    struct GNodeData : public GBaseData, public GPosSizeData, public GSocketCache, public GPortCache {
        symbol::TransformMode   transform;
        std::string             type;  // URL/etc to the node template
        
        GNodeData(gid_t);
        GNodeData(const GNodeData&);
        virtual ~GNodeData();
        virtual GBaseData*  clone() const override;
        virtual bool is_node() const override { return true; }
    };
}
