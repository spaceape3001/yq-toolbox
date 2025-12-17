////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Circle2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/shape/AxBox2.hpp>

#include <yq/vector/Vector2.hxx>

#include "Circle2.hxx"

YQ_TYPE_IMPLEMENT(yq::Circle2D)
YQ_TYPE_IMPLEMENT(yq::Circle2F)
YQ_TYPE_IMPLEMENT(yq::Circle2I)
YQ_TYPE_IMPLEMENT(yq::Circle2U)

using namespace yq;

static void reg_circle2()
{
    {
        auto w = writer<Circle2D>();
        w.description("2D circle in double");
        w.property(szArea, &Circle2D::area).description(szArea_Circle).alias(szA);
        w.property(szBox, &Circle2D::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2D::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szCircumference, &Circle2D::circumference).description(szCircumference).alias({szCirc, szPerimeter, szPeri});
        w.property(szDiameter, &Circle2D::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2D::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2D::valid).description(szValid_Circle);
        w.format<math_io::format<Circle2D>>();
        w.parse<math_io::parse<Circle2D>>();
    }
    
    {
        auto w = writer<Circle2F>();
        w.description("2D circle in float");
        w.property(szArea, &Circle2F::area).description(szArea_Circle).alias(szA);
        w.property(szBox, &Circle2F::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2F::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szCircumference, &Circle2F::circumference).description(szCircumference).alias({szCirc, szPerimeter, szPeri});
        w.property(szDiameter, &Circle2F::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2F::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2F::valid).description(szValid_Circle);
        w.format<math_io::format<Circle2F>>();
        w.parse<math_io::parse<Circle2F>>();
    }
    
    {
        auto w = writer<Circle2I>();
        w.description("2D circle in integer");
        w.property(szBox, &Circle2I::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2I::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szDiameter, &Circle2I::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2I::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2I::valid).description(szValid_Circle);
        w.format<math_io::format<Circle2I>>();
        w.parse<math_io::parse<Circle2I>>();
    }
    
    {
        auto w = writer<Circle2U>();
        w.description("2D circle in unsigned int");
        w.property(szBox, &Circle2U::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2U::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szDiameter, &Circle2U::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2U::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2U::valid).description(szValid_Circle);
        w.format<math_io::format<Circle2U>>();
        w.parse<math_io::parse<Circle2U>>();
    }
}

YQ_INVOKE(reg_circle2();)
