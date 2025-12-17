////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor33.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor31.hpp>
#include <yq/tensor/Tensor32.hpp>
#include <yq/tensor/Tensor34.hpp>

#include "Tensor33.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor33D)
YQ_TYPE_IMPLEMENT(yq::Tensor33F)
YQ_TYPE_IMPLEMENT(yq::Tensor33I)
YQ_TYPE_IMPLEMENT(yq::Tensor33U)

using namespace yq;

static void reg_tensor33()
{
    {
        auto w = writer<Tensor33D>();
        w.description("3x3 tensor in double");
        w.property(szXX, &Tensor33D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor33D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor33D::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor33D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor33D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor33D::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor33D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor33D::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor33D::zz).description(szZZ_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector3D>();
        w.operate_with<Tensor31D>();
        w.operate_with<Tensor32D>();
        w.operate_with<Tensor34D>();
        w.format<math_io::format<Tensor33D>>();
        w.parse<math_io::parse<Tensor33D>>();
        w.print<math_io::print<Tensor33D>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor33D>();
    }

    {
        auto w = writer<Tensor33F>();
        w.description("3x3 tensor in float");
        w.property(szXX, &Tensor33F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor33F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor33F::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor33F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor33F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor33F::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor33F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor33F::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor33F::zz).description(szZZ_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector3F>();
        w.operate_with<Tensor31F>();
        w.operate_with<Tensor32F>();
        w.operate_with<Tensor34F>();
        w.format<math_io::format<Tensor33F>>();
        w.parse<math_io::parse<Tensor33F>>();
        w.print<math_io::print<Tensor33F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor33F>();
    }

    {
        auto w = writer<Tensor33I>();
        w.description("3x3 tensor in integer");
        w.property(szXX, &Tensor33I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor33I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor33I::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor33I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor33I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor33I::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor33I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor33I::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor33I::zz).description(szZZ_Tensor);
        w.operate_self();
        w.operate_with<int>();
        w.operate_with<Vector3I>();
        w.operate_with<Tensor31I>();
        w.operate_with<Tensor32I>();
        w.operate_with<Tensor34I>();
        w.format<math_io::format<Tensor33I>>();
        w.parse<math_io::parse<Tensor33I>>();
        w.print<math_io::print<Tensor33I>>();
    }

    {
        auto w = writer<Tensor33U>();
        w.description("3x3 tensor in unsigned integer");
        w.property(szXX, &Tensor33U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor33U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor33U::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor33U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor33U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor33U::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor33U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor33U::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor33U::zz).description(szZZ_Tensor);
        w.operate_self();
        w.operate_with<unsigned>();
        w.operate_with<Vector3U>();
        w.operate_with<Tensor31U>();
        w.operate_with<Tensor32U>();
        w.operate_with<Tensor34U>();
        w.format<math_io::format<Tensor33U>>();
        w.parse<math_io::parse<Tensor33U>>();
        w.print<math_io::print<Tensor33U>>();
    }
}

YQ_INVOKE(reg_tensor33();)
