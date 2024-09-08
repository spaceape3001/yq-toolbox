////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Quadvector4.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/vector/Bivector4.hpp>
#include <yq-toolbox/vector/Multivector4.hpp>
#include <yq-toolbox/vector/Trivector4.hpp>
#include <yq-toolbox/vector/Vector4.hpp>

#include "Quadvector4.hxx"

YQ_TYPE_IMPLEMENT(yq::Quadvector4D)
YQ_TYPE_IMPLEMENT(yq::Quadvector4F)

using namespace yq;

static void reg_quadvector4()
{
    {
        auto w = writer<Quadvector4D>();
        w.description("4D quadvector in double");
        w.property(szXYZW, &Quadvector4D::xyzw).description(szXYZW_Quadvector);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector4D>();
        w.operate_with<Multivector4D>();
        w.operate_with<Trivector4D>();
        w.operate_with<Vector4D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Quadvector4D>();
    }

    {
        auto w = writer<Quadvector4F>();
        w.description("4D quadvector in float");
        w.property(szXYZW, &Quadvector4F::xyzw).description(szXYZW_Quadvector);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector4F>();
        w.operate_with<Multivector4F>();
        w.operate_with<Trivector4F>();
        w.operate_with<Vector4F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Quadvector4F>();
    }
}

YQ_INVOKE(reg_quadvector4();)

