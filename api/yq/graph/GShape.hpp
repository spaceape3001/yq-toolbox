////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBase.hpp>

namespace yq {
    class GShape : public GBase {
    public:
        
        GShape();
        GShape(const GShape&);
        GShape(GShape&&);
        GShape(GDocumentPtr, gid_t);
        ~GShape();
        GShape& operator=(const GShape&);
        GShape& operator=(GShape&&);
        
        operator bool() const;
        GShapeData*  data();
        const GShapeData*  data() const;
        
    };
}
