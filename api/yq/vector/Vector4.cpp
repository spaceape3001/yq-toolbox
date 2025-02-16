////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector4.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
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
void    print_vector4(Stream& str, const Vector4<T>& v)
{
    str << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
}

static std::string_view write_vector4d(const Vector4D& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg,%.*lg,%.*lg", kMaxDoubleDigits, v.x, kMaxDoubleDigits, v.y, kMaxDoubleDigits, v.z, kMaxDoubleDigits, v.w);
    return std::string_view(buffer, n);
}

static std::string_view write_vector4f(const Vector4F& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g,%.*g,%.*g", kMaxFloatDigits, v.x, kMaxFloatDigits, v.y, kMaxFloatDigits, v.z, kMaxFloatDigits, v.w);
    return std::string_view(buffer, n);
}

static std::string_view write_vector4i(const Vector4I& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%i,%i,%i,%i", v.x, v.y, v.z, v.w);
    return std::string_view(buffer, n);
}

static std::string_view write_vector4u(const Vector4U& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%u,%u,%u,%u", v.x, v.y, v.z, v.w);
    return std::string_view(buffer, n);
}

static bool  parse_vector4d(Vector4D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto x = to_double(bits[0]);
    auto y = to_double(bits[1]);
    auto z = to_double(bits[2]);
    auto w = to_double(bits[3]);
    if(!(x && y && z && w)) 
        return false;
    v   = Vector4D(*x, *y, *z, *w);
    return true;
}

static bool  parse_vector4f(Vector4F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto x = to_float(bits[0]);
    auto y = to_float(bits[1]);
    auto z = to_float(bits[2]);
    auto w = to_float(bits[3]);
    if(!(x && y && z && w)) 
        return false;
    v   = Vector4F(*x, *y, *z, *w);
    return true;
}

static bool  parse_vector4i(Vector4I& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto x = to_int(bits[0]);
    auto y = to_int(bits[1]);
    auto z = to_int(bits[2]);
    auto w = to_int(bits[3]);
    if(!(x && y && z && w)) 
        return false;
    v   = Vector4I(*x, *y, *z, *w);
    return true;
}

static bool  parse_vector4u(Vector4U& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto x = to_unsigned(bits[0]);
    auto y = to_unsigned(bits[1]);
    auto z = to_unsigned(bits[2]);
    auto w = to_unsigned(bits[3]);
    if(!(x && y && z && w)) 
        return false;
    v   = Vector4U(*x, *y, *z, *w);
    return true;
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
        w.format<write_vector4d>();
        w.parse<parse_vector4d>();
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
        w.format<write_vector4f>();
        w.parse<parse_vector4f>();
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
        w.format<write_vector4i>();
        w.parse<parse_vector4i>();
    }
    
    //{
        //auto w = writer<int>();
        //w.operate_with<Vector4I>();
    //}

    {
        auto w = writer<Vector4U>();
        w.description("4D vector in unsigned integer");
        w.property(szLength², &Vector4U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector4U::x).description(szX_Vector);
        w.property(szY, &Vector4U::y).description(szY_Vector);
        w.property(szZ, &Vector4U::z).description(szZ_Vector);
        w.property(szW, &Vector4U::w).description(szW_Vector);
        w.print<print_vector4<unsigned>>();
        w.format<write_vector4u>();
        w.parse<parse_vector4u>();
    }

    //{
        //auto w = writer<unsigned>();
        //w.operate_with<Vector4U>();
    //}

}

namespace {
    YQ_INVOKE(reg_vector4();)
}
