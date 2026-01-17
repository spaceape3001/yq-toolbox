////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Oval2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/shape/AxBox2.hpp>

#include <yq/vector/Vector2.hxx>

#include "Oval2.hxx"

YQ_TYPE_IMPLEMENT(yq::Oval2D)
YQ_TYPE_IMPLEMENT(yq::Oval2F)
YQ_TYPE_IMPLEMENT(yq::Oval2I)
YQ_TYPE_IMPLEMENT(yq::Oval2U)

using namespace yq;

static void reg_oval2()
{
    {
        auto w = writer<Oval2D>();
        w.description("2D oval in double");
        w.property(szArea, &Oval2D::area).description(szArea_Oval).alias(szA);
        w.property(szBox, &Oval2D::bounds).description(szBox_Oval);
        w.property(szCenter, &Oval2D::center).description(szCenter_Oval).alias({szPoint, szPt});
        //w.property(szCircumference, &Oval2D::circumference).description(szCircumference).alias({szCirc, szPerimeter, szPeri});
        w.property(szRadius, &Oval2D::radius).description(szRadius_Oval).alias({szRad, szR});
        w.property(szValid, &Oval2D::valid).description(szValid_Oval);
        w.format<math_io::format<Oval2D>>();
        w.parse<math_io::parse<Oval2D>>();
    }
    
    {
        auto w = writer<Oval2F>();
        w.description("2D oval in float");
        w.property(szArea, &Oval2F::area).description(szArea_Oval).alias(szA);
        w.property(szBox, &Oval2F::bounds).description(szBox_Oval);
        w.property(szCenter, &Oval2F::center).description(szCenter_Oval).alias({szPoint, szPt});
        //w.property(szCircumference, &Oval2F::circumference).description(szCircumference).alias({szCirc, szPerimeter, szPeri});
        w.property(szRadius, &Oval2F::radius).description(szRadius_Oval).alias({szRad, szR});
        w.property(szValid, &Oval2F::valid).description(szValid_Oval);
        w.format<math_io::format<Oval2F>>();
        w.parse<math_io::parse<Oval2F>>();
    }
    
    {
        auto w = writer<Oval2I>();
        w.description("2D oval in integer");
        w.property(szBox, &Oval2I::bounds).description(szBox_Oval);
        w.property(szCenter, &Oval2I::center).description(szCenter_Oval).alias({szPoint, szPt});
        w.property(szRadius, &Oval2I::radius).description(szRadius_Oval).alias({szRad, szR});
        w.property(szValid, &Oval2I::valid).description(szValid_Oval);
        w.format<math_io::format<Oval2I>>();
        w.parse<math_io::parse<Oval2I>>();
    }
    
    {
        auto w = writer<Oval2U>();
        w.description("2D oval in unsigned int");
        w.property(szBox, &Oval2U::bounds).description(szBox_Oval);
        w.property(szCenter, &Oval2U::center).description(szCenter_Oval).alias({szPoint, szPt});
        w.property(szRadius, &Oval2U::radius).description(szRadius_Oval).alias({szRad, szR});
        w.property(szValid, &Oval2U::valid).description(szValid_Oval);
        w.format<math_io::format<Oval2U>>();
        w.parse<math_io::parse<Oval2U>>();
    }
}

YQ_INVOKE(reg_oval2();)
