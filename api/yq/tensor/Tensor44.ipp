////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor44.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor41.hpp>
#include <yq/tensor/Tensor42.hpp>
#include <yq/tensor/Tensor43.hpp>

#include "Tensor44.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor44D)
YQ_TYPE_IMPLEMENT(yq::Tensor44F)
YQ_TYPE_IMPLEMENT(yq::Tensor44I)
YQ_TYPE_IMPLEMENT(yq::Tensor44U)

using namespace yq;

static void reg_tensor44()
{
    {
        auto w = writer<Tensor44D>();
        w.description("4x4 tensor in double");
        w.property(szXX, &Tensor44D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor44D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor44D::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor44D::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor44D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor44D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor44D::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor44D::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor44D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor44D::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor44D::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor44D::zw).description(szZW_Tensor);
        w.property(szWX, &Tensor44D::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor44D::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor44D::wz).description(szWZ_Tensor);
        w.property(szWW, &Tensor44D::ww).description(szWW_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector4D>();
        w.operate_with<Tensor41D>();
        w.operate_with<Tensor42D>();
        w.operate_with<Tensor43D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor44D>();
    }

    {
        auto w = writer<Tensor44F>();
        w.description("4x4 tensor in float");
        w.property(szXX, &Tensor44F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor44F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor44F::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor44F::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor44F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor44F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor44F::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor44F::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor44F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor44F::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor44F::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor44F::zw).description(szZW_Tensor);
        w.property(szWX, &Tensor44F::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor44F::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor44F::wz).description(szWZ_Tensor);
        w.property(szWW, &Tensor44F::ww).description(szWW_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector4F>();
        w.operate_with<Tensor41F>();
        w.operate_with<Tensor42F>();
        w.operate_with<Tensor43F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor44D>();
    }

    {
        auto w = writer<Tensor44I>();
        w.description("4x4 tensor in integer");
        w.property(szXX, &Tensor44I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor44I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor44I::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor44I::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor44I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor44I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor44I::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor44I::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor44I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor44I::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor44I::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor44I::zw).description(szZW_Tensor);
        w.property(szWX, &Tensor44I::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor44I::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor44I::wz).description(szWZ_Tensor);
        w.property(szWW, &Tensor44I::ww).description(szWW_Tensor);
    }

    {
        auto w = writer<Tensor44U>();
        w.description("4x4 tensor in unsigned integer");
        w.property(szXX, &Tensor44U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor44U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor44U::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor44U::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor44U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor44U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor44U::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor44U::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor44U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor44U::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor44U::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor44U::zw).description(szZW_Tensor);
        w.property(szWX, &Tensor44U::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor44U::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor44U::wz).description(szWZ_Tensor);
        w.property(szWW, &Tensor44U::ww).description(szWW_Tensor);
    }
}

YQ_INVOKE(reg_tensor44();)
