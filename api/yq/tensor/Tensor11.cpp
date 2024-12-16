////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor11.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor12.hpp>
#include <yq/tensor/Tensor13.hpp>
#include <yq/tensor/Tensor14.hpp>

#include "Tensor11.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor11D)
YQ_TYPE_IMPLEMENT(yq::Tensor11F)
YQ_TYPE_IMPLEMENT(yq::Tensor11I)
YQ_TYPE_IMPLEMENT(yq::Tensor11U)

using namespace yq;

static void reg_tensor11()
{
    {
        auto w = writer<Tensor11D>();
        w.description("1x1 tensor in double");
        w.property(szXX, &Tensor11D::xx).description(szXX_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector1D>();
        w.operate_with<Tensor12D>();
        w.operate_with<Tensor13D>();
        w.operate_with<Tensor14D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor11D>();
    }

    {
        auto w = writer<Tensor11F>();
        w.description("1x1 tensor in float");
        w.property(szXX, &Tensor11F::xx).description(szXX_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Tensor12F>();
        w.operate_with<Tensor13F>();
        w.operate_with<Tensor14F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor11D>();
    }

    {
        auto w = writer<Tensor11I>();
        w.description("1x1 tensor in integer");
        w.property(szXX, &Tensor11I::xx).description(szXX_Tensor);
    }

    {
        auto w = writer<Tensor11U>();
        w.description("1x1 tensor in unsigned integer");
        w.property(szXX, &Tensor11U::xx).description(szXX_Tensor);
    }
}

YQ_INVOKE(reg_tensor11();)
