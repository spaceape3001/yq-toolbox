////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBaseData.hpp>

namespace yq {
    struct GTextData : public GBaseData, public GPosSizeData {
        //std::string         symbol; // symbol, empty implies a rectangle/box
        std::string         text;
        
        
        GTextData(gid_t);
        GTextData(const GTextData&);
        virtual ~GTextData();
        GBaseData*  clone() const;
        virtual bool is_text() const { return true; }
        
    };
}
