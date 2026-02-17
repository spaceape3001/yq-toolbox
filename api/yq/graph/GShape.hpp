////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GBase.hpp>
#include <yq/typedef/size2.hpp>
#include <yq/typedef/vector2.hpp>

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
        
        Vector2D            position() const;
        void                position(set_k, const Vector2D&);

        Size2D              size() const;
        void                size(set_k, const Size2D&);

        symbol::TransformMode    transform() const;
        void                    transform(set_k, symbol::TransformMode);
    };
}
