////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor32.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/tensor/Tensor21.hpp>
#include <yq-toolbox/tensor/Tensor22.hpp>
#include <yq-toolbox/tensor/Tensor23.hpp>
#include <yq-toolbox/tensor/Tensor24.hpp>
#include <yq-toolbox/tensor/Tensor31.hpp>
#include <yq-toolbox/tensor/Tensor33.hpp>
#include <yq-toolbox/tensor/Tensor34.hpp>

#include "Tensor32.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor32D)
YQ_TYPE_IMPLEMENT(yq::Tensor32F)
YQ_TYPE_IMPLEMENT(yq::Tensor32I)
YQ_TYPE_IMPLEMENT(yq::Tensor32U)

using namespace yq;

static void reg_tensor32()
{
    {
        auto w = writer<Tensor32D>();
        w.description("3x2 tensor in double");
        w.property(szXX, &Tensor32D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32D::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32D::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32D::zy).description(szZY_Tensor);
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
        w.operate_with<Tensor32D>();
    }

    {
        auto w = writer<Tensor32F>();
        w.description("3x2 tensor in float");
        w.property(szXX, &Tensor32F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32F::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32F::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32F::zy).description(szZY_Tensor);
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
        w.operate_with<Tensor32D>();
    }

    {
        auto w = writer<Tensor32I>();
        w.description("3x2 tensor in integer");
        w.property(szXX, &Tensor32I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32I::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32I::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32I::zy).description(szZY_Tensor);
    }

    {
        auto w = writer<Tensor32U>();
        w.description("3x2 tensor in unsigned integer");
        w.property(szXX, &Tensor32U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32U::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32U::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32U::zy).description(szZY_Tensor);
    }
}

YQ_INVOKE(reg_tensor32();)
