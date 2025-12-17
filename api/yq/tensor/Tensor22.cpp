////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor22.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor21.hpp>
#include <yq/tensor/Tensor23.hpp>
#include <yq/tensor/Tensor24.hpp>

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
        w.format<math_io::format<Tensor22D>>();
        w.parse<math_io::parse<Tensor22D>>();
        w.print<math_io::print<Tensor22D>>();
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
        w.format<math_io::format<Tensor22F>>();
        w.parse<math_io::parse<Tensor22F>>();
        w.print<math_io::print<Tensor22F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor22F>();
    }

    {
        auto w = writer<Tensor22I>();
        w.description("2x2 tensor in integer");
        w.property(szXX, &Tensor22I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22I::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22I::yy).description(szYY_Tensor);
        w.operate_self();
        w.operate_with<int>();
        w.operate_with<Vector2I>();
        w.operate_with<Tensor21I>();
        w.operate_with<Tensor23I>();
        w.operate_with<Tensor24I>();
        w.format<math_io::format<Tensor22I>>();
        w.parse<math_io::parse<Tensor22I>>();
        w.print<math_io::print<Tensor22I>>();
    }

    {
        auto w = writer<Tensor22U>();
        w.description("2x2 tensor in unsigned integer");
        w.property(szXX, &Tensor22U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22U::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22U::yy).description(szYY_Tensor);
        w.operate_self();
        w.operate_with<unsigned>();
        w.operate_with<Vector2U>();
        w.operate_with<Tensor21U>();
        w.operate_with<Tensor23U>();
        w.operate_with<Tensor24U>();
        w.format<math_io::format<Tensor22U>>();
        w.parse<math_io::parse<Tensor22U>>();
        w.print<math_io::print<Tensor22U>>();
    }
}

YQ_INVOKE(reg_tensor22();)
