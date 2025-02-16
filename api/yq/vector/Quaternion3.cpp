////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Quaternion3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Quaternion3.hxx"

YQ_TYPE_IMPLEMENT(yq::Quaternion3D)
YQ_TYPE_IMPLEMENT(yq::Quaternion3F)

using namespace yq;

template <typename T>
void    print_quaternion3(Stream& str, const Quaternion3<T>& v)
{
    str << "(" << v.w << "," << v.x << "," << v.y << "," << v.z << ")";
}


static std::string_view write_quaternion3d(const Quaternion3D& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg,%.*lg,%.*lg", kMaxDoubleDigits, v.w, kMaxDoubleDigits, v.x, kMaxDoubleDigits, v.y, kMaxDoubleDigits, v.z);
    return std::string_view(buffer, n);
}

static std::string_view write_quaternion3f(const Quaternion3F& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g,%.*g,%.*g", kMaxFloatDigits, v.w, kMaxFloatDigits, v.x, kMaxFloatDigits, v.y, kMaxFloatDigits, v.z);
    return std::string_view(buffer, n);
}

static bool  parse_quaternion3d(Quaternion3D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto w = to_double(bits[0]);
    auto x = to_double(bits[1]);
    auto y = to_double(bits[2]);
    auto z = to_double(bits[3]);
    if(!(x && y && z && w)) 
        return false;
    v   = Quaternion3D(*w, *x, *y, *z);
    return true;
}

static bool  parse_quaternion3f(Quaternion3F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto w = to_float(bits[0]);
    auto x = to_float(bits[1]);
    auto y = to_float(bits[2]);
    auto z = to_float(bits[3]);
    if(!(x && y && z && w)) 
        return false;
    v   = Quaternion3F(*w, *x, *y, *z);
    return true;
}


static void reg_quaternion3()
{
    {
        auto w = writer<Quaternion3D>();
        w.description("3D Quaternion in double");
        w.property(szW, &Quaternion3D::w).description(szW_Quaternion);
        w.property(szX, &Quaternion3D::x).description(szX_Quaternion);
        w.property(szY, &Quaternion3D::y).description(szY_Quaternion);
        w.property(szZ, &Quaternion3D::z).description(szZ_Quaternion);
        w.operate_self();
        w.operate_with<double>();
        //w.operate_with<Vector3D>(); // DISABLED due to bad template expansion causing weird compiler substitution issues
        w.print<print_quaternion3<double>>();
        w.format<write_quaternion3d>();
        w.parse<parse_quaternion3d>();
    }

    {
        auto w = writer<double>();
        w.operate_with<Quaternion3D>();
    }

    {
        auto w = writer<Quaternion3F>();
        w.description("3D Quaternion in float");
        w.property(szW, &Quaternion3F::w).description(szW_Quaternion);
        w.property(szX, &Quaternion3F::x).description(szX_Quaternion);
        w.property(szY, &Quaternion3F::y).description(szY_Quaternion);
        w.property(szZ, &Quaternion3F::z).description(szZ_Quaternion);
        w.operate_self();
        w.operate_with<float>();
        //w.operate_with<Vector3F>(); // DISABLED due to bad template expansion causing weird compiler substitution issues
        w.print<print_quaternion3<float>>();
        w.format<write_quaternion3f>();
        w.parse<parse_quaternion3f>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Quaternion3F>();
    }

}

YQ_INVOKE(reg_quaternion3();)
