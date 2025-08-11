////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AxBox1.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "AxBox1.hxx"

YQ_TYPE_IMPLEMENT(yq::AxBox1D)
YQ_TYPE_IMPLEMENT(yq::AxBox1F)
YQ_TYPE_IMPLEMENT(yq::AxBox1I)
YQ_TYPE_IMPLEMENT(yq::AxBox1U)

using namespace yq;

template <typename T>
void    print_axbox1(Stream& str, const AxBox1<T>& v)
{
    as_stream(str, v);
}

static std::string_view write_axbox1d(const AxBox1D& v)
{
    static thread_local char    buffer [ 128 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg", 
        kMaxDoubleDigits, v.lo.x, 
        kMaxDoubleDigits, v.hi.x
    );
    return std::string_view(buffer, n);
}

static std::string_view write_axbox1f(const AxBox1F& v)
{
    static thread_local char    buffer [ 128 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g", 
        kMaxFloatDigits, v.lo.x, 
        kMaxFloatDigits, v.hi.x
    );
    return std::string_view(buffer, n);
}

static std::string_view write_axbox1i(const AxBox1I& v)
{
    static thread_local char    buffer [ 128 ];
    int n = snprintf(buffer, sizeof(buffer), "%i,%i", 
        v.lo.x, 
        v.hi.x
    );
    return std::string_view(buffer, n);
}

static std::string_view write_axbox1u(const AxBox1U& v)
{
    static thread_local char    buffer [ 128 ];
    int n = snprintf(buffer, sizeof(buffer), "%u,%u", 
        v.lo.x, 
        v.hi.x
    );
    return std::string_view(buffer, n);
}

static bool  parse_axbox1d(AxBox1D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto lx = to_double(bits[0]);
    auto hx = to_double(bits[1]);
    if(!(lx && hx)) 
        return false;
    v   = AxBox1D(Vector1D(*lx),Vector1D(*hx));
    return true;
}

static bool  parse_axbox1f(AxBox1F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto lx = to_float(bits[0]);
    auto hx = to_float(bits[1]);
    if(!(lx && hx)) 
        return false;
    v   = AxBox1F(Vector1F(*lx),Vector1F(*hx));
    return true;
}

static bool  parse_axbox1i(AxBox1I& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto lx = to_integer(bits[0]);
    auto hx = to_integer(bits[1]);
    if(!(lx && hx)) 
        return false;
    v   = AxBox1I(Vector1I(*lx),Vector1I(*hx));
    return true;
}

static bool  parse_axbox1u(AxBox1U& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto lx = to_unsigned(bits[0]);
    auto hx = to_unsigned(bits[1]);
    if(!(lx && hx)) 
        return false;
    v   = AxBox1U(Vector1U(*lx),Vector1U(*hx));
    return true;
}

static void reg_axbox1()
{

    {
        auto w = writer<AxBox1D>();
        w.description("1D Axially Aligned Bounding Box in double");
        w.property(szCenter, &AxBox1D::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1D::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox1D::hi).description(szHigh_Box);
        w.property(szLow, &AxBox1D::lo).description(szLow_Box);
        w.property(szValid, &AxBox1D::valid).description(szValid_Box);
        w.property(szX, &AxBox1D::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1D::*)(const Vector1D&) const) &AxBox1D::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1D::*)(const AxBox1D&) const) &AxBox1D::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1D::*)(const AxBox1D&) const) &AxBox1D::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox1D::project).description(szProject_Box);
        w.method(szUnproject, &AxBox1D::unproject).description(szUnproject_Box);
        w.parse<parse_axbox1d>();
        w.print<print_axbox1<double>>();
        w.format<write_axbox1d>();
    }

    {
        auto w = writer<AxBox1F>();
        w.description("1D Axially Aligned Bounding Box in float");
        w.property(szCenter, &AxBox1F::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1F::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox1F::hi).description(szHigh_Box);
        w.property(szLow, &AxBox1F::lo).description(szLow_Box);
        w.property(szValid, &AxBox1F::valid).description(szValid_Box);
        w.property(szX, &AxBox1F::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1F::*)(const Vector1F&) const) &AxBox1F::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1F::*)(const AxBox1F&) const) &AxBox1F::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1F::*)(const AxBox1F&) const) &AxBox1F::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox1F::project).description(szProject_Box);
        w.method(szUnproject, &AxBox1F::unproject).description(szUnproject_Box);
        w.parse<parse_axbox1f>();
        w.print<print_axbox1<float>>();
        w.format<write_axbox1f>();
    }

    {
        auto w = writer<AxBox1I>();
        w.description("1D Axially Aligned Bounding Box in integer");
        w.property(szCenter, &AxBox1I::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1I::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox1I::hi).description(szHigh_Box);
        w.property(szLow, &AxBox1I::lo).description(szLow_Box);
        w.property(szValid, &AxBox1I::valid).description(szValid_Box);
        w.property(szX, &AxBox1I::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1I::*)(const Vector1I&) const) &AxBox1I::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1I::*)(const AxBox1I&) const) &AxBox1I::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1I::*)(const AxBox1I&) const) &AxBox1I::overlaps).description(szOverlaps_Box_Box);
        w.parse<parse_axbox1i>();
        w.print<print_axbox1<int>>();
        w.format<write_axbox1i>();
    }

    {
        auto w = writer<AxBox1U>();
        w.description("1D Axially Aligned Bounding Box in unsigned integers");
        w.property(szCenter, &AxBox1U::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1U::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox1U::lo).description(szLow_Box);
        w.property(szHigh, &AxBox1U::hi).description(szHigh_Box);
        w.property(szValid, &AxBox1U::valid).description(szValid_Box);
        w.property(szX, &AxBox1U::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1U::*)(const Vector1U&) const) &AxBox1U::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1U::*)(const AxBox1U&) const) &AxBox1U::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1U::*)(const AxBox1U&) const) &AxBox1U::overlaps).description(szOverlaps_Box_Box);
        w.parse<parse_axbox1u>();
        w.print<print_axbox1<unsigned>>();
        w.format<write_axbox1u>();
    }
}

YQ_INVOKE(reg_axbox1();)
