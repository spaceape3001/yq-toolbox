////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Bivector3.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/vector/Multivector3.hpp>
#include <yq-toolbox/vector/Trivector3.hpp>
#include <yq-toolbox/vector/Vector3.hpp>

#include "Bivector3.hxx"

YQ_TYPE_IMPLEMENT(yq::Bivector3D)
YQ_TYPE_IMPLEMENT(yq::Bivector3F)

using namespace yq;

static void reg_bivector3()
{

    {
        auto w = writer<Bivector3D>();
        w.description("3D Bivector in double");
        w.property(szXY, &Bivector3D::xy).description(szXY_Bivector);
        w.property(szYZ, &Bivector3D::yz).description(szYZ_Bivector);
        w.property(szZX, &Bivector3D::zx).description(szZX_Bivector);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Multivector3D>();
        w.operate_with<Trivector3D>();
        w.operate_with<Vector3D>();
    }

    {
        auto w = writer<double>();
        w.operate_with<Bivector3D>();
    }

    {
        auto w = writer<Bivector3F>();
        w.description("3D Bivector in float");
        w.property(szXY, &Bivector3F::xy).description(szXY_Bivector);
        w.property(szYZ, &Bivector3F::yz).description(szYZ_Bivector);
        w.property(szZX, &Bivector3F::zx).description(szZX_Bivector);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Multivector3F>();
        w.operate_with<Trivector3F>();
        w.operate_with<Vector3F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Bivector3F>();
    }

}

namespace {
    YQ_INVOKE(reg_bivector3();)
}
