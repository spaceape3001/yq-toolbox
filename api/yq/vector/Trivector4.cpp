////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Trivector4.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/vector/Bivector4.hpp>
#include <yq/vector/Multivector4.hpp>
#include <yq/vector/Quadvector4.hpp>
#include <yq/vector/Vector4.hpp>

#include "Trivector4.hxx"

YQ_TYPE_IMPLEMENT(yq::Trivector4D)
YQ_TYPE_IMPLEMENT(yq::Trivector4F)

using namespace yq;

static void reg_trivector4()
{
    {
        auto w = writer<Trivector4D>();
        w.description("4D trivector in double");
        w.property(szXYZ, &Trivector4D::xyz).description(szXYZ_Trivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szYZW, &Trivector4D::yzw).description(szYZW_Trivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZWX, &Trivector4D::zwx).description(szZWX_Trivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szWXY, &Trivector4D::wxy).description(szWXY_Trivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector4D>();
        w.operate_with<Multivector4D>();
        w.operate_with<Quadvector4D>();
        w.operate_with<Vector4D>();
        w.format<math_io::format<Trivector4D>>();
        w.parse<math_io::parse<Trivector4D>>();
        w.print<math_io::print<Trivector4D>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Trivector4D>();
    }

    {
        auto w = writer<Trivector4F>();
        w.description("4D trivector in float");
        w.property(szXYZ, &Trivector4F::xyz).description(szXYZ_Trivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szYZW, &Trivector4F::yzw).description(szYZW_Trivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZWX, &Trivector4F::zwx).description(szZWX_Trivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szWXY, &Trivector4F::wxy).description(szWXY_Trivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector4F>();
        w.operate_with<Multivector4F>();
        w.operate_with<Quadvector4F>();
        w.operate_with<Vector4F>();
        w.format<math_io::format<Trivector4F>>();
        w.parse<math_io::parse<Trivector4F>>();
        w.print<math_io::print<Trivector4F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Trivector4F>();
    }

}

YQ_INVOKE(reg_trivector4();)
