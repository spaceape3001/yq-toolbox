////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Size1.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/math/utility.hpp>
#include <yq/meta/Init.hpp>

#include "Size1.hxx"

YQ_TYPE_IMPLEMENT(yq::Size1D)
YQ_TYPE_IMPLEMENT(yq::Size1F)
YQ_TYPE_IMPLEMENT(yq::Size1I)
YQ_TYPE_IMPLEMENT(yq::Size1U)

namespace yq {
    Size1I  iround(const Size1D&v)
    {
        return { iround(v.x) };
    }
}

using namespace yq;

static void reg_size1()
{
    {
        auto w = writer<Size1D>();
        w.description("1D Size in double");
        w.property(szX, &Size1D::x).description(szX_Size).alias(szWidth);
        w.format<math_io::format<Size1D>>();
        w.parse<math_io::parse<Size1D>>();
        w.print<math_io::print<Size1D>>();
        w.operate_with<double>();
    }

    {
        auto w = writer<Size1F>();
        w.description("1D Size in float");
        w.property(szX, &Size1F::x).description(szX_Size).alias(szWidth);
        w.format<math_io::format<Size1F>>();
        w.parse<math_io::parse<Size1F>>();
        w.print<math_io::print<Size1F>>();
        w.operate_with<float>();
    }

    {
        auto w = writer<Size1I>();
        w.description("1D Size in integer");
        w.property(szX, &Size1I::x).description(szX_Size).alias(szWidth);
        w.format<math_io::format<Size1I>>();
        w.parse<math_io::parse<Size1I>>();
        w.print<math_io::print<Size1I>>();
        w.operate_with<int>();
    }

    {
        auto w = writer<Size1U>();
        w.description("1D Size in unsigned integer");
        w.property(szX, &Size1U::x).description(szX_Size).alias(szWidth);
        w.format<math_io::format<Size1U>>();
        w.parse<math_io::parse<Size1U>>();
        w.print<math_io::print<Size1U>>();
        w.operate_with<unsigned>();
    }
}

YQ_INVOKE(reg_size1();)

