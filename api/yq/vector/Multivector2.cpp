////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Multivector2.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/vector/Bivector2.hpp>
#include <yq/vector/Vector2.hpp>

#include "Multivector2.hxx"

YQ_TYPE_IMPLEMENT(yq::Multivector2D)
YQ_TYPE_IMPLEMENT(yq::Multivector2F)

using namespace yq;

static void reg_multivector2()
{
    {
        auto w  = writer<Multivector2D>();
        w.description("2D Multivector in double");
        w.property(szA, &Multivector2D::a).description(szA_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szX, &Multivector2D::x).description(szX_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Multivector2D::y).description(szY_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szXY, &Multivector2D::xy).description(szXY_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector2D>();
        w.operate_with<Vector2D>();
        w.format<math_io::format<Multivector2D>>();
        w.parse<math_io::parse<Multivector2D>>();
        w.print<math_io::print<Multivector2D>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Multivector2D>();
    }

    {
        auto w  = writer<Multivector2F>();
        w.description("2D Multivector in float");
        w.property(szA, &Multivector2F::a).description(szA_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szX, &Multivector2F::x).description(szX_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Multivector2F::y).description(szY_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szXY, &Multivector2F::xy).description(szXY_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector2F>();
        w.operate_with<Vector2F>();
        w.format<math_io::format<Multivector2F>>();
        w.parse<math_io::parse<Multivector2F>>();
        w.print<math_io::print<Multivector2F>>();
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Multivector2F>();
    }

}

YQ_INVOKE(reg_multivector2();)
