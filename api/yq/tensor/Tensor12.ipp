////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor12.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include <yq-toolbox/tensor/Tensor11.hpp>
#include <yq-toolbox/tensor/Tensor13.hpp>
#include <yq-toolbox/tensor/Tensor14.hpp>
#include <yq-toolbox/tensor/Tensor21.hpp>
#include <yq-toolbox/tensor/Tensor22.hpp>
#include <yq-toolbox/tensor/Tensor23.hpp>
#include <yq-toolbox/tensor/Tensor24.hpp>

#include "Tensor12.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor12D)
YQ_TYPE_IMPLEMENT(yq::Tensor12F)
YQ_TYPE_IMPLEMENT(yq::Tensor12I)
YQ_TYPE_IMPLEMENT(yq::Tensor12U)

using namespace yq;

static void reg_tensor12()
{
    {
        auto w = writer<Tensor12D>();
        w.description("1x2 tensor in double");
        w.property(szXX, &Tensor12D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12D::xy).description(szXY_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector2D>();
        w.operate_with<Tensor21D>();
        w.operate_with<Tensor22D>();
        w.operate_with<Tensor23D>();
        w.operate_with<Tensor24D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor12D>();
    }

    {
        auto w = writer<Tensor12F>();
        w.description("1x2 tensor in float");
        w.property(szXX, &Tensor12F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12F::xy).description(szXY_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector2F>();
        w.operate_with<Tensor21F>();
        w.operate_with<Tensor22F>();
        w.operate_with<Tensor23F>();
        w.operate_with<Tensor24F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor12D>();
    }

    {
        auto w = writer<Tensor12I>();
        w.description("1x2 tensor in integer");
        w.property(szXX, &Tensor12I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12I::xy).description(szXY_Tensor);
    }

    {
        auto w = writer<Tensor12U>();
        w.description("1x2 tensor in unsigned integer");
        w.property(szXX, &Tensor12U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12U::xy).description(szXY_Tensor);
    }
}

YQ_INVOKE(reg_tensor12();)
