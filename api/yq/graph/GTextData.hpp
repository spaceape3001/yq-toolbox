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
    
        Vector2F            position    = NAN;
        Size2F              size        = NAN;
        std::string         symbol; // symbol, empty implies a rectangle/box
        std::string         text;
        
        
        GTextData(gid_t);
        GTextData(const GTextData&);
        virtual ~GTextData();
        GBaseData*  clone() const;
        virtual bool is_text() const { return true; }
        
    };
}
