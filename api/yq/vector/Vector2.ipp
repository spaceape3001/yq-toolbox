////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/utility.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor21.hpp>
#include <yq/tensor/Tensor22.hpp>
#include <yq/tensor/Tensor23.hpp>
#include <yq/tensor/Tensor24.hpp>
#include <yq/vector/Bivector2.hpp>
#include <yq/vector/Multivector2.hpp>
#include <yq/vector/Vector3.hpp>

#include "Vector2.hxx"
#include "Multivector2.hxx"

YQ_TYPE_IMPLEMENT(yq::Vector2D)
YQ_TYPE_IMPLEMENT(yq::Vector2F)
YQ_TYPE_IMPLEMENT(yq::Vector2I)
YQ_TYPE_IMPLEMENT(yq::Vector2U)

namespace yq {
    Vector2I    iround(const Vector2D&v)
    {
        return { iround(v.x), iround(v.y) };
    }
}

using namespace yq;

template <typename T>
void    print_vector2(Stream& str, const Vector2<T>& v)
{
    str << "(" << v.x << "," << v.y << ")";
}

static void reg_vector2()
{
    {
        auto w = writer<Vector2D>();
        w.description("2D vector in double");
        w.property(szLength², &Vector2D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2D::x).description(szX_Vector);
        w.property(szY, &Vector2D::y).description(szY_Vector);
        w.method(szZ, &Vector2D::z).description(szZ_Vector2);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector2D>();
        w.operate_with<Multivector2D>();
        w.operate_with<Tensor21D>(Operator::Multiply);
        w.operate_with<Tensor22D>(Operator::Multiply);
        w.operate_with<Tensor23D>(Operator::Multiply);
        w.operate_with<Tensor24D>(Operator::Multiply);
        w.print<print_vector2<double>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Vector2D>();
    }

    {
        auto w = writer<Vector2F>();
        w.description("2D vector in float");
        w.property(szLength², &Vector2F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2F::x).description(szX_Vector);
        w.property(szY, &Vector2F::y).description(szY_Vector);
        w.method(szZ, &Vector2F::z).description(szZ_Vector2);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector2F>();
        w.operate_with<Multivector2F>();
        w.operate_with<Tensor21F>(Operator::Multiply);
        w.operate_with<Tensor22F>(Operator::Multiply);
        w.operate_with<Tensor23F>(Operator::Multiply);
        w.operate_with<Tensor24F>(Operator::Multiply);
        w.print<print_vector2<float>>();
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Vector2F>();
    }

    {
        auto w = writer<Vector2I>();
        w.description("2D vector in integer");
        w.property(szLength², &Vector2I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector2I::x).description(szX_Vector);
        w.property(szY, &Vector2I::y).description(szY_Vector);
        w.method(szZ, &Vector2I::z).description(szZ_Vector2);
        w.operate_self({Operator::Add, Operator::Subtract});
        w.print<print_vector2<int>>();
    }

    {
        auto w = writer<Vector2U>();
        w.description("2D vector in unsigned integer");
        w.property(szLength², &Vector2U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector2U::x).description(szX_Vector);
        w.property(szY, &Vector2U::y).description(szY_Vector);
        w.method(szZ, &Vector2U::z).description(szZ_Vector2);
        w.operate_self({Operator::Add, Operator::Subtract});
        w.print<print_vector2<unsigned>>();
    }
}

namespace {
    YQ_INVOKE(reg_vector2();)
}
