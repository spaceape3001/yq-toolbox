////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Size2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/math/utility.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Size2.hxx"

YQ_TYPE_IMPLEMENT(yq::Size2D)
YQ_TYPE_IMPLEMENT(yq::Size2F)
YQ_TYPE_IMPLEMENT(yq::Size2I)
YQ_TYPE_IMPLEMENT(yq::Size2U)

namespace yq {
    Size2I  iround(const Size2D&v)
    {
        return { iround(v.x), iround(v.y) };
    }
}

using namespace yq;

static void reg_size2()
{
    {
        auto w = writer<Size2D>();
        w.description("2D Size in double");
        w.property(szX, &Size2D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2D::y).description(szY_Size).alias(szHeight);
        w.format<math_io::format<Size2D>>();
        w.parse<math_io::parse<Size2D>>();
        w.print<math_io::print<Size2D>>();
        w.operate_with<double>();
    }

    {
        auto w = writer<Size2F>();
        w.description("2D Size in float");
        w.property(szX, &Size2F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2F::y).description(szY_Size).alias(szHeight);
        w.format<math_io::format<Size2F>>();
        w.parse<math_io::parse<Size2F>>();
        w.print<math_io::print<Size2F>>();
        w.operate_with<float>();
    }

    {
        auto w = writer<Size2I>();
        w.description("2D Size in integer");
        w.property(szX, &Size2I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2I::y).description(szY_Size).alias(szHeight);
        w.format<math_io::format<Size2I>>();
        w.parse<math_io::parse<Size2I>>();
        w.print<math_io::print<Size2I>>();
        w.operate_with<int>();
    }

    {
        auto w = writer<Size2U>();
        w.description("2D Size in unsigned integer");
        w.property(szX, &Size2U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2U::y).description(szY_Size).alias(szHeight);
        w.format<math_io::format<Size2U>>();
        w.parse<math_io::parse<Size2U>>();
        w.print<math_io::print<Size2U>>();
        w.operate_with<unsigned>();
    }
}

YQ_INVOKE(reg_size2();)

