////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/math/Range.hpp>
#include <yq/shape/Segment2.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/typedef/string_vectors.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/symbol/style.hpp>

namespace yq::symbol {
    
    //! General pin type
    enum class PinShape {
        Default,
        None,
        Arrow,
        Circle,
        Diamond,
        Oval,
        Rectangle,
        Triangle,
        Plus,
        Minus
    };
    
    enum class PinFlow {
        Bi,     //!< Bidirectional
        In,     //!< "Input" pin
        Out,    //!< "Output" pin
        NC      //!< No connection pin
    };
    
    struct PinBase  {
        //! Direction of pointing triangles, arrows, diamonds, etc
        Vector2F        direction   = { 0., 0. };
        Size2F          size        = { 0., 0. };
        PinFlow         flow        = PinFlow::Bi;
        PinShape        shape       = PinShape::Default; // "type" in the symbol file
        style_t         style;
    };
    
    struct Pin : public PinBase {
        std::string     key;
        Vector2F        position    = { 0., 0. };
    };

    struct Pins : public PinBase {
        Segment2F       segment   = ZERO;
        RangeU          count     = ZERO; // 0...0 implies any, N...0 implies N to no limit (keys will hint for 0...0)
        string_vector_t keys;
    };
}
