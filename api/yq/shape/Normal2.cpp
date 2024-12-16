////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Normal2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Normal2.hxx"

YQ_TYPE_IMPLEMENT(yq::Normal2D)
YQ_TYPE_IMPLEMENT(yq::Normal2F)

using namespace yq;

static void reg_normal2()
{

    {
        auto w = writer<Normal2D>();
        w.description("2D normal in double");
        w.property(szDirection, &Normal2D::direction).description(szDirection_Normal).alias(szDir);
    }

    {
        auto w = writer<Normal2F>();
        w.description("2D normal in float");
        w.property(szDirection, &Normal2F::direction).description(szDirection_Normal).alias(szDir);
    }
}

YQ_INVOKE(reg_normal2();)
