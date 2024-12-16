////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor21.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor11.hpp>
#include <yq/tensor/Tensor12.hpp>
#include <yq/tensor/Tensor13.hpp>
#include <yq/tensor/Tensor14.hpp>
#include <yq/tensor/Tensor22.hpp>
#include <yq/tensor/Tensor23.hpp>
#include <yq/tensor/Tensor24.hpp>

#include "Tensor21.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor21D)
YQ_TYPE_IMPLEMENT(yq::Tensor21F)
YQ_TYPE_IMPLEMENT(yq::Tensor21I)
YQ_TYPE_IMPLEMENT(yq::Tensor21U)

using namespace yq;

static void reg_tensor21()
{
    {
        auto w = writer<Tensor21D>();
        w.description("2x1 tensor in double");
        w.property(szXX, &Tensor21D::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21D::yx).description(szYX_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector1D>();
        w.operate_with<Tensor11D>();
        w.operate_with<Tensor12D>();
        w.operate_with<Tensor13D>();
        w.operate_with<Tensor14D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor21D>();
    }

    {
        auto w = writer<Tensor21F>();
        w.description("2x1 tensor in float");
        w.property(szXX, &Tensor21F::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21F::yx).description(szYX_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector1F>();
        w.operate_with<Tensor11F>();
        w.operate_with<Tensor12F>();
        w.operate_with<Tensor13F>();
        w.operate_with<Tensor14F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor21D>();
    }

    {
        auto w = writer<Tensor21I>();
        w.description("2x1 tensor in integer");
        w.property(szXX, &Tensor21I::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21I::yx).description(szYX_Tensor);
    }

    {
        auto w = writer<Tensor21U>();
        w.description("2x1 tensor in unsigned integer");
        w.property(szXX, &Tensor21U::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21U::yx).description(szYX_Tensor);
    }
}

YQ_INVOKE(reg_tensor21();)
