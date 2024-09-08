////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector4.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/tensor/Tensor41.hpp>
#include <yq-toolbox/tensor/Tensor42.hpp>
#include <yq-toolbox/tensor/Tensor43.hpp>
#include <yq-toolbox/tensor/Tensor44.hpp>
#include <yq-toolbox/vector/Bivector4.hpp>
#include <yq-toolbox/vector/Multivector4.hpp>
#include <yq-toolbox/vector/Quadvector4.hpp>
#include <yq-toolbox/vector/Trivector4.hpp>

#include "Vector4.hxx"
#include "Multivector4.hxx"

YQ_TYPE_IMPLEMENT(yq::Vector4D)
YQ_TYPE_IMPLEMENT(yq::Vector4F)
YQ_TYPE_IMPLEMENT(yq::Vector4I)
YQ_TYPE_IMPLEMENT(yq::Vector4U)

using namespace yq;

template <typename T>
void    print_vector4(Stream& str, const Vector4<T>& v)
{
    str << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
}

static void reg_vector4()
{
    {
        auto w = writer<Vector4D>();
        w.description("4D vector in double");
        w.property(szLength², &Vector4D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector4D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector4D::x).description(szX_Vector);
        w.property(szY, &Vector4D::y).description(szY_Vector);
        w.property(szZ, &Vector4D::z).description(szZ_Vector);
        w.property(szW, &Vector4D::w).description(szW_Vector);
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
        w.print<print_vector4<double>>();
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
        w.property(szX, &Vector4F::x).description(szX_Vector);
        w.property(szY, &Vector4F::y).description(szY_Vector);
        w.property(szZ, &Vector4F::z).description(szZ_Vector);
        w.property(szW, &Vector4F::w).description(szW_Vector);
        w.operate_with<Bivector4F>();
        w.operate_with<Multivector4F>();
        w.operate_with<Quadvector4F>();
        w.operate_with<Trivector4F>();
        w.operate_with<Tensor41F>(Operator::Multiply);
        w.operate_with<Tensor42F>(Operator::Multiply);
        w.operate_with<Tensor43F>(Operator::Multiply);
        w.operate_with<Tensor44F>(Operator::Multiply);
        w.print<print_vector4<float>>();
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Vector4F>();
    }

    {
        auto w = writer<Vector4I>();
        w.description("4D vector in integer");
        w.property(szLength², &Vector4I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector4I::x).description(szX_Vector);
        w.property(szY, &Vector4I::y).description(szY_Vector);
        w.property(szZ, &Vector4I::z).description(szZ_Vector);
        w.property(szW, &Vector4I::w).description(szW_Vector);
        w.print<print_vector4<int>>();
    }

    {
        auto w = writer<Vector4U>();
        w.description("4D vector in unsigned integer");
        w.property(szLength², &Vector4U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector4U::x).description(szX_Vector);
        w.property(szY, &Vector4U::y).description(szY_Vector);
        w.property(szZ, &Vector4U::z).description(szZ_Vector);
        w.property(szW, &Vector4U::w).description(szW_Vector);
        w.print<print_vector4<unsigned>>();
    }
}

namespace {
    YQ_INVOKE(reg_vector4();)
}
