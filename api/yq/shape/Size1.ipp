////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Size1.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Size1.hxx"

YQ_TYPE_IMPLEMENT(yq::Size1D)
YQ_TYPE_IMPLEMENT(yq::Size1F)
YQ_TYPE_IMPLEMENT(yq::Size1I)
YQ_TYPE_IMPLEMENT(yq::Size1U)

using namespace yq;

static void reg_size1()
{
    {
        auto w = writer<Size1D>();
        w.description("1D Size in double");
        w.property(szX, &Size1D::x).description(szX_Size).alias(szWidth);
    }

    {
        auto w = writer<Size1F>();
        w.description("1D Size in float");
        w.property(szX, &Size1F::x).description(szX_Size).alias(szWidth);
    }

    {
        auto w = writer<Size1I>();
        w.description("1D Size in integer");
        w.property(szX, &Size1I::x).description(szX_Size).alias(szWidth);
    }

    {
        auto w = writer<Size1U>();
        w.description("1D Size in unsigned integer");
        w.property(szX, &Size1U::x).description(szX_Size).alias(szWidth);
    }
}

YQ_INVOKE(reg_size1();)

