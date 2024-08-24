////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/math/preamble.hpp>
#include <0/math/strings.hpp>


#include <0/math/vector/Tensor11.hpp>
#include <0/math/vector/Tensor12.hpp>
#include <0/math/vector/Tensor13.hpp>
#include <0/math/vector/Tensor14.hpp>

#include <0/math/vector/Tensor21.hpp>
#include <0/math/vector/Tensor22.hpp>
#include <0/math/vector/Tensor23.hpp>
#include <0/math/vector/Tensor24.hpp>

#include <0/math/vector/Tensor31.hpp>
#include <0/math/vector/Tensor32.hpp>
#include <0/math/vector/Tensor33.hpp>
#include <0/math/vector/Tensor34.hpp>

#include <0/math/vector/Tensor41.hpp>
#include <0/math/vector/Tensor42.hpp>
#include <0/math/vector/Tensor43.hpp>
#include <0/math/vector/Tensor44.hpp>

#include <0/basic/DelayInit.hpp>
#include <0/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::Tensor11D)
YQ_TYPE_IMPLEMENT(yq::Tensor11F)
YQ_TYPE_IMPLEMENT(yq::Tensor11I)
YQ_TYPE_IMPLEMENT(yq::Tensor11U)

YQ_TYPE_IMPLEMENT(yq::Tensor12D)
YQ_TYPE_IMPLEMENT(yq::Tensor12F)
YQ_TYPE_IMPLEMENT(yq::Tensor12I)
YQ_TYPE_IMPLEMENT(yq::Tensor12U)

YQ_TYPE_IMPLEMENT(yq::Tensor13D)
YQ_TYPE_IMPLEMENT(yq::Tensor13F)
YQ_TYPE_IMPLEMENT(yq::Tensor13I)
YQ_TYPE_IMPLEMENT(yq::Tensor13U)

YQ_TYPE_IMPLEMENT(yq::Tensor14D)
YQ_TYPE_IMPLEMENT(yq::Tensor14F)
YQ_TYPE_IMPLEMENT(yq::Tensor14I)
YQ_TYPE_IMPLEMENT(yq::Tensor14U)

YQ_TYPE_IMPLEMENT(yq::Tensor21D)
YQ_TYPE_IMPLEMENT(yq::Tensor21F)
YQ_TYPE_IMPLEMENT(yq::Tensor21I)
YQ_TYPE_IMPLEMENT(yq::Tensor21U)

YQ_TYPE_IMPLEMENT(yq::Tensor22D)
YQ_TYPE_IMPLEMENT(yq::Tensor22F)
YQ_TYPE_IMPLEMENT(yq::Tensor22I)
YQ_TYPE_IMPLEMENT(yq::Tensor22U)

YQ_TYPE_IMPLEMENT(yq::Tensor23D)
YQ_TYPE_IMPLEMENT(yq::Tensor23F)
YQ_TYPE_IMPLEMENT(yq::Tensor23I)
YQ_TYPE_IMPLEMENT(yq::Tensor23U)

YQ_TYPE_IMPLEMENT(yq::Tensor24D)
YQ_TYPE_IMPLEMENT(yq::Tensor24F)
YQ_TYPE_IMPLEMENT(yq::Tensor24I)
YQ_TYPE_IMPLEMENT(yq::Tensor24U)

YQ_TYPE_IMPLEMENT(yq::Tensor31D)
YQ_TYPE_IMPLEMENT(yq::Tensor31F)
YQ_TYPE_IMPLEMENT(yq::Tensor31I)
YQ_TYPE_IMPLEMENT(yq::Tensor31U)

YQ_TYPE_IMPLEMENT(yq::Tensor32D)
YQ_TYPE_IMPLEMENT(yq::Tensor32F)
YQ_TYPE_IMPLEMENT(yq::Tensor32I)
YQ_TYPE_IMPLEMENT(yq::Tensor32U)

YQ_TYPE_IMPLEMENT(yq::Tensor33D)
YQ_TYPE_IMPLEMENT(yq::Tensor33F)
YQ_TYPE_IMPLEMENT(yq::Tensor33I)
YQ_TYPE_IMPLEMENT(yq::Tensor33U)

YQ_TYPE_IMPLEMENT(yq::Tensor34D)
YQ_TYPE_IMPLEMENT(yq::Tensor34F)
YQ_TYPE_IMPLEMENT(yq::Tensor34I)
YQ_TYPE_IMPLEMENT(yq::Tensor34U)

YQ_TYPE_IMPLEMENT(yq::Tensor41D)
YQ_TYPE_IMPLEMENT(yq::Tensor41F)
YQ_TYPE_IMPLEMENT(yq::Tensor41I)
YQ_TYPE_IMPLEMENT(yq::Tensor41U)

YQ_TYPE_IMPLEMENT(yq::Tensor42D)
YQ_TYPE_IMPLEMENT(yq::Tensor42F)
YQ_TYPE_IMPLEMENT(yq::Tensor42I)
YQ_TYPE_IMPLEMENT(yq::Tensor42U)

