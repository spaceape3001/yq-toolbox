////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Shape.hpp"
#include <yq/art/logging.hpp>
#include <yq/art/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Shape)

#ifdef NAN
    #undef NAN
#endif

namespace yq::art {
    void Shape::init_meta()
    {
        auto w = writer<Shape>();
        w.description("Abstract Shape");
    }

    ////////////////////////////////////////////////////////////////////////////

    Shape::Shape(Doc& doc) : Obj(doc)
    {
    }
    
    Shape::~Shape()
    {
    }

    void   Shape::save_to(XmlNode&x) const 
    {
        Obj::save_to(x);
    }
    
    bool   Shape::load_from(const XmlNode&x)
    {
        return Obj::load_from(x);
    }
}
