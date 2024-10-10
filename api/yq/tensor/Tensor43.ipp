////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor43.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor31.hpp>
#include <yq/tensor/Tensor32.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/tensor/Tensor34.hpp>
#include <yq/tensor/Tensor41.hpp>
#include <yq/tensor/Tensor42.hpp>
#include <yq/tensor/Tensor44.hpp>

#include "Tensor43.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor43D)
YQ_TYPE_IMPLEMENT(yq::Tensor43F)
YQ_TYPE_IMPLEMENT(yq::Tensor43I)
YQ_TYPE_IMPLEMENT(yq::Tensor43U)

using namespace yq;

static void reg_tensor43()
{
    {
        auto w = writer<Tensor43D>();
        w.description("4x3 tensor in double");
        w.property(szXX, &Tensor43D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor43D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor43D::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor43D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor43D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor43D::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor43D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor43D::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor43D::zz).description(szZZ_Tensor);
        w.property(szWX, &Tensor43D::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor43D::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor43D::wz).description(szWZ_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector3D>();
        w.operate_with<Tensor31D>();
        w.operate_with<Tensor32D>();
        w.operate_with<Tensor33D>();
        w.operate_with<Tensor34D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor43D>();
    }

    {
        auto w = writer<Tensor43F>();
        w.description("4x3 tensor in float");
        w.property(szXX, &Tensor43F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor43F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor43F::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor43F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor43F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor43F::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor43F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor43F::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor43F::zz).description(szZZ_Tensor);
        w.property(szWX, &Tensor43F::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor43F::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor43F::wz).description(szWZ_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector3F>();
        w.operate_with<Tensor31F>();
        w.operate_with<Tensor32F>();
        w.operate_with<Tensor33F>();
        w.operate_with<Tensor34F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor43D>();
    }

    {
        auto w = writer<Tensor43I>();
        w.description("4x3 tensor in integer");
        w.property(szXX, &Tensor43I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor43I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor43I::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor43I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor43I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor43I::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor43I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor43I::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor43I::zz).description(szZZ_Tensor);
        w.property(szWX, &Tensor43I::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor43I::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor43I::wz).description(szWZ_Tensor);
    }

    {
        auto w = writer<Tensor43U>();
        w.description("4x3 tensor in unsigned integer");
        w.property(szXX, &Tensor43U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor43U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor43U::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor43U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor43U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor43U::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor43U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor43U::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor43U::zz).description(szZZ_Tensor);
        w.property(szWX, &Tensor43U::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor43U::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor43U::wz).description(szWZ_Tensor);
    }
}

YQ_INVOKE(reg_tensor43();)
