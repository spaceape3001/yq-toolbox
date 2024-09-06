////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor14.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/tensor/Tensor11.hpp>
#include <yq-toolbox/tensor/Tensor12.hpp>
#include <yq-toolbox/tensor/Tensor13.hpp>
#include <yq-toolbox/tensor/Tensor41.hpp>
#include <yq-toolbox/tensor/Tensor42.hpp>
#include <yq-toolbox/tensor/Tensor43.hpp>
#include <yq-toolbox/tensor/Tensor44.hpp>

#include "Tensor14.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor14D)
YQ_TYPE_IMPLEMENT(yq::Tensor14F)
YQ_TYPE_IMPLEMENT(yq::Tensor14I)
YQ_TYPE_IMPLEMENT(yq::Tensor14U)

using namespace yq;

static void reg_tensor14()
{
    {
        auto w = writer<Tensor14D>();
        w.description("1x4 tensor in double");
        w.property(szXX, &Tensor14D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14D::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14D::xw).description(szXW_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector4D>();
        w.operate_with<Tensor41D>();
        w.operate_with<Tensor42D>();
        w.operate_with<Tensor43D>();
        w.operate_with<Tensor44D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor14D>();
    }

    {
        auto w = writer<Tensor14F>();
        w.description("1x4 tensor in float");
        w.property(szXX, &Tensor14F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14F::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14F::xw).description(szXW_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector4F>();
        w.operate_with<Tensor41F>();
        w.operate_with<Tensor42F>();
        w.operate_with<Tensor43F>();
        w.operate_with<Tensor44F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor14D>();
    }

    {
        auto w = writer<Tensor14I>();
        w.description("1x4 tensor in integer");
        w.property(szXX, &Tensor14I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14I::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14I::xw).description(szXW_Tensor);
    }

    {
        auto w = writer<Tensor14U>();
        w.description("1x4 tensor in unsigned integer");
        w.property(szXX, &Tensor14U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14U::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14U::xw).description(szXW_Tensor);
    }
}

YQ_INVOKE(reg_tensor14();)
