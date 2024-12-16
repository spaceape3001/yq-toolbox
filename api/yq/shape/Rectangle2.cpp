////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Rectangle2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Rectangle2.hxx"

YQ_TYPE_IMPLEMENT(yq::Rectangle2D)
YQ_TYPE_IMPLEMENT(yq::Rectangle2F)
YQ_TYPE_IMPLEMENT(yq::Rectangle2I)
YQ_TYPE_IMPLEMENT(yq::Rectangle2U)

using namespace yq;

static void reg_rectangle2()
{
    {
        auto w = writer<Rectangle2D>();
        w.description("2D rectangle in double");
        w.property(szPosition, &Rectangle2D::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2D::size).description(szSize_Rectangle);
    }

    {
        auto w = writer<Rectangle2F>();
        w.description("2D rectangle in float");
        w.property(szPosition, &Rectangle2F::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2F::size).description(szSize_Rectangle);
    }

    {
        auto w = writer<Rectangle2I>();
        w.description("2D rectangle in integer");
        w.property(szPosition, &Rectangle2I::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2I::size).description(szSize_Rectangle);
    }

    {
        auto w = writer<Rectangle2U>();
        w.description("2D rectangle in unsigned integer");
        w.property(szPosition, &Rectangle2U::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2U::size).description(szSize_Rectangle);
    }
}

YQ_INVOKE(reg_rectangle2();)
