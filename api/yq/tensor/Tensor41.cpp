////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor41.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/math/math_io.hpp>
#include <yq/tensor/Tensor11.hpp>
#include <yq/tensor/Tensor12.hpp>
#include <yq/tensor/Tensor13.hpp>
#include <yq/tensor/Tensor14.hpp>
#include <yq/tensor/Tensor42.hpp>
#include <yq/tensor/Tensor43.hpp>
#include <yq/tensor/Tensor44.hpp>

#include "Tensor41.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor41D)
YQ_TYPE_IMPLEMENT(yq::Tensor41F)
YQ_TYPE_IMPLEMENT(yq::Tensor41I)
YQ_TYPE_IMPLEMENT(yq::Tensor41U)

using namespace yq;

static void reg_tensor41()
{
    {
        auto w = writer<Tensor41D>();
        w.description("4x1 tensor in double");
        w.property(szXX, &Tensor41D::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41D::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41D::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41D::wx).description(szWX_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector1D>();
        w.operate_with<Tensor11D>();
        w.operate_with<Tensor12D>();
        w.operate_with<Tensor13D>();
        w.operate_with<Tensor14D>();
        w.format<math_io::format<Tensor41D>>();
        w.parse<math_io::parse<Tensor41D>>();
        w.print<math_io::print<Tensor41D>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor41D>();
    }

    {
        auto w = writer<Tensor41F>();
        w.description("4x1 tensor in float");
        w.property(szXX, &Tensor41F::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41F::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41F::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41F::wx).description(szWX_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector1F>();
        w.operate_with<Tensor11F>();
        w.operate_with<Tensor12F>();
        w.operate_with<Tensor13F>();
        w.operate_with<Tensor14F>();
        w.format<math_io::format<Tensor41F>>();
        w.parse<math_io::parse<Tensor41F>>();
        w.print<math_io::print<Tensor41F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor41F>();
    }

    {
        auto w = writer<Tensor41I>();
        w.description("4x1 tensor in integer");
        w.property(szXX, &Tensor41I::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41I::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41I::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41I::wx).description(szWX_Tensor);
        w.operate_self();
        w.operate_with<int>();
        w.operate_with<Vector1I>();
        w.operate_with<Tensor11I>();
        w.operate_with<Tensor12I>();
        w.operate_with<Tensor13I>();
        w.operate_with<Tensor14I>();
        w.format<math_io::format<Tensor41I>>();
        w.parse<math_io::parse<Tensor41I>>();
        w.print<math_io::print<Tensor41I>>();
    }

    {
        auto w = writer<Tensor41U>();
        w.description("4x1 tensor in unsigned integer");
        w.property(szXX, &Tensor41U::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41U::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41U::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41U::wx).description(szWX_Tensor);
        w.operate_self();
        w.operate_with<unsigned>();
        w.operate_with<Vector1U>();
        w.operate_with<Tensor11U>();
        w.operate_with<Tensor12U>();
        w.operate_with<Tensor13U>();
        w.operate_with<Tensor14U>();
        w.format<math_io::format<Tensor41U>>();
        w.parse<math_io::parse<Tensor41U>>();
        w.print<math_io::print<Tensor41U>>();
    }
}

YQ_INVOKE(reg_tensor41();)
