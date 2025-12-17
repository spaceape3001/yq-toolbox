////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector2.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/units.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/math/utility.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor21.hpp>
#include <yq/tensor/Tensor22.hpp>
#include <yq/tensor/Tensor23.hpp>
#include <yq/tensor/Tensor24.hpp>
#include <yq/vector/Bivector2.hpp>
#include <yq/vector/Multivector2.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Vector2.hxx"
#include "Multivector2.hxx"

YQ_TYPE_IMPLEMENT(yq::Vector2D)
YQ_TYPE_IMPLEMENT(yq::Vector2F)
YQ_TYPE_IMPLEMENT(yq::Vector2I)
YQ_TYPE_IMPLEMENT(yq::Vector2U)
YQ_TYPE_IMPLEMENT(yq::Vector2M)
YQ_TYPE_IMPLEMENT(yq::Vector2CM)
YQ_TYPE_IMPLEMENT(yq::Vector2MM)

namespace yq {
    Vector2I    iround(const Vector2D&v)
    {
        return { iround(v.x), iround(v.y) };
    }
}

using namespace yq;

template <typename T>
Vector2<T>    construct_vector2(T x, T y)
{
    return Vector2<T>(x,y);
}

template <typename T>
void    print_vector2(Stream& str, const Vector2<T>& v)
{
    str << "(" << v.x << "," << v.y << ")";
}

static std::string_view write_vector2m(const Vector2M& v)
{
    static thread_local char    buffer [ 128 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg", kMaxDoubleDigits, v.x.value, kMaxDoubleDigits, v.y.value);
    return std::string_view(buffer, n);
}

static std::string_view write_vector2cm(const Vector2CM& v)
{
    static thread_local char    buffer [ 128 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg", kMaxDoubleDigits, v.x.value, kMaxDoubleDigits, v.y.value);
    return std::string_view(buffer, n);
}

static std::string_view write_vector2mm(const Vector2MM& v)
{
    static thread_local char    buffer [ 128 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg", kMaxDoubleDigits, v.x.value, kMaxDoubleDigits, v.y.value);
    return std::string_view(buffer, n);
}

static bool  parse_vector2m(Vector2M& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_double(bits[0]);
    auto y = to_double(bits[1]);
    if(!(x && y)) 
        return false;
    v   = Vector2M(*x, *y);
    return true;
}

static bool  parse_vector2cm(Vector2CM& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_double(bits[0]);
    auto y = to_double(bits[1]);
    if(!(x && y)) 
        return false;
    v   = Vector2CM(*x, *y);
    return true;
}

static bool  parse_vector2mm(Vector2MM& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_double(bits[0]);
    auto y = to_double(bits[1]);
    if(!(x && y)) 
        return false;
    v   = Vector2MM(*x, *y);
    return true;
}

static void reg_vector2()
{
    {
        auto w = writer<Vector2D>();
        w.description("2D vector in double");
        w.property(szLength², &Vector2D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2D::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector2D::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.method(szZ, &Vector2D::z).description(szZ_Vector2);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector2D>();
        w.operate_with<Multivector2D>();
        w.operate_with<Tensor21D>(Operator::Multiply);
        w.operate_with<Tensor22D>(Operator::Multiply);
        w.operate_with<Tensor23D>(Operator::Multiply);
        w.operate_with<Tensor24D>(Operator::Multiply);
        w.format<math_io::format<Vector2D>>();
        w.parse<math_io::parse<Vector2D>>();
        w.print<math_io::print<Vector2D>>();
        w.constructor(construct_vector2<double>);
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
        w.property(szX, &Vector2F::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector2F::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.method(szZ, &Vector2F::z).description(szZ_Vector2);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector2F>();
        w.operate_with<Multivector2F>();
        w.operate_with<Tensor21F>(Operator::Multiply);
        w.operate_with<Tensor22F>(Operator::Multiply);
        w.operate_with<Tensor23F>(Operator::Multiply);
        w.operate_with<Tensor24F>(Operator::Multiply);
        w.format<math_io::format<Vector2F>>();
        w.parse<math_io::parse<Vector2F>>();
        w.print<math_io::print<Vector2F>>();
        w.constructor(construct_vector2<float>);
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Vector2F>();
    }

    {
        auto w = writer<Vector2I>();
        w.description("2D vector in integer");
        w.property(szLength², &Vector2I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector2I::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector2I::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.method(szZ, &Vector2I::z).description(szZ_Vector2);
        w.operate_self({Operator::Add, Operator::Subtract});
        w.format<math_io::format<Vector2I>>();
        w.parse<math_io::parse<Vector2I>>();
        w.print<math_io::print<Vector2I>>();
        w.constructor(construct_vector2<int>);
    }

    {
        auto w = writer<Vector2U>();
        w.description("2D vector in unsigned integer");
        w.property(szLength², &Vector2U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector2U::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector2U::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        w.method(szZ, &Vector2U::z).description(szZ_Vector2);
        w.operate_self({Operator::Add, Operator::Subtract});
        w.format<math_io::format<Vector2U>>();
        w.parse<math_io::parse<Vector2U>>();
        w.print<math_io::print<Vector2U>>();
        w.constructor(construct_vector2<unsigned>);
    }

    {
        auto w = writer<Vector2M>();
        w.description("2D vector in meters");
        w.property(szLength², &Vector2M::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2M::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2M::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector2M::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        //w.method(szZ, &Vector2M::z).description(szZ_Vector2);
        w.operate_self();
        //w.operate_with<double>();
        w.print<print_vector2<unit::Meter>>();
        w.format<write_vector2m>();
        w.parse<parse_vector2m>();
        w.constructor(construct_vector2<unit::Meter>);
    }

    {
        auto w = writer<Vector2CM>();
        w.description("2D vector in centimeters");
        w.property(szLength², &Vector2CM::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2CM::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2CM::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector2CM::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        //w.method(szZ, &Vector2CM::z).description(szZ_Vector2);
        w.operate_self();
        //w.operate_with<double>();
        w.print<print_vector2<unit::Centimeter>>();
        w.format<write_vector2cm>();
        w.parse<parse_vector2cm>();
        w.constructor(construct_vector2<unit::Centimeter>);
    }

    {
        auto w = writer<Vector2MM>();
        w.description("2D vector in millimeters");
        w.property(szLength², &Vector2MM::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2MM::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2MM::x).description(szX_Vector).tag(kTag_Save).tag(kTag_Print);
        w.property(szY, &Vector2MM::y).description(szY_Vector).tag(kTag_Save).tag(kTag_Print);
        //w.method(szZ, &Vector2MM::z).description(szZ_Vector2);
        w.operate_self();
        //w.operate_with<double>();
        w.print<print_vector2<unit::Millimeter>>();
        w.format<write_vector2mm>();
        w.parse<parse_vector2mm>();
        w.constructor(construct_vector2<unit::Millimeter>);
    }
}

namespace {
    YQ_INVOKE(reg_vector2();)
}
