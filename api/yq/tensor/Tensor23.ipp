////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor23.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor21.hpp>
#include <yq/tensor/Tensor22.hpp>
#include <yq/tensor/Tensor24.hpp>
#include <yq/tensor/Tensor31.hpp>
#include <yq/tensor/Tensor32.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/tensor/Tensor34.hpp>

#include "Tensor23.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor23D)
YQ_TYPE_IMPLEMENT(yq::Tensor23F)
YQ_TYPE_IMPLEMENT(yq::Tensor23I)
YQ_TYPE_IMPLEMENT(yq::Tensor23U)

using namespace yq;

static void reg_tensor23()
{
    {
        auto w = writer<Tensor23D>();
        w.description("2x3 tensor in double");
        w.property(szXX, &Tensor23D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor23D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor23D::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor23D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor23D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor23D::yz).description(szYZ_Tensor);
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
        w.operate_with<Tensor23D>();
    }

    {
        auto w = writer<Tensor23F>();
        w.description("2x3 tensor in float");
        w.property(szXX, &Tensor23F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor23F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor23F::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor23F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor23F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor23F::yz).description(szYZ_Tensor);
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
        w.operate_with<Tensor23D>();
    }

    {
        auto w = writer<Tensor23I>();
        w.description("2x3 tensor in integer");
        w.property(szXX, &Tensor23I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor23I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor23I::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor23I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor23I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor23I::yz).description(szYZ_Tensor);
    }

    {
        auto w = writer<Tensor23U>();
        w.description("2x3 tensor in unsigned integer");
        w.property(szXX, &Tensor23U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor23U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor23U::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor23U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor23U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor23U::yz).description(szYZ_Tensor);
    }
}

YQ_INVOKE(reg_tensor23();)
