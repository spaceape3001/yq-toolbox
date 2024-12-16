////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor13.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor11.hpp>
#include <yq/tensor/Tensor12.hpp>
#include <yq/tensor/Tensor14.hpp>
#include <yq/tensor/Tensor31.hpp>
#include <yq/tensor/Tensor32.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/tensor/Tensor34.hpp>

#include "Tensor13.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor13D)
YQ_TYPE_IMPLEMENT(yq::Tensor13F)
YQ_TYPE_IMPLEMENT(yq::Tensor13I)
YQ_TYPE_IMPLEMENT(yq::Tensor13U)

using namespace yq;

static void reg_tensor13()
{
    {
        auto w = writer<Tensor13D>();
        w.description("1x3 tensor in double");
        w.property(szXX, &Tensor13D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13D::xz).description(szXZ_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector3D>();
        w.operate_with<Tensor31D>();
        w.operate_with<Tensor32D>();
        w.operate_with<Tensor33D>();
        w.operate_with<Tensor34D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor13D>();
    }

    {
        auto w = writer<Tensor13F>();
        w.description("1x3 tensor in float");
        w.property(szXX, &Tensor13F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13F::xz).description(szXZ_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector3F>();
        w.operate_with<Tensor31F>();
        w.operate_with<Tensor32F>();
        w.operate_with<Tensor33F>();
        w.operate_with<Tensor34F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor13D>();
    }

    {
        auto w = writer<Tensor13I>();
        w.description("1x3 tensor in integer");
        w.property(szXX, &Tensor13I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13I::xz).description(szXZ_Tensor);
    }

    {
        auto w = writer<Tensor13U>();
        w.description("1x3 tensor in unsigned integer");
        w.property(szXX, &Tensor13U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13U::xz).description(szXZ_Tensor);
    }
}

YQ_INVOKE(reg_tensor13();)
