////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Normal3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>

#include "Normal3.hxx"

YQ_TYPE_IMPLEMENT(yq::Normal3D)
YQ_TYPE_IMPLEMENT(yq::Normal3F)

using namespace yq;

static void reg_normal3()
{

    {
        auto w = writer<Normal3D>();
        w.description("3D normal in double");
        w.property(szDirection, &Normal3D::direction).description(szDirection_Normal).alias(szDir);
        w.format<math_io::format<Normal3D>>();
        w.parse<math_io::parse<Normal3D>>();
    }

    {
        auto w = writer<Normal3F>();
        w.description("3D normal in float");
        w.property(szDirection, &Normal3F::direction).description(szDirection_Normal).alias(szDir);
        w.format<math_io::format<Normal3F>>();
        w.parse<math_io::parse<Normal3F>>();
    }
}

YQ_INVOKE(reg_normal3();)
