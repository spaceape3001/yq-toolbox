////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tensor21.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor11.hpp>
#include <yq/tensor/Tensor12.hpp>
#include <yq/tensor/Tensor13.hpp>
#include <yq/tensor/Tensor14.hpp>
#include <yq/tensor/Tensor22.hpp>
#include <yq/tensor/Tensor23.hpp>
#include <yq/tensor/Tensor24.hpp>

#include "Tensor21.hxx"

YQ_TYPE_IMPLEMENT(yq::Tensor21D)
YQ_TYPE_IMPLEMENT(yq::Tensor21F)
YQ_TYPE_IMPLEMENT(yq::Tensor21I)
YQ_TYPE_IMPLEMENT(yq::Tensor21U)

using namespace yq;

static void reg_tensor21()
{
    {
        auto w = writer<Tensor21D>();
        w.description("2x1 tensor in double");
        w.property(szXX, &Tensor21D::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21D::yx).description(szYX_Tensor);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector1D>();
        w.operate_with<Tensor11D>();
        w.operate_with<Tensor12D>();
        w.operate_with<Tensor13D>();
        w.operate_with<Tensor14D>();
        w.format<math_io::format<Tensor21D>>();
        w.parse<math_io::parse<Tensor21D>>();
        w.print<math_io::print<Tensor21D>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Tensor21D>();
    }

    {
        auto w = writer<Tensor21F>();
        w.description("2x1 tensor in float");
        w.property(szXX, &Tensor21F::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21F::yx).description(szYX_Tensor);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector1F>();
        w.operate_with<Tensor11F>();
        w.operate_with<Tensor12F>();
        w.operate_with<Tensor13F>();
        w.operate_with<Tensor14F>();
        w.format<math_io::format<Tensor21F>>();
        w.parse<math_io::parse<Tensor21F>>();
        w.print<math_io::print<Tensor21F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Tensor21F>();
    }

    {
        auto w = writer<Tensor21I>();
        w.description("2x1 tensor in integer");
        w.property(szXX, &Tensor21I::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21I::yx).description(szYX_Tensor);
        w.operate_self();
        w.operate_with<int>();
        w.operate_with<Vector1I>();
        w.operate_with<Tensor11I>();
        w.operate_with<Tensor12I>();
        w.operate_with<Tensor13I>();
        w.operate_with<Tensor14I>();
        w.format<math_io::format<Tensor21I>>();
        w.parse<math_io::parse<Tensor21I>>();
        w.print<math_io::print<Tensor21I>>();
    }

    {
        auto w = writer<Tensor21U>();
        w.description("2x1 tensor in unsigned integer");
        w.property(szXX, &Tensor21U::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21U::yx).description(szYX_Tensor);
        w.operate_self();
        w.operate_with<unsigned>();
        w.operate_with<Vector1U>();
        w.operate_with<Tensor11U>();
        w.operate_with<Tensor12U>();
        w.operate_with<Tensor13U>();
        w.operate_with<Tensor14U>();
        w.format<math_io::format<Tensor21U>>();
        w.parse<math_io::parse<Tensor21U>>();
        w.print<math_io::print<Tensor21U>>();
    }
}

YQ_INVOKE(reg_tensor21();)
