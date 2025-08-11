////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AxBox4.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "AxBox4.hxx"

YQ_TYPE_IMPLEMENT(yq::AxBox4D)
YQ_TYPE_IMPLEMENT(yq::AxBox4F)
YQ_TYPE_IMPLEMENT(yq::AxBox4I)
YQ_TYPE_IMPLEMENT(yq::AxBox4U)

using namespace yq;

template <typename T>
void    print_axbox4(Stream& str, const AxBox4<T>& v)
{
    as_stream(str, v);
}

static std::string_view write_axbox4d(const AxBox4D& v)
{
    static thread_local char    buffer [ 512 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg,%.*lg,%.*lg,%.*lg,%.*lg,%.*lg,%.*lg", 
        kMaxDoubleDigits, v.lo.x, 
        kMaxDoubleDigits, v.lo.y, 
        kMaxDoubleDigits, v.lo.z, 
        kMaxDoubleDigits, v.lo.w,
        kMaxDoubleDigits, v.hi.x, 
        kMaxDoubleDigits, v.hi.y, 
        kMaxDoubleDigits, v.hi.z, 
        kMaxDoubleDigits, v.hi.w
    );
    return std::string_view(buffer, n);
}

static std::string_view write_axbox4f(const AxBox4F& v)
{
    static thread_local char    buffer [ 512 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g,%.*g,%.*g,%.*g,%.*g,%.*g,%.*g", 
        kMaxFloatDigits, v.lo.x, 
        kMaxFloatDigits, v.lo.y, 
        kMaxFloatDigits, v.lo.z, 
        kMaxFloatDigits, v.lo.w,
        kMaxFloatDigits, v.hi.x, 
        kMaxFloatDigits, v.hi.y, 
        kMaxFloatDigits, v.hi.z, 
        kMaxFloatDigits, v.hi.w
    );
    return std::string_view(buffer, n);
}

static std::string_view write_axbox4i(const AxBox4I& v)
{
    static thread_local char    buffer [ 512 ];
    int n = snprintf(buffer, sizeof(buffer), "%i,%i,%i,%i,%i,%i,%i,%i", 
        v.lo.x, 
        v.lo.y, 
        v.lo.z, 
        v.lo.w,
        v.hi.x, 
        v.hi.y, 
        v.hi.z, 
        v.hi.w
    );
    return std::string_view(buffer, n);
}

static std::string_view write_axbox4u(const AxBox4U& v)
{
    static thread_local char    buffer [ 512 ];
    int n = snprintf(buffer, sizeof(buffer), "%u,%u,%u,%u,%u,%u,%u,%u", 
        v.lo.x, 
        v.lo.y, 
        v.lo.z, 
        v.lo.w,
        v.hi.x, 
        v.hi.y, 
        v.hi.z, 
        v.hi.w
    );
    return std::string_view(buffer, n);
}


static bool  parse_axbox4d(AxBox4D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 8)
        return false;
    auto lx = to_double(bits[0]);
    auto ly = to_double(bits[1]);
    auto lz = to_double(bits[2]);
    auto lw = to_double(bits[3]);
    auto hx = to_double(bits[4]);
    auto hy = to_double(bits[5]);
    auto hz = to_double(bits[6]);
    auto hw = to_double(bits[7]);
    if(!(lx && ly && lz && lw && hx && hy && hz && hw)) 
        return false;
    v   = AxBox4D(Vector4D(*lx, *ly, *lz, *lw),Vector4D(*hx, *hy, *hz, *hw));
    return true;
}

static bool  parse_axbox4f(AxBox4F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 8)
        return false;
    auto lx = to_float(bits[0]);
    auto ly = to_float(bits[1]);
    auto lz = to_float(bits[2]);
    auto lw = to_float(bits[3]);
    auto hx = to_float(bits[4]);
    auto hy = to_float(bits[5]);
    auto hz = to_float(bits[6]);
    auto hw = to_float(bits[7]);
    if(!(lx && ly && lz && lw && hx && hy && hz && hw)) 
        return false;
    v   = AxBox4F(Vector4F(*lx, *ly, *lz, *lw),Vector4F(*hx, *hy, *hz, *hw));
    return true;
}

static bool  parse_axbox4i(AxBox4I& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 8)
        return false;
    auto lx = to_integer(bits[0]);
    auto ly = to_integer(bits[1]);
    auto lz = to_integer(bits[2]);
    auto lw = to_integer(bits[3]);
    auto hx = to_integer(bits[4]);
    auto hy = to_integer(bits[5]);
    auto hz = to_integer(bits[6]);
    auto hw = to_integer(bits[7]);
    if(!(lx && ly && lz && lw && hx && hy && hz && hw)) 
        return false;
    v   = AxBox4I(Vector4I(*lx, *ly, *lz, *lw),Vector4I(*hx, *hy, *hz, *hw));
    return true;
}

