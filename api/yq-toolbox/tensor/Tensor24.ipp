////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor24.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/tensor/Tensor21.hpp>
#include <yq-toolbox/tensor/Tensor22.hpp>
#include <yq-toolbox/tensor/Tensor23.hpp>
#include <yq-toolbox/tensor/Tensor41.hpp>
#include <yq-toolbox/tensor/Tensor42.hpp>
#include <yq-toolbox/tensor/Tensor43.hpp>
#include <yq-toolbox/tensor/Tensor44.hpp>

#include "Tensor24.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor24D)
YQ_TYPE_IMPLEMENT(yq::Tensor24F)
YQ_TYPE_IMPLEMENT(yq::Tensor24I)
YQ_TYPE_IMPLEMENT(yq::Tensor24U)

using namespace yq;

static void reg_tensor24()
{
    {
        auto w = writer<Tensor24D>();
        w.description("2x4 tensor in double");
        w.property(szXX, &Tensor24D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor24D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor24D::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor24D::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor24D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor24D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor24D::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor24D::yw).description(szYW_Tensor);
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
        w.operate_with<Tensor24D>();
    }

    {
        auto w = writer<Tensor24F>();
        w.description("2x4 tensor in float");
        w.property(szXX, &Tensor24F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor24F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor24F::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor24F::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor24F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor24F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor24F::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor24F::yw).description(szYW_Tensor);
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
        w.operate_with<Tensor24D>();
    }

    {
        auto w = writer<Tensor24I>();
        w.description("2x4 tensor in integer");
        w.property(szXX, &Tensor24I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor24I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor24I::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor24I::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor24I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor24I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor24I::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor24I::yw).description(szYW_Tensor);
    }

    {
        auto w = writer<Tensor24U>();
        w.description("2x4 tensor in unsigned integer");
        w.property(szXX, &Tensor24U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor24U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor24U::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor24U::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor24U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor24U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor24U::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor24U::yw).description(szYW_Tensor);
    }
}

YQ_INVOKE(reg_tensor24();)
