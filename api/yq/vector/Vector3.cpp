////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vector3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor31.hpp>
#include <yq/tensor/Tensor32.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/tensor/Tensor34.hpp>
#include <yq/vector/Bivector3.hpp>
#include <yq/vector/Multivector3.hpp>
#include <yq/vector/Quaternion3.hpp>
#include <yq/vector/Trivector3.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>
#include <yq/core/Logging.hpp>

#include "Vector3.hxx"
#include "Multivector3.hxx"

YQ_TYPE_IMPLEMENT(yq::Vector3D)
YQ_TYPE_IMPLEMENT(yq::Vector3F)
YQ_TYPE_IMPLEMENT(yq::Vector3I)
YQ_TYPE_IMPLEMENT(yq::Vector3U)

namespace yq {
    Vector3I    iround(const Vector3D&v)
    {
        return { iround(v.x), iround(v.y), iround(v.z) };
    }
}

using namespace yq;

template <typename T>
void    print_vector3(Stream& str, const Vector3<T>& v)
{
    str << "(" << v.x << "," << v.y << "," << v.z << ")";
}

static std::string_view write_vector3d(const Vector3D& v)
{
    static thread_local char    buffer [ 192 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg,%.*lg", kMaxDoubleDigits, v.x, kMaxDoubleDigits, v.y, kMaxDoubleDigits, v.z);
    return std::string_view(buffer, n);
}

static std::string_view write_vector3f(const Vector3F& v)
{
    static thread_local char    buffer [ 192 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g,%.*g", kMaxFloatDigits, v.x, kMaxFloatDigits, v.y, kMaxFloatDigits, v.z);
    return std::string_view(buffer, n);
}

static std::string_view write_vector3i(const Vector3I& v)
{
    static thread_local char    buffer [ 192 ];
    int n = snprintf(buffer, sizeof(buffer), "%i,%i,%i", v.x, v.y, v.z);
    return std::string_view(buffer, n);
}

static std::string_view write_vector3u(const Vector3U& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%u,%u,%u", v.x, v.y, v.z);
    return std::string_view(buffer, n);
}

static bool  parse_vector3d(Vector3D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_double(bits[0]);
    auto y = to_double(bits[1]);
    auto z = to_double(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = Vector3D(*x, *y, *z);
    return true;
}

static bool  parse_vector3f(Vector3F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_float(bits[0]);
    auto y = to_float(bits[1]);
    auto z = to_float(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = Vector3F(*x, *y, *z);
    return true;
}

static bool  parse_vector3i(Vector3I& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_int(bits[0]);
    auto y = to_int(bits[1]);
    auto z = to_int(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = Vector3I(*x, *y, *z);
    return true;
}

static bool  parse_vector3u(Vector3U& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_unsigned(bits[0]);
    auto y = to_unsigned(bits[1]);
    auto z = to_unsigned(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = Vector3U(*x, *y, *z);
    return true;
}

static void reg_vector3()
{
    {
        auto w = writer<Vector3D>();
        w.description("3D vector in double");
        w.property(szLength², &Vector3D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector3D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector3D::x).description(szX_Vector);
        w.property(szY, &Vector3D::y).description(szY_Vector);
        w.property(szZ, &Vector3D::z).description(szZ_Vector);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector3D>();
        w.operate_with<Multivector3D>();
        w.operate_with<Quaternion3D>();
        w.operate_with<Trivector3D>();
        w.operate_with<Tensor31D>(Operator::Multiply);
        w.operate_with<Tensor32D>(Operator::Multiply);
        w.operate_with<Tensor33D>(Operator::Multiply);
        w.operate_with<Tensor34D>(Operator::Multiply);
        w.print<print_vector3<double>>();
        w.format<write_vector3d>();
        w.parse<parse_vector3d>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Vector3D>();
    }

    {
        auto w = writer<Vector3F>();
        w.description("3D vector in float");
        w.property(szLength², &Vector3F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector3F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector3F::x).description(szX_Vector);
        w.property(szY, &Vector3F::y).description(szY_Vector);
        w.property(szZ, &Vector3F::z).description(szZ_Vector);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector3F>();
        w.operate_with<Multivector3F>();
        w.operate_with<Quaternion3F>();
        w.operate_with<Trivector3F>();
        w.operate_with<Tensor31F>(Operator::Multiply);
        w.operate_with<Tensor32F>(Operator::Multiply);
        w.operate_with<Tensor33F>(Operator::Multiply);
        w.operate_with<Tensor34F>(Operator::Multiply);
        w.print<print_vector3<float>>();
        w.format<write_vector3f>();
        w.parse<parse_vector3f>();
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Vector3F>();
    }

    {
        auto w = writer<Vector3I>();
        w.description("3D vector in integer");
        w.property(szLength², &Vector3I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3I::x).description(szX_Vector);
        w.property(szY, &Vector3I::y).description(szY_Vector);
        w.property(szZ, &Vector3I::z).description(szZ_Vector);
        w.print<print_vector3<int>>();
        w.format<write_vector3i>();
        w.parse<parse_vector3i>();
    }

    {
        auto w = writer<Vector3U>();
        w.description("3D vector in unsigned integer");
        w.property(szLength², &Vector3U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3U::x).description(szX_Vector);
        w.property(szY, &Vector3U::y).description(szY_Vector);
        w.property(szZ, &Vector3U::z).description(szZ_Vector);
        w.print<print_vector3<unsigned>>();
        w.format<write_vector3u>();
        w.parse<parse_vector3u>();
    }
}

namespace {
    YQ_INVOKE(reg_vector3();)
}
