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
#include <yq/symbol/style.hpp>
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
    
    enum class TextType {
        Text,   //!< Generic text (no restrictions)
        Label,  //!< Simple label (no edit)
        Prog,   //!< Programmable label
        User    //!< User editable label
    };

    struct text_t {      // user/edit/prog text... 
        Vector2F        position    = ZERO;
        HAlign          halign      = HAlign::Center;
        VAlign          valign      = VAlign::Middle;

        std::string     text;   //!< Text to show (default for alterables/editables)
        TextType        type    = TextType::Text;
    };

    struct image_t {
        Size2F          size        = ZERO;
        Vector2F        position    = ZERO;
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
        image_t
    >;
    
    AxBox2F     bounds_for(const primitive_t&);
    
    struct Shape {
        primitive_t     primitive;
        style_t         style;
        std::string     key;    // key/ID
        
        Shape();
        Shape(const primitive_t&);
        Shape(const Shape&);
        Shape(Shape&&);
        ~Shape();
        Shape& operator=(const Shape&);
        Shape& operator=(Shape&&);
    };
}
