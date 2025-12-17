////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector4.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor41.hpp>
#include <yq/tensor/Tensor42.hpp>
#include <yq/tensor/Tensor43.hpp>
#include <yq/tensor/Tensor44.hpp>
#include <yq/vector/Bivector4.hpp>
#include <yq/vector/Multivector4.hpp>
#include <yq/vector/Quadvector4.hpp>
#include <yq/vector/Trivector4.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Vector4.hxx"
#include "Multivector4.hxx"

YQ_TYPE_IMPLEMENT(yq::Vector4D)
YQ_TYPE_IMPLEMENT(yq::Vector4F)
YQ_TYPE_IMPLEMENT(yq::Vector4I)
YQ_TYPE_IMPLEMENT(yq::Vector4U)

namespace yq {
    Vector4I    iround(const Vector4D&v)
    {
        return { iround(v.x), iround(v.y), iround(v.z), iround(v.w) };
    }
}

using namespace yq;

template <typename T>
Vector4<T>    construct_vector4(T x, T y, T z, T w)
{
    return Vector4<T>(x,y,z,w);
}

static void reg_vector4()
{
    {
        auto w = writer<Vector4D>();
        w.description("4D vector in double");
        w.property(szLength², &Vector4D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector4D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector4D::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector4D::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Vector4D::z).description(szZ_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szW, &Vector4D::w).description(szW_Vector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self({ Operator::Add, Operator::Subtract });
        w.operate_with<double>();
        w.operate_with<Bivector4D>();
        w.operate_with<Multivector4D>();
        w.operate_with<Quadvector4D>();
        w.operate_with<Trivector4D>();
        w.operate_with<Tensor41D>(Operator::Multiply);
        w.operate_with<Tensor42D>(Operator::Multiply);
        w.operate_with<Tensor43D>(Operator::Multiply);
        w.operate_with<Tensor44D>(Operator::Multiply);
        w.print<math_io::print<Vector4D>>();
        w.format<math_io::format<Vector4D>>();
        w.parse<math_io::parse<Vector4D>>();
        w.constructor(construct_vector4<double>);
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Vector4D>();
    }

    {
        auto w = writer<Vector4F>();
        w.description("4D vector in float");
        w.property(szLength², &Vector4F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector4F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector4F::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector4F::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Vector4F::z).description(szZ_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szW, &Vector4F::w).description(szW_Vector).tag(kTag_Save).tag(kTag_Print);
        w.operate_with<Bivector4F>();
        w.operate_with<Multivector4F>();
        w.operate_with<Quadvector4F>();
        w.operate_with<Trivector4F>();
        w.operate_with<Tensor41F>(Operator::Multiply);
        w.operate_with<Tensor42F>(Operator::Multiply);
        w.operate_with<Tensor43F>(Operator::Multiply);
        w.operate_with<Tensor44F>(Operator::Multiply);
        w.print<math_io::print<Vector4F>>();
        w.format<math_io::format<Vector4F>>();
        w.parse<math_io::parse<Vector4F>>();
        w.constructor(construct_vector4<float>);
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Vector4F>();
    }

    {
        auto w = writer<Vector4I>();
        w.description("4D vector in integer");
        w.property(szLength², &Vector4I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector4I::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector4I::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Vector4I::z).description(szZ_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szW, &Vector4I::w).description(szW_Vector).tag(kTag_Save).tag(kTag_Print);
        w.print<math_io::print<Vector4I>>();
        w.format<math_io::format<Vector4I>>();
        w.parse<math_io::parse<Vector4I>>();
        w.constructor(construct_vector4<int>);
    }
    
    //{
        //auto w = writer<int>();
        //w.operate_with<Vector4I>();
    //}

    {
        auto w = writer<Vector4U>();
        w.description("4D vector in unsigned integer");
        w.property(szLength², &Vector4U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector4U::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector4U::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Vector4U::z).description(szZ_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szW, &Vector4U::w).description(szW_Vector).tag(kTag_Save).tag(kTag_Print);
        w.print<math_io::print<Vector4U>>();
        w.format<math_io::format<Vector4U>>();
        w.parse<math_io::parse<Vector4U>>();
        w.constructor(construct_vector4<unsigned>);
    }

    //{
        //auto w = writer<unsigned>();
        //w.operate_with<Vector4U>();
    //}

}

namespace {
    YQ_INVOKE(reg_vector4();)
}