YQ_TYPE_IMPLEMENT(yq::Tensor43D)
YQ_TYPE_IMPLEMENT(yq::Tensor43F)
YQ_TYPE_IMPLEMENT(yq::Tensor43I)
YQ_TYPE_IMPLEMENT(yq::Tensor43U)

YQ_TYPE_IMPLEMENT(yq::Tensor44D)
YQ_TYPE_IMPLEMENT(yq::Tensor44F)
YQ_TYPE_IMPLEMENT(yq::Tensor44I)
YQ_TYPE_IMPLEMENT(yq::Tensor44U)


//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//  OTHER HELPERS FOR MATH

namespace yq {
    namespace {
    }
}    
    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

static void reg_tensor_math () {

    // General order ... all alphabetical
    //
    //      1. properties
    //      2. methods
    //
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Tensor

    {
        auto w = writer<Tensor11D>();
        w.description("1x1 tensor in double");
        w.property(szXX, &Tensor11D::xx);
        w.operate_self();
    }

    {
        auto w = writer<Tensor11F>();
        w.description("1x1 tensor in float");
        w.property(szXX, &Tensor11F::xx);
    }

    {
        auto w = writer<Tensor11I>();
        w.description("1x1 tensor in integer");
        w.property(szXX, &Tensor11I::xx).description(szXX_Tensor);
    }

    {
        auto w = writer<Tensor11U>();
        w.description("1x1 tensor in unsigned integer");
        w.property(szXX, &Tensor11U::xx).description(szXX_Tensor);
    }

    {
        auto w = writer<Tensor12D>();
        w.description("1x2 tensor in double");
        w.property(szXX, &Tensor12D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12D::xy).description(szXY_Tensor);
        w.operate_self();
    }

    {
        auto w = writer<Tensor12F>();
        w.description("1x2 tensor in float");
        w.property(szXX, &Tensor12F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12F::xy).description(szXY_Tensor);
    }

    {
        auto w = writer<Tensor12I>();
        w.description("1x2 tensor in integer");
        w.property(szXX, &Tensor12I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12I::xy).description(szXY_Tensor);
    }

    {
        auto w = writer<Tensor12U>();
        w.description("1x2 tensor in unsigned integer");
        w.property(szXX, &Tensor12U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12U::xy).description(szXY_Tensor);
    }

    {
        auto w = writer<Tensor13D>();
        w.description("1x3 tensor in double");
        w.property(szXX, &Tensor13D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13D::xz).description(szXZ_Tensor);
        w.operate_self();
    }

    {
        auto w = writer<Tensor13F>();
        w.description("1x3 tensor in float");
        w.property(szXX, &Tensor13F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13F::xz).description(szXZ_Tensor);
    }

    {
        auto w = writer<Tensor13I>();
        w.description("1x3 tensor in integer");
        w.property(szXX, &Tensor13I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13I::xz).description(szXZ_Tensor);
    }

    {
        auto w = writer<Tensor13U>();
        w.description("1x3 tensor in unsigned integer");
        w.property(szXX, &Tensor13U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13U::xz).description(szXZ_Tensor);
    }

    {
        auto w = writer<Tensor14D>();
        w.description("1x4 tensor in double");
        w.property(szXX, &Tensor14D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14D::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14D::xw).description(szXW_Tensor);
        w.operate_self();
    }

    {
        auto w = writer<Tensor14F>();
        w.description("1x4 tensor in float");
        w.property(szXX, &Tensor14F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14F::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14F::xw).description(szXW_Tensor);
    }

    {
        auto w = writer<Tensor14I>();
        w.description("1x4 tensor in integer");
        w.property(szXX, &Tensor14I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14I::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14I::xw).description(szXW_Tensor);
    }

    {
        auto w = writer<Tensor14U>();
        w.description("1x4 tensor in unsigned integer");
        w.property(szXX, &Tensor14U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14U::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14U::xw).description(szXW_Tensor);
    }

    {
        auto w = writer<Tensor21D>();
        w.description("2x1 tensor in double");
        w.property(szXX, &Tensor21D::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21D::yx).description(szYX_Tensor);
        w.operate_self();
    }

    {
        auto w = writer<Tensor21F>();
        w.description("2x1 tensor in float");
        w.property(szXX, &Tensor21F::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21F::yx).description(szYX_Tensor);
    }

    {
        auto w = writer<Tensor21I>();
        w.description("2x1 tensor in integer");
        w.property(szXX, &Tensor21I::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21I::yx).description(szYX_Tensor);
    }

    {
        auto w = writer<Tensor21U>();
        w.description("2x1 tensor in unsigned integer");
        w.property(szXX, &Tensor21U::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21U::yx).description(szYX_Tensor);
    }

    {
        auto w = writer<Tensor22D>();
        w.description("2x2 tensor in double");
        w.property(szXX, &Tensor22D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22D::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22D::yy).description(szYY_Tensor);
        w.operate_self();
    }

    {
        auto w = writer<Tensor22F>();
        w.description("2x2 tensor in float");
        w.property(szXX, &Tensor22F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22F::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22F::yy).description(szYY_Tensor);
    }

    {
        auto w = writer<Tensor22I>();
        w.description("2x2 tensor in integer");
        w.property(szXX, &Tensor22I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22I::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22I::yy).description(szYY_Tensor);
    }

    {
        auto w = writer<Tensor22U>();
        w.description("2x2 tensor in unsigned integer");
        w.property(szXX, &Tensor22U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22U::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22U::yy).description(szYY_Tensor);
    }

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

    {
        auto w = writer<Tensor31D>();
        w.description("3x1 tensor in double");
        w.property(szXX, &Tensor31D::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31D::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31D::zx).description(szZX_Tensor);
        w.operate_self();
    }

    {
        auto w = writer<Tensor31F>();
        w.description("3x1 tensor in float");
        w.property(szXX, &Tensor31F::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31F::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31F::zx).description(szZX_Tensor);
    }

    {
        auto w = writer<Tensor31I>();
        w.description("3x1 tensor in integer");
        w.property(szXX, &Tensor31I::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31I::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31I::zx).description(szZX_Tensor);
    }

    {
        auto w = writer<Tensor31U>();
        w.description("3x1 tensor in unsigned integer");
        w.property(szXX, &Tensor31U::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31U::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31U::zx).description(szZX_Tensor);
    }

    {
        auto w = writer<Tensor32D>();
        w.description("3x2 tensor in double");
        w.property(szXX, &Tensor32D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32D::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32D::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32D::zy).description(szZY_Tensor);
        w.operate_self();
    }

    {
        auto w = writer<Tensor32F>();
        w.description("3x2 tensor in float");
        w.property(szXX, &Tensor32F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32F::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32F::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32F::zy).description(szZY_Tensor);
    }

    {
        auto w = writer<Tensor32I>();
        w.description("3x2 tensor in integer");
        w.property(szXX, &Tensor32I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32I::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32I::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32I::zy).description(szZY_Tensor);
    }

    {
        auto w = writer<Tensor32U>();
        w.description("3x2 tensor in unsigned integer");
        w.property(szXX, &Tensor32U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32U::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32U::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32U::zy).description(szZY_Tensor);
    }

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
    }

    {
        auto w = writer<Tensor33F>();
        w.description("3x3 tensor in float");
        w.property(szXX, &Tensor33F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor33F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor33F::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor33F::yx).description(szYY_Tensor);
        w.property(szYY, &Tensor33F::yy).description(szYZ_Tensor);
        w.property(szYZ, &Tensor33F::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor33F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor33F::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor33F::zz).description(szZZ_Tensor);
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

    {
        auto w = writer<Tensor41D>();
        w.description("4x1 tensor in double");
        w.property(szXX, &Tensor41D::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41D::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41D::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41D::wx).description(szWX_Tensor);
        w.operate_self();
    }

    {
        auto w = writer<Tensor41F>();
        w.description("4x1 tensor in float");
        w.property(szXX, &Tensor41F::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41F::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41F::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41F::wx).description(szWX_Tensor);
    }

    {
        auto w = writer<Tensor41I>();
        w.description("4x1 tensor in integer");
        w.property(szXX, &Tensor41I::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41I::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41I::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41I::wx).description(szWX_Tensor);
    }

    {
        auto w = writer<Tensor41U>();
        w.description("4x1 tensor in unsigned integer");
        w.property(szXX, &Tensor41U::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41U::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41U::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41U::wx).description(szWX_Tensor);
    }

    {
        auto w = writer<Tensor42D>();
        w.description("4x2 tensor in double");
        w.property(szXX, &Tensor42D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42D::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42D::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42D::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42D::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42D::wy).description(szWY_Tensor);
        w.operate_self();
    }

    {
        auto w = writer<Tensor42F>();
        w.description("4x2 tensor in float");
        w.property(szXX, &Tensor42F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42F::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42F::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42F::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42F::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42F::wy).description(szWY_Tensor);
    }

    {
        auto w = writer<Tensor42I>();
        w.description("4x2 tensor in integer");
        w.property(szXX, &Tensor42I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42I::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42I::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42I::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42I::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42I::wy).description(szWY_Tensor);
    }

    {
        auto w = writer<Tensor42U>();
        w.description("4x2 tensor in unsigned integer");
        w.property(szXX, &Tensor42U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42U::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42U::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42U::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42U::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42U::wy).description(szWY_Tensor);
    }

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

YQ_INVOKE(reg_tensor_math();)


#include "vector/Tensor11.hxx"
#include "vector/Tensor12.hxx"
#include "vector/Tensor13.hxx"
#include "vector/Tensor14.hxx"

#include "vector/Tensor21.hxx"
#include "vector/Tensor22.hxx"
#include "vector/Tensor23.hxx"
#include "vector/Tensor24.hxx"

#include "vector/Tensor31.hxx"
#include "vector/Tensor32.hxx"
#include "vector/Tensor33.hxx"
#include "vector/Tensor34.hxx"

#include "vector/Tensor41.hxx"
#include "vector/Tensor42.hxx"
#include "vector/Tensor43.hxx"
#include "vector/Tensor44.hxx"

