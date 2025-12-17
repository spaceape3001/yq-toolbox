////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector1.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor11.hpp>
#include <yq/tensor/Tensor12.hpp>
#include <yq/tensor/Tensor13.hpp>
#include <yq/tensor/Tensor14.hpp>
#include <yq/vector/Multivector1.hpp>
#include <yq/vector/Vector1.hpp>

#include "Vector1.hxx"

YQ_TYPE_IMPLEMENT(yq::Vector1D)
YQ_TYPE_IMPLEMENT(yq::Vector1F)
YQ_TYPE_IMPLEMENT(yq::Vector1I)
YQ_TYPE_IMPLEMENT(yq::Vector1U)

namespace yq {
    Vector1I    iround(const Vector1D&v)
    {
        return { iround(v.x) };
    }
}

using namespace yq;

template <typename T>
Vector1<T>    construct_vector1(T x)
{
    return Vector1<T>(x);
}

template <typename T>
void    print_vector1(Stream& str, const Vector1<T>& v)
{
    str << "(" << v.x << ")";
}

static void reg_vector1()
{

    {
        auto w = writer<Vector1D>();
        w.description("1D vector in double");
        w.property(szLength, &Vector1D::length).description(szLength_Vector).alias(szLen);
        w.property(szLength², &Vector1D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1D::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Multivector1D>();
        w.operate_with<Tensor11D>(Operator::Multiply);
        w.operate_with<Tensor12D>(Operator::Multiply);
        w.operate_with<Tensor13D>(Operator::Multiply);
        w.operate_with<Tensor14D>(Operator::Multiply);
        w.constructor(construct_vector1<double>);
        w.format<math_io::format<Vector1D>>();
        w.parse<math_io::parse<Vector1D>>();
        w.print<math_io::print<Vector1D>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Vector1D>();
    }

    {
        auto w = writer<Vector1F>();
        w.description("1D vector in float");
        w.property(szLength, &Vector1F::length).description(szLength_Vector).alias(szLen);
        w.property(szLength², &Vector1F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1F::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Multivector1F>();
        w.operate_with<Tensor11F>(Operator::Multiply);
        w.operate_with<Tensor12F>(Operator::Multiply);
        w.operate_with<Tensor13F>(Operator::Multiply);
        w.operate_with<Tensor14F>(Operator::Multiply);
        w.constructor(construct_vector1<float>);
        w.format<math_io::format<Vector1F>>();
        w.parse<math_io::parse<Vector1F>>();
        w.print<math_io::print<Vector1F>>();
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Vector1F>();
    }

    {
        auto w = writer<Vector1I>();
        w.description("1D vector in integer");
        w.property(szLength², &Vector1I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1I::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self({ Operator::Add, Operator::Subtract });
        w.constructor(construct_vector1<int>);
        w.format<math_io::format<Vector1I>>();
        w.parse<math_io::parse<Vector1I>>();
        w.print<math_io::print<Vector1I>>();
    }

    {
        auto w = writer<Vector1U>();
        w.description("1D vector in unsigned integer");
        w.property(szLength², &Vector1U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1U::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self({ Operator::Add, Operator::Subtract });
        w.constructor(construct_vector1<unsigned>);
        w.format<math_io::format<Vector1U>>();
        w.parse<math_io::parse<Vector1U>>();
        w.print<math_io::print<Vector1U>>();
    }
}

namespace {
    YQ_INVOKE(reg_vector1();)
}
