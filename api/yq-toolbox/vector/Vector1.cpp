////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector1.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/vector/Multivector1.hpp>

#include "Vector1.hxx"

YQ_TYPE_IMPLEMENT(yq::Vector1D)
YQ_TYPE_IMPLEMENT(yq::Vector1F)
YQ_TYPE_IMPLEMENT(yq::Vector1I)
YQ_TYPE_IMPLEMENT(yq::Vector1U)

using namespace yq;

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
        w.property(szX, &Vector1D::x).description(szX_Vector);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Multivector1D>();
        w.print<print_vector1<double>>();
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
        w.property(szX, &Vector1F::x).description(szX_Vector);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Multivector1F>();
        w.print<print_vector1<float>>();
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Vector1F>();
    }

    {
        auto w = writer<Vector1I>();
        w.description("1D vector in integer");
        w.property(szLength², &Vector1I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1I::x).description(szX_Vector);
        w.operate_self({ Operator::Add, Operator::Subtract });
        w.print<print_vector1<int>>();
    }

    {
        auto w = writer<Vector1U>();
        w.description("1D vector in unsigned integer");
        w.property(szLength², &Vector1U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1U::x).description(szX_Vector);
        w.operate_self({ Operator::Add, Operator::Subtract });
        w.print<print_vector1<unsigned>>();
    }
}

namespace {
    YQ_INVOKE(reg_vector1();)
}
