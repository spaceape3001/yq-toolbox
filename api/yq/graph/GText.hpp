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
    class GText : public GBase {
    public:
        
        GText();
        GText(const GText&);
        GText(GText&&);
        GText(GDocumentPtr, gid_t);
        ~GText();
        GText& operator=(const GText&);
        GText& operator=(GText&&);
        
        operator bool() const;
        
        GTextData*  data();
        const GTextData*  data() const;

        Vector2D            position() const;
        void                position(set_k, const Vector2D&);

        Size2D              size() const;
        void                size(set_k, const Size2D&);
    };
}
