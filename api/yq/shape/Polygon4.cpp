////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Polygon4.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Polygon4.hxx"

YQ_TYPE_IMPLEMENT(yq::Polygon4D)
YQ_TYPE_IMPLEMENT(yq::Polygon4F)
YQ_TYPE_IMPLEMENT(yq::Polygon4I)
YQ_TYPE_IMPLEMENT(yq::Polygon4U)

using namespace yq;

static void reg_polygon4()
{
    {
        auto w = writer<Polygon4D>();
        w.description("4D polygon in double");
        w.property(szCount, &Polygon4D::count).description(szCount_Polygon);
    }

    {
        auto w = writer<Polygon4F>();
        w.description("4D polygon in float");
        w.property(szCount, &Polygon4F::count).description(szCount_Polygon);
    }

    {
        auto w = writer<Polygon4I>();
        w.description("4D polygon in integer");
        w.property(szCount, &Polygon4I::count).description(szCount_Polygon);
    }

    {
        auto w = writer<Polygon4U>();
        w.description("4D polygon in unsigned integer");
        w.property(szCount, &Polygon4U::count).description(szCount_Polygon);
    }
}

YQ_INVOKE(reg_polygon4();)
