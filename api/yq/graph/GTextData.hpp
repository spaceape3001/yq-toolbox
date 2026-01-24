////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>

namespace yq {
    struct GTextData : public GBaseData {
        
        virtual bool is_text() const { return true; }
        GTextData(gid_t _id) : GBaseData(_id) {}
        virtual ~GTextData(){}
        
    };
}
