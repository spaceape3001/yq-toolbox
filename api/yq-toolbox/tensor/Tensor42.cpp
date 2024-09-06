////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor42.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/tensor/Tensor21.hpp>
#include <yq-toolbox/tensor/Tensor22.hpp>
#include <yq-toolbox/tensor/Tensor23.hpp>
#include <yq-toolbox/tensor/Tensor24.hpp>
#include <yq-toolbox/tensor/Tensor41.hpp>
#include <yq-toolbox/tensor/Tensor43.hpp>
#include <yq-toolbox/tensor/Tensor44.hpp>

#include "Tensor42.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor42D)
YQ_TYPE_IMPLEMENT(yq::Tensor42F)
YQ_TYPE_IMPLEMENT(yq::Tensor42I)
YQ_TYPE_IMPLEMENT(yq::Tensor42U)

using namespace yq;

static void reg_tensor42()
{
    {
        auto w = writer<Tensor42D>();
        w.description("4x2 tensor in double");
        w.property(szXX, &Tensor42D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42D::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42D::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42D::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42D::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42D::wy).description(szWY_Tensor);
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
        w.operate_with<Tensor42D>();
    }

    {
        auto w = writer<Tensor42F>();
        w.description("4x2 tensor in float");
        w.property(szXX, &Tensor42F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42F::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42F::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42F::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42F::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42F::wy).description(szWY_Tensor);
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
        w.operate_with<Tensor42D>();
    }

    {
        auto w = writer<Tensor42I>();
        w.description("4x2 tensor in integer");
        w.property(szXX, &Tensor42I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42I::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42I::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42I::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42I::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42I::wy).description(szWY_Tensor);
    }

    {
        auto w = writer<Tensor42U>();
        w.description("4x2 tensor in unsigned integer");
        w.property(szXX, &Tensor42U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42U::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42U::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42U::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42U::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42U::wy).description(szWY_Tensor);
    }
}

YQ_INVOKE(reg_tensor42();)
