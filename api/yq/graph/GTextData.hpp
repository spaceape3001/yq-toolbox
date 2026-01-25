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
    struct GTextData : public GBaseData {
    
        std::string         symbol; // symbol, empty implies a rectangle/box
        std::string         text;
        
        Vector2F            position    = NAN;
        Size2F              size        = NAN;
        
        virtual bool is_text() const { return true; }
        GTextData(gid_t _id) : GBaseData(_id) {}
        virtual ~GTextData(){}
        
    };
}
