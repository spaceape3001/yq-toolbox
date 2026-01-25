////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GShape.hpp"
#include "GShapeData.hpp"

namespace yq {
    GShape::GShape() = default;
    GShape::GShape(const GShape&) = default;
    GShape::GShape(GShape&&) = default;
    GShape::GShape(GDocumentPtr doc, gid_t i) : GBase(doc, i) {}
    GShape::~GShape() = default;
    GShape& GShape::operator=(const GShape&) = default;
    GShape& GShape::operator=(GShape&&) = default;

    GShape::operator bool() const
    {
        return static_cast<bool>(data());
    }

    GShapeData*  GShape::data()
    {
        if(m_doc)
            return m_doc -> shape(m_id);
        return nullptr;
    }
    
    const GShapeData*  GShape::data() const
    {
        if(m_doc)
            return m_doc -> shape(m_id);
        return nullptr;
    }

    Vector2F  GShape::position() const
    {
        if(const GShapeData* gn = data())
            return gn -> position;
        return NAN;
    }
    
    void      GShape::position(set_k, const Vector2F&v)
    {
        if(GShapeData* gn = data())
            gn -> position  = v;
    }
}
