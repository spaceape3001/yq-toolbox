////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Polyline2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Polyline2.hxx"

YQ_TYPE_IMPLEMENT(yq::Polyline2D)
YQ_TYPE_IMPLEMENT(yq::Polyline2F)
YQ_TYPE_IMPLEMENT(yq::Polyline2I)
YQ_TYPE_IMPLEMENT(yq::Polyline2U)

using namespace yq;

static void reg_polyline2()
{
    {
        auto w = writer<Polyline2D>();
        w.description("2D polyline in double");
        w.property(szCount, &Polyline2D::count).description(szCount_Polyline);
    }

    {
        auto w = writer<Polyline2F>();
        w.description("2D polyline in float");
        w.property(szCount, &Polyline2F::count).description(szCount_Polyline);
    }

    {
        auto w = writer<Polyline2I>();
        w.description("2D polyline in integer");
        w.property(szCount, &Polyline2I::count).description(szCount_Polyline);
    }

    {
        auto w = writer<Polyline2U>();
        w.description("2D polyline in unsigned integer");
        w.property(szCount, &Polyline2U::count).description(szCount_Polyline);
    }
}

YQ_INVOKE(reg_polyline2();)
