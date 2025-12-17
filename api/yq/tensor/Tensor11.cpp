////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor11.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
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
        w.format<math_io::format<Tensor11D>>();
        w.parse<math_io::parse<Tensor11D>>();
        w.print<math_io::print<Tensor11D>>();
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
        w.format<math_io::format<Tensor11F>>();
        w.parse<math_io::parse<Tensor11F>>();
        w.print<math_io::print<Tensor11F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor11F>();
    }

    {
        auto w = writer<Tensor11I>();
        w.description("1x1 tensor in integer");
        w.property(szXX, &Tensor11I::xx).description(szXX_Tensor);
        w.operate_self();
        w.operate_with<int>();
        w.operate_with<Tensor12I>();
        w.operate_with<Tensor13I>();
        w.operate_with<Tensor14I>();
        w.format<math_io::format<Tensor11I>>();
        w.parse<math_io::parse<Tensor11I>>();
        w.print<math_io::print<Tensor11I>>();
    }

    {
        auto w = writer<Tensor11U>();
        w.description("1x1 tensor in unsigned integer");
        w.property(szXX, &Tensor11U::xx).description(szXX_Tensor);
        w.operate_self();
        w.operate_with<unsigned>();
        w.operate_with<Tensor12U>();
        w.operate_with<Tensor13U>();
        w.operate_with<Tensor14U>();
        w.format<math_io::format<Tensor11U>>();
        w.parse<math_io::parse<Tensor11U>>();
        w.print<math_io::print<Tensor11U>>();
    }
}

YQ_INVOKE(reg_tensor11();)
