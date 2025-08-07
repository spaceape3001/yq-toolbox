////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Point.hpp"
#include <yq/art/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Point)

namespace yq::art {
    void Point::init_meta()
    {
        auto w = writer<Point>();
        w.description("Point");
    }

    Point::Point(Doc&doc) : Obj(doc)
    {
    }
    
    Point::~Point()
    {
    }

    bool    Point::load_from(const XmlNode&xn)
    {
        bool    success = Obj::load_from(xn);
        success = read_vertices(xn, {&m_vertex}) && success;
        return success;
    }
    
    void    Point::save_to(XmlNode&xn) const 
    {
        write_vertices(xn, { &m_vertex });
        Obj::save_to(xn);
    }

    void    Point::vertex(set_k, const vertex_t& v)
    {
        m_vertex    = v;
    }
}