static bool  parse_axbox4u(AxBox4U& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 8)
        return false;
    auto lx = to_unsigned(bits[0]);
    auto ly = to_unsigned(bits[1]);
    auto lz = to_unsigned(bits[2]);
    auto lw = to_unsigned(bits[3]);
    auto hx = to_unsigned(bits[4]);
    auto hy = to_unsigned(bits[5]);
    auto hz = to_unsigned(bits[6]);
    auto hw = to_unsigned(bits[7]);
    if(!(lx && ly && lz && lw && hx && hy && hz && hw)) 
        return false;
    v   = AxBox4U(Vector4U(*lx, *ly, *lz, *lw),Vector4U(*hx, *hy, *hz, *hw));
    return true;
}

static void reg_axbox4()
{
    {
        auto w = writer<AxBox4D>();
        w.description("4D Axially Aligned Bounding Box in double");
        w.property(szCenter, &AxBox4D::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4D::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4D::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4D::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4D::lo).description(szLow_Box);
        w.property(szValid, &AxBox4D::valid).description(szValid_Box);
        w.property(szW, &AxBox4D::w_range).description(szW_Box);
        w.property(szX, &AxBox4D::x_range).description(szX_Box);
        w.property(szY, &AxBox4D::y_range).description(szY_Box);
        w.property(szZ, &AxBox4D::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4D::*)(const Vector4D&) const) &AxBox4D::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4D::*)(const AxBox4D&) const) &AxBox4D::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4D::*)(const AxBox4D&) const) &AxBox4D::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox4D::project).description(szProject_Box);
        w.method(szUnproject, &AxBox4D::unproject).description(szUnproject_Box);
        w.parse<parse_axbox4d>();
        w.print<print_axbox4<double>>();
        w.format<write_axbox4d>();
    }

    {
        auto w = writer<AxBox4F>();
        w.description("4D Axially Aligned Bounding Box in float");
        w.property(szCenter, &AxBox4F::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4F::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4F::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4F::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4F::lo).description(szLow_Box);
        w.property(szValid, &AxBox4F::valid).description(szValid_Box);
        w.property(szW, &AxBox4F::w_range).description(szW_Box);
        w.property(szX, &AxBox4F::x_range).description(szX_Box);
        w.property(szY, &AxBox4F::y_range).description(szY_Box);
        w.property(szZ, &AxBox4F::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4F::*)(const Vector4F&) const) &AxBox4F::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4F::*)(const AxBox4F&) const) &AxBox4F::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4F::*)(const AxBox4F&) const) &AxBox4F::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox4F::project).description(szProject_Box);
        w.method(szUnproject, &AxBox4F::unproject).description(szUnproject_Box);
        w.parse<parse_axbox4f>();
        w.print<print_axbox4<float>>();
        w.format<write_axbox4f>();
    }
    
    {
        auto w = writer<AxBox4I>();
        w.description("4D Axially Aligned Bounding Box in integer");
        w.property(szCenter, &AxBox4I::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4I::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4I::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4I::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4I::lo).description(szLow_Box);
        w.property(szValid, &AxBox4I::valid).description(szValid_Box);
        w.property(szW, &AxBox4I::w_range).description(szW_Box);
        w.property(szX, &AxBox4I::x_range).description(szX_Box);
        w.property(szY, &AxBox4I::y_range).description(szY_Box);
        w.property(szZ, &AxBox4I::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4I::*)(const Vector4I&) const) &AxBox4I::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4I::*)(const AxBox4I&) const) &AxBox4I::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4I::*)(const AxBox4I&) const) &AxBox4I::overlaps).description(szOverlaps_Box_Box);
        w.parse<parse_axbox4i>();
        w.print<print_axbox4<int>>();
        w.format<write_axbox4i>();
    }
    
    {
        auto w = writer<AxBox4U>();
        w.description("4D Axially Aligned Bounding Box in unsigned integers");
        w.property(szCenter, &AxBox4U::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4U::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4U::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4U::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4U::lo).description(szLow_Box);
        w.property(szValid, &AxBox4U::valid).description(szValid_Box);
        w.property(szW, &AxBox4U::w_range).description(szW_Box);
        w.property(szX, &AxBox4U::x_range).description(szX_Box);
        w.property(szY, &AxBox4U::y_range).description(szY_Box);
        w.property(szZ, &AxBox4U::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4U::*)(const Vector4U&) const) &AxBox4U::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4U::*)(const AxBox4U&) const) &AxBox4U::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4U::*)(const AxBox4U&) const) &AxBox4U::overlaps).description(szOverlaps_Box_Box);
        w.parse<parse_axbox4u>();
        w.print<print_axbox4<unsigned>>();
        w.format<write_axbox4u>();
    }
}

YQ_INVOKE(reg_axbox4();)
