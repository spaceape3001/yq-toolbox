////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Shape.hpp"

#include <yq/shape/AxBox2.hxx>
#include <yq/shape/Circle2.hxx>
#include <yq/shape/Oval2.hxx>
#include <yq/shape/Polygon2.hxx>
#include <yq/shape/Polyline2.hxx>
#include <yq/shape/Segment2.hxx>
#include <yq/shape/Triangle2.hxx>
#include <yq/vector/Vector2.hxx>

namespace yq::symbol {
    Shape::Shape() = default;
    Shape::Shape(const Shape&) = default;
    Shape::Shape(Shape&&) = default;
    Shape::~Shape() = default;
    Shape& Shape::operator=(const Shape&) = default;
    Shape& Shape::operator=(Shape&&) = default;

    Shape::Shape(const primitive_t& p) : primitive(p) {}

    AxBox2F     bounds_for(const primitive_t& v)
    {
        if(const auto p = std::get_if<AxBox2F>(&v))
            return *p;
        if(const auto p = std::get_if<Circle2F>(&v))
            return p->bounds();
        if(const auto p = std::get_if<Oval2F>(&v))
            return p->bounds();
        if(const auto p = std::get_if<Polyline2F>(&v))
            return p->bounds();
        if(const auto p = std::get_if<Polygon2F>(&v))
            return p->bounds();
        if(const auto p = std::get_if<Segment2F>(&v))
            return p->bounds();
        if(const auto p = std::get_if<Triangle2F>(&v))
            return p->bounds();
        if(const auto p = std::get_if<image_t>(&v)){
            return AxBox2F(
                { p->position.x-0.5f*p->size.x, p->position.y-0.5f*p->size.y },
                { p->position.x+0.5f*p->size.x, p->position.y+0.5f*p->size.y }
            );
        }
        return NAN;
    }
}
