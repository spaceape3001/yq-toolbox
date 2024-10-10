////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Polygon2.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Polygon2.hxx"

YQ_TYPE_IMPLEMENT(yq::Polygon2D)
YQ_TYPE_IMPLEMENT(yq::Polygon2F)
YQ_TYPE_IMPLEMENT(yq::Polygon2I)
YQ_TYPE_IMPLEMENT(yq::Polygon2U)

using namespace yq;

static void reg_polygon2()
{
    {
        auto w = writer<Polygon2D>();
        w.description("2D polygon in double");
        w.property(szCount, &Polygon2D::count).description(szCount_Polygon);
    }

    {
        auto w = writer<Polygon2F>();
        w.description("2D polygon in float");
        w.property(szCount, &Polygon2F::count).description(szCount_Polygon);
    }

    {
        auto w = writer<Polygon2I>();
        w.description("2D polygon in integer");
        w.property(szCount, &Polygon2I::count).description(szCount_Polygon);
    }

    {
        auto w = writer<Polygon2U>();
        w.description("2D polygon in unsigned integer");
        w.property(szCount, &Polygon2U::count).description(szCount_Polygon);
    }
}

YQ_INVOKE(reg_polygon2();)
