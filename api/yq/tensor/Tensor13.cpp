////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor13.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor11.hpp>
#include <yq/tensor/Tensor12.hpp>
#include <yq/tensor/Tensor14.hpp>
#include <yq/tensor/Tensor31.hpp>
#include <yq/tensor/Tensor32.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/tensor/Tensor34.hpp>

#include "Tensor13.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor13D)
YQ_TYPE_IMPLEMENT(yq::Tensor13F)
YQ_TYPE_IMPLEMENT(yq::Tensor13I)
YQ_TYPE_IMPLEMENT(yq::Tensor13U)

using namespace yq;

static void reg_tensor13()
{
    {
        auto w = writer<Tensor13D>();
        w.description("1x3 tensor in double");
        w.property(szXX, &Tensor13D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13D::xz).description(szXZ_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector3D>();
        w.operate_with<Tensor31D>();
        w.operate_with<Tensor32D>();
        w.operate_with<Tensor33D>();
        w.operate_with<Tensor34D>();
        w.format<math_io::format<Tensor13D>>();
        w.parse<math_io::parse<Tensor13D>>();
        w.print<math_io::print<Tensor13D>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor13D>();
    }

    {
        auto w = writer<Tensor13F>();
        w.description("1x3 tensor in float");
        w.property(szXX, &Tensor13F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13F::xz).description(szXZ_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector3F>();
        w.operate_with<Tensor31F>();
        w.operate_with<Tensor32F>();
        w.operate_with<Tensor33F>();
        w.operate_with<Tensor34F>();
        w.format<math_io::format<Tensor13F>>();
        w.parse<math_io::parse<Tensor13F>>();
        w.print<math_io::print<Tensor13F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor13F>();
    }

    {
        auto w = writer<Tensor13I>();
        w.description("1x3 tensor in integer");
        w.property(szXX, &Tensor13I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13I::xz).description(szXZ_Tensor);
        w.operate_self();
        w.operate_with<unsigned>();
        w.operate_with<Vector3I>();
        w.operate_with<Tensor31I>();
        w.operate_with<Tensor32I>();
        w.operate_with<Tensor33I>();
        w.operate_with<Tensor34I>();
        w.format<math_io::format<Tensor13I>>();
        w.parse<math_io::parse<Tensor13I>>();
        w.print<math_io::print<Tensor13I>>();
    }

    {
        auto w = writer<Tensor13U>();
        w.description("1x3 tensor in unsigned integer");
        w.property(szXX, &Tensor13U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13U::xz).description(szXZ_Tensor);
        w.operate_self();
        w.operate_with<unsigned>();
        w.operate_with<Vector3U>();
        w.operate_with<Tensor31U>();
        w.operate_with<Tensor32U>();
        w.operate_with<Tensor33U>();
        w.operate_with<Tensor34U>();
        w.format<math_io::format<Tensor13U>>();
        w.parse<math_io::parse<Tensor13U>>();
        w.print<math_io::print<Tensor13U>>();
    }
}

YQ_INVOKE(reg_tensor13();)
