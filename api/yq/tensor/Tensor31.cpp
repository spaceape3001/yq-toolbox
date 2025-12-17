////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor31.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor11.hpp>
#include <yq/tensor/Tensor12.hpp>
#include <yq/tensor/Tensor13.hpp>
#include <yq/tensor/Tensor14.hpp>
#include <yq/tensor/Tensor32.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/tensor/Tensor34.hpp>

#include "Tensor31.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor31D)
YQ_TYPE_IMPLEMENT(yq::Tensor31F)
YQ_TYPE_IMPLEMENT(yq::Tensor31I)
YQ_TYPE_IMPLEMENT(yq::Tensor31U)

using namespace yq;

static void reg_tensor31()
{
    {
        auto w = writer<Tensor31D>();
        w.description("3x1 tensor in double");
        w.property(szXX, &Tensor31D::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31D::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31D::zx).description(szZX_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector1D>();
        w.operate_with<Tensor11D>();
        w.operate_with<Tensor12D>();
        w.operate_with<Tensor13D>();
        w.operate_with<Tensor14D>();
        w.format<math_io::format<Tensor31D>>();
        w.parse<math_io::parse<Tensor31D>>();
        w.print<math_io::print<Tensor31D>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor31D>();
    }

    {
        auto w = writer<Tensor31F>();
        w.description("3x1 tensor in float");
        w.property(szXX, &Tensor31F::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31F::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31F::zx).description(szZX_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector1F>();
        w.operate_with<Tensor11F>();
        w.operate_with<Tensor12F>();
        w.operate_with<Tensor13F>();
        w.operate_with<Tensor14F>();
        w.format<math_io::format<Tensor31F>>();
        w.parse<math_io::parse<Tensor31F>>();
        w.print<math_io::print<Tensor31F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor31F>();
    }

    {
        auto w = writer<Tensor31I>();
        w.description("3x1 tensor in integer");
        w.property(szXX, &Tensor31I::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31I::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31I::zx).description(szZX_Tensor);
        w.operate_self();
        w.operate_with<int>();
        w.operate_with<Vector1I>();
        w.operate_with<Tensor11I>();
        w.operate_with<Tensor12I>();
        w.operate_with<Tensor13I>();
        w.operate_with<Tensor14I>();
        w.format<math_io::format<Tensor31I>>();
        w.parse<math_io::parse<Tensor31I>>();
        w.print<math_io::print<Tensor31I>>();
    }

    {
        auto w = writer<Tensor31U>();
        w.description("3x1 tensor in unsigned integer");
        w.property(szXX, &Tensor31U::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31U::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31U::zx).description(szZX_Tensor);
    }
}

YQ_INVOKE(reg_tensor31();)
