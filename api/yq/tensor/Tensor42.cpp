////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor42.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor21.hpp>
#include <yq/tensor/Tensor22.hpp>
#include <yq/tensor/Tensor23.hpp>
#include <yq/tensor/Tensor24.hpp>
#include <yq/tensor/Tensor41.hpp>
#include <yq/tensor/Tensor43.hpp>
#include <yq/tensor/Tensor44.hpp>

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
        w.format<math_io::format<Tensor42D>>();
        w.parse<math_io::parse<Tensor42D>>();
        w.print<math_io::print<Tensor42D>>();
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
        w.format<math_io::format<Tensor42F>>();
        w.parse<math_io::parse<Tensor42F>>();
        w.print<math_io::print<Tensor42F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor42F>();
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
        w.operate_self();
        w.operate_with<int>();
        w.operate_with<Vector2I>();
        w.operate_with<Tensor21I>();
        w.operate_with<Tensor22I>();
        w.operate_with<Tensor23I>();
        w.operate_with<Tensor24I>();
        w.format<math_io::format<Tensor42I>>();
        w.parse<math_io::parse<Tensor42I>>();
        w.print<math_io::print<Tensor42I>>();
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
        w.operate_self();
        w.operate_with<unsigned>();
        w.operate_with<Vector2U>();
        w.operate_with<Tensor21U>();
        w.operate_with<Tensor22U>();
        w.operate_with<Tensor23U>();
        w.operate_with<Tensor24U>();
        w.format<math_io::format<Tensor42U>>();
        w.parse<math_io::parse<Tensor42U>>();
        w.print<math_io::print<Tensor42U>>();
    }
}

YQ_INVOKE(reg_tensor42();)
