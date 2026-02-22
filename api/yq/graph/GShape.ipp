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

    Vector2D  GShape::position() const
    {
        if(const GShapeData* gn = data())
            return gn -> position;
        return NAN;
    }
    
    void      GShape::position(set_k, const Vector2D&v)
    {
        if(GShapeData* gn = data())
            gn -> position  = v;
    }

    Size2D  GShape::size() const
    {
        if(const GShapeData* gn = data())
            return gn -> size;
        return NAN;
    }
    
    void    GShape::size(set_k, const Size2D&v)
    {
        if(GShapeData* gn = data())
            gn -> size  = v;
    }

    symbol::TransformMode    GShape::transform() const
    {
        if(const GShapeData* gn = data())
            return gn -> transform;
        return symbol::TransformMode();
    }
    
    void                    GShape::transform(set_k, symbol::TransformMode v)
    {
        if(GShapeData* gn = data())
            gn -> transform  = v;
    }
    
    ////////////////////////////////////////////////////////////////////////////

    GShapeData::GShapeData(gid_t _id) : GBaseData(_id) 
    {
    }
    
    GShapeData::GShapeData(const GShapeData&) = default;
    GShapeData::~GShapeData() = default;
    
    GBaseData*  GShapeData::clone() const 
    { 
        return new GShapeData(*this); 
    }
}
