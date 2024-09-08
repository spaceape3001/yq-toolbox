////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Size2.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Size2.hxx"

YQ_TYPE_IMPLEMENT(yq::Size2D)
YQ_TYPE_IMPLEMENT(yq::Size2F)
YQ_TYPE_IMPLEMENT(yq::Size2I)
YQ_TYPE_IMPLEMENT(yq::Size2U)

using namespace yq;

static void reg_size2()
{
    {
        auto w = writer<Size2D>();
        w.description("2D Size in double");
        w.property(szX, &Size2D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2D::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size2F>();
        w.description("2D Size in float");
        w.property(szX, &Size2F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2F::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size2I>();
        w.description("2D Size in integer");
        w.property(szX, &Size2I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2I::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size2U>();
        w.description("2D Size in unsigned integer");
        w.property(szX, &Size2U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2U::y).description(szY_Size).alias(szHeight);
    }
}

YQ_INVOKE(reg_size2();)

