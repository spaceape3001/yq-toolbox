////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Spinor2.hpp"
#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Spinor2.hxx"

YQ_TYPE_IMPLEMENT(yq::Spinor2D)
YQ_TYPE_IMPLEMENT(yq::Spinor2F)


using namespace yq;

template <typename T>
void    print_spinor2(Stream& str, const Spinor2<T>& v)
{
    str << "(" << v.w << "," << v.z << ")";
}

static std::string_view write_spinor2d(const Spinor2D& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg", kMaxDoubleDigits, v.w, kMaxDoubleDigits, v.z);
    return std::string_view(buffer, n);
}

static std::string_view write_spinor2f(const Spinor2F& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g", kMaxFloatDigits, v.w, kMaxFloatDigits, v.z);
    return std::string_view(buffer, n);
}

static bool  parse_spinor2d(Spinor2D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto w = to_double(bits[0]);
    auto z = to_double(bits[1]);
    if(!(z && w)) 
        return false;
    v   = Spinor2D(*w, *z);
    return true;
}

static bool  parse_spinor2f(Spinor2F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto w = to_float(bits[0]);
    auto z = to_float(bits[1]);
    if(!(z && w)) 
        return false;
    v   = Spinor2F(*w, *z);
    return true;
}


static void reg_spinor2()
{
    {
        auto w = writer<Spinor2D>();
        w.description("2D Spinor in double");
        w.property(szW, &Spinor2D::w).description(szW_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Spinor2D::z).description(szZ_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        //w.operate_with<Vector3D>(); // DISABLED due to bad template expansion causing weird compiler substitution issues
        w.print<print_spinor2<double>>();
        w.format<write_spinor2d>();
        w.parse<parse_spinor2d>();
    }

    {
        auto w = writer<double>();
        w.operate_with<Spinor2D>();
    }

    {
        auto w = writer<Spinor2F>();
        w.description("2D Spinor in float");
        w.property(szW, &Spinor2F::w).description(szW_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.property(szZ, &Spinor2F::z).description(szZ_Quaternion).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        //w.operate_with<Vector3F>(); // DISABLED due to bad template expansion causing weird compiler substitution issues
        w.print<print_spinor2<float>>();
        w.format<write_spinor2f>();
        w.parse<parse_spinor2f>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Spinor2F>();
    }

}

YQ_INVOKE(reg_spinor2();)

