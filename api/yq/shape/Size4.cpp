////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Size4.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/math/utility.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Size4.hxx"

YQ_TYPE_IMPLEMENT(yq::Size4D)
YQ_TYPE_IMPLEMENT(yq::Size4F)
YQ_TYPE_IMPLEMENT(yq::Size4I)
YQ_TYPE_IMPLEMENT(yq::Size4U)

namespace yq {
    Size4I  iround(const Size4D&v)
    {
        return { iround(v.x), iround(v.y), iround(v.z), iround(v.w) };
    }
}

using namespace yq;

static void reg_size4()
{
    {
        auto w = writer<Size4D>();
        w.description("4D Size in double");
        w.property(szX, &Size4D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4D::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4D::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4D::w).description(szW_Size).alias(szDuration);
        w.format<math_io::format<Size4D>>();
        w.parse<math_io::parse<Size4D>>();
        w.print<math_io::print<Size4D>>();
        w.operate_with<double>();
    }

    {
        auto w = writer<Size4F>();
        w.description("4D Size in float");
        w.property(szX, &Size4F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4F::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4F::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4F::w).description(szW_Size).alias(szDuration);
        w.format<math_io::format<Size4F>>();
        w.parse<math_io::parse<Size4F>>();
        w.print<math_io::print<Size4F>>();
        w.operate_with<float>();
    }

    {
        auto w = writer<Size4I>();
        w.description("4D Size in integer");
        w.property(szX, &Size4I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4I::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4I::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4I::w).description(szW_Size).alias(szDuration);
        w.format<math_io::format<Size4I>>();
        w.parse<math_io::parse<Size4I>>();
        w.print<math_io::print<Size4I>>();
        w.operate_with<int>();
    }

    {
        auto w = writer<Size4U>();
        w.description("4D Size in unsigned integer");
        w.property(szX, &Size4U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4U::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4U::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4U::w).description(szW_Size).alias(szDuration);
        w.format<math_io::format<Size4U>>();
        w.parse<math_io::parse<Size4U>>();
        w.print<math_io::print<Size4U>>();
        w.operate_with<unsigned>();
    }
}

YQ_INVOKE(reg_size4();)

