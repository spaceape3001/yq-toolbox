////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBase.hpp>

namespace yq {
    class GLine : public GBase {
    public:
    
        GLine();
        GLine(const GLine&);
        GLine(GLine&&);
        GLine(GDocumentPtr, gid_t);
        
        ~GLine();
        
        GLine& operator=(const GLine&);
        GLine& operator=(GLine&&);
        operator bool() const;
        
        GLineData*          data();
        const GLineData*    data() const;
        
    };
}
