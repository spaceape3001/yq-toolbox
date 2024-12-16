////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor34.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor31.hpp>
#include <yq/tensor/Tensor32.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/tensor/Tensor41.hpp>
#include <yq/tensor/Tensor42.hpp>
#include <yq/tensor/Tensor43.hpp>
#include <yq/tensor/Tensor44.hpp>

#include "Tensor34.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor34D)
YQ_TYPE_IMPLEMENT(yq::Tensor34F)
YQ_TYPE_IMPLEMENT(yq::Tensor34I)
YQ_TYPE_IMPLEMENT(yq::Tensor34U)

using namespace yq;

static void reg_tensor34()
{
    {
        auto w = writer<Tensor34D>();
        w.description("3x4 tensor in double");
        w.property(szXX, &Tensor34D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor34D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor34D::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor34D::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor34D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor34D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor34D::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor34D::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor34D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor34D::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor34D::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor34D::zw).description(szZW_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector4D>();
        w.operate_with<Tensor41D>();
        w.operate_with<Tensor42D>();
        w.operate_with<Tensor43D>();
        w.operate_with<Tensor44D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor34D>();
    }

    {
        auto w = writer<Tensor34F>();
        w.description("3x4 tensor in float");
        w.property(szXX, &Tensor34F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor34F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor34F::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor34F::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor34F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor34F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor34F::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor34F::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor34F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor34F::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor34F::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor34F::zw).description(szZW_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector4F>();
        w.operate_with<Tensor41F>();
        w.operate_with<Tensor42F>();
        w.operate_with<Tensor43F>();
        w.operate_with<Tensor44F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor34D>();
    }

    {
        auto w = writer<Tensor34I>();
        w.description("3x4 tensor in integer");
        w.property(szXX, &Tensor34I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor34I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor34I::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor34I::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor34I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor34I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor34I::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor34I::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor34I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor34I::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor34I::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor34I::zw).description(szZW_Tensor);
    }

    {
        auto w = writer<Tensor34U>();
        w.description("3x4 tensor in unsigned integer");
        w.property(szXX, &Tensor34U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor34U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor34U::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor34U::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor34U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor34U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor34U::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor34U::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor34U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor34U::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor34U::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor34U::zw).description(szZW_Tensor);
    }
}

YQ_INVOKE(reg_tensor34();)
