////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor22.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/tensor/Tensor21.hpp>
#include <yq-toolbox/tensor/Tensor23.hpp>
#include <yq-toolbox/tensor/Tensor24.hpp>

#include "Tensor22.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor22D)
YQ_TYPE_IMPLEMENT(yq::Tensor22F)
YQ_TYPE_IMPLEMENT(yq::Tensor22I)
YQ_TYPE_IMPLEMENT(yq::Tensor22U)

using namespace yq;

static void reg_tensor22()
{
    {
        auto w = writer<Tensor22D>();
        w.description("2x2 tensor in double");
        w.property(szXX, &Tensor22D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22D::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22D::yy).description(szYY_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector2D>();
        w.operate_with<Tensor21D>();
        w.operate_with<Tensor23D>();
        w.operate_with<Tensor24D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor22D>();
    }

    {
        auto w = writer<Tensor22F>();
        w.description("2x2 tensor in float");
        w.property(szXX, &Tensor22F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22F::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22F::yy).description(szYY_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector2F>();
        w.operate_with<Tensor21F>();
        w.operate_with<Tensor23F>();
        w.operate_with<Tensor24F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor22D>();
    }

    {
        auto w = writer<Tensor22I>();
        w.description("2x2 tensor in integer");
        w.property(szXX, &Tensor22I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22I::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22I::yy).description(szYY_Tensor);
    }

    {
        auto w = writer<Tensor22U>();
        w.description("2x2 tensor in unsigned integer");
        w.property(szXX, &Tensor22U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22U::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22U::yy).description(szYY_Tensor);
    }
}

YQ_INVOKE(reg_tensor22();)
