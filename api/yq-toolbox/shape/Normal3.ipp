////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Normal3.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

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
    }

    {
        auto w = writer<Normal3F>();
        w.description("3D normal in float");
        w.property(szDirection, &Normal3F::direction).description(szDirection_Normal).alias(szDir);
    }
}

YQ_INVOKE(reg_normal3();)
