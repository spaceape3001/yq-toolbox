////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGBA.hpp>
#include <yq/net/Url.hpp>
#include <yq/shape/AxBox2.hpp>
#include <yq/shape/Circle2.hpp>
#include <yq/shape/Oval2.hpp>
#include <yq/shape/Polygon2.hpp>
#include <yq/shape/Polyline2.hpp>
#include <yq/shape/Segment2.hpp>
#include <yq/shape/Triangle2.hpp>
#include <optional>
#include <variant>
#include <vector>

namespace yq::symbol {
    enum class HAlign {
        Left,
        Center,
        Right
    };

    enum class VAlign {
        Top,
        Middle,
        Bottom
    };
    
    struct aligned_t {
        Vector2F        point       = ZERO;
        HAlign          halign      = HAlign::Center;
        VAlign          valign      = VAlign::Middle;
    };

    struct label_t : public aligned_t  {
    };

    struct text_t : public aligned_t {
        std::string     text;
    };

    struct image_t {
        AxBox2F         box;
        Url             url;
    };
    
    using primitive_t   = std::variant<std::monostate,
        AxBox2F,
        Circle2F,
        Oval2F,
        Polygon2F,
        Polyline2F,
        Segment2F,
        Triangle2F,
        text_t,
        label_t,
        image_t
    >;
    
    struct Shape {
        std::vector<primitive_t>    primitives;
        std::optional<RGBA4F>       color;
        std::optional<RGBA4F>       bgcolor;
        
        Shape();
        Shape(const Shape&);
        Shape(Shape&&);
        ~Shape();
        Shape& operator=(const Shape&);
        Shape& operator=(Shape&&);
    };
}
