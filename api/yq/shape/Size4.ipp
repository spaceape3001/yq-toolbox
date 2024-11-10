////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Size4.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/utility.hpp>
#include <yq/meta/Init.hpp>

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
    }

    {
        auto w = writer<Size4F>();
        w.description("4D Size in float");
        w.property(szX, &Size4F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4F::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4F::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4F::w).description(szW_Size).alias(szDuration);
    }

    {
        auto w = writer<Size4I>();
        w.description("4D Size in integer");
        w.property(szX, &Size4I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4I::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4I::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4I::w).description(szW_Size).alias(szDuration);
    }

    {
        auto w = writer<Size4U>();
        w.description("4D Size in unsigned integer");
        w.property(szX, &Size4U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4U::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4U::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4U::w).description(szW_Size).alias(szDuration);
    }
}

YQ_INVOKE(reg_size4();)

