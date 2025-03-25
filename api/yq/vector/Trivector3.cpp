////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Trivector3.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/vector/Bivector3.hpp>
#include <yq/vector/Multivector3.hpp>
#include <yq/vector/Vector3.hpp>

#include "Trivector3.hxx"

YQ_TYPE_IMPLEMENT(yq::Trivector3D)
YQ_TYPE_IMPLEMENT(yq::Trivector3F)

using namespace yq;

static void reg_trivector3()
{
    {
        auto w = writer<Trivector3D>();
        w.description("3D trivector in double");
        w.property(szXYZ, &Trivector3D::xyz).description(szXYZ_Trivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector3D>();
        w.operate_with<Multivector3D>();
        w.operate_with<Vector3D>();
    }

    {
        auto w = writer<double>();
        w.operate_with<Trivector3D>();
    }
    
    {
        auto w = writer<Trivector3F>();
        w.description("3D trivector in float");
        w.property(szXYZ, &Trivector3F::xyz).description(szXYZ_Trivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector3F>();
        w.operate_with<Multivector3F>();
        w.operate_with<Vector3F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Trivector3F>();
    }
}

YQ_INVOKE(reg_trivector3();)
