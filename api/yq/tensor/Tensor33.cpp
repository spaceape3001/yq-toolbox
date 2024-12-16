////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor33.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
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
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor33D>();
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
    }
}

YQ_INVOKE(reg_tensor33();)
