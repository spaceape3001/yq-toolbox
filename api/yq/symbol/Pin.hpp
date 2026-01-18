////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/math/Range.hpp>
#include <yq/shape/Segment2.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/symbol/style.hpp>

namespace yq::symbol {
    
    //! General pin type
    enum class PinShape {
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
        Vector2F        dir         = { 0., 0. };
        Vector2F        size        = { 0., 0. };
        PinFlow         flow        = PinFlow::Bi;
        PinShape        shape       = PinShape::None;
        struct {
            stroke_style_t          stroke;
            fill_style_t            fill;
        } style;
        bool            filled      = false;
    };
    
    struct Pin : public PinBase {
        Vector2F        pos         = { 0., 0. };
    };

    struct Pins : public PinBase {
        Segment2F       segment   = ZERO;
        RangeU          count     = ZERO; // 0...0 implies any, N...0 implies N to no limit
    };
}
