////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Multivector3.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/vector/Bivector3.hpp>
#include <yq/vector/Trivector3.hpp>
#include <yq/vector/Vector3.hpp>

#include "Multivector3.hxx"

YQ_TYPE_IMPLEMENT(yq::Multivector3D)
YQ_TYPE_IMPLEMENT(yq::Multivector3F)

using namespace yq;

static void reg_multivector3()
{
    {
        auto w  = writer<Multivector3D>();
        w.description("3D Multivector in double");
        w.property(szA, &Multivector3D::a).description(szA_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szX, &Multivector3D::x).description(szX_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Multivector3D::y).description(szY_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Multivector3D::z).description(szZ_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szXY, &Multivector3D::xy).description(szXY_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szYZ, &Multivector3D::yz).description(szYZ_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZX, &Multivector3D::zx).description(szZX_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szXYZ, &Multivector3D::xyz).description(szXYZ_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector3D>();
        w.operate_with<Multivector3D>();
        w.operate_with<Trivector3D>();
        w.operate_with<Vector3D>();
        w.format<math_io::format<Multivector3D>>();
        w.parse<math_io::parse<Multivector3D>>();
        w.print<math_io::print<Multivector3D>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Multivector3D>();
    }

    {
        auto w  = writer<Multivector3F>();
        w.description("3D Multivector in float");
        w.property(szA, &Multivector3F::a).description(szA_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szX, &Multivector3F::x).description(szX_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Multivector3F::y).description(szY_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Multivector3F::z).description(szZ_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szXY, &Multivector3F::xy).description(szXY_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szYZ, &Multivector3F::yz).description(szYZ_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZX, &Multivector3F::zx).description(szZX_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szXYZ, &Multivector3F::xyz).description(szXYZ_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector3F>();
        w.operate_with<Multivector3F>();
        w.operate_with<Trivector3F>();
        w.operate_with<Vector3F>();
        w.format<math_io::format<Multivector3F>>();
        w.parse<math_io::parse<Multivector3F>>();
        w.print<math_io::print<Multivector3F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Multivector3F>();
    }
}

YQ_INVOKE(reg_multivector3();)
