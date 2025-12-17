////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Size3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/math/utility.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Size3.hxx"

YQ_TYPE_IMPLEMENT(yq::Size3D)
YQ_TYPE_IMPLEMENT(yq::Size3F)
YQ_TYPE_IMPLEMENT(yq::Size3I)
YQ_TYPE_IMPLEMENT(yq::Size3U)

namespace yq {
    Size3I  iround(const Size3D&v)
    {
        return { iround(v.x), iround(v.y), iround(v.z) };
    }
}

using namespace yq;



static void reg_size3()
{
    {
        auto w = writer<Size3D>();
        w.description("3D Size in double");
        w.property(szX, &Size3D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3D::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3D::z).description(szZ_Size).alias(szDepth);
        w.format<math_io::format<Size3D>>();
        w.parse<math_io::parse<Size3D>>();
        w.print<math_io::print<Size3D>>();
        w.operate_with<double>();
    }

    {
        auto w = writer<Size3F>();
        w.description("3D Size in float");
        w.property(szX, &Size3F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3F::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3F::z).description(szZ_Size).alias(szDepth);
        w.format<math_io::format<Size3F>>();
        w.parse<math_io::parse<Size3F>>();
        w.print<math_io::print<Size3F>>();
        w.operate_with<float>();
    }

    {
        auto w = writer<Size3I>();
        w.description("3D Size in integer");
        w.property(szX, &Size3I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3I::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3I::z).description(szZ_Size).alias(szDepth);
        w.format<math_io::format<Size3I>>();
        w.parse<math_io::parse<Size3I>>();
        w.print<math_io::print<Size3I>>();
        w.operate_with<int>();
    }

    {
        auto w = writer<Size3U>();
        w.description("3D Size in unsigned integer");
        w.property(szX, &Size3U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3U::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3U::z).description(szZ_Size).alias(szDepth);
        w.format<math_io::format<Size3U>>();
        w.parse<math_io::parse<Size3U>>();
        w.print<math_io::print<Size3U>>();
        w.operate_with<unsigned>();
    }
}

YQ_INVOKE(reg_size3();)

