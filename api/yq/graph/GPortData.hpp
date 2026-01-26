////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>

namespace yq {
    struct GPortData : public GBaseData {
        
        GPortData(gid_t);
        GPortData(const GPortData&);
        virtual ~GPortData();
        virtual GBaseData*  clone() const override;
        virtual bool is_port() const { return true; }
    };
}
