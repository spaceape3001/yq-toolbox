////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Polygon3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Polygon3.hxx"

YQ_TYPE_IMPLEMENT(yq::Polygon3D)
YQ_TYPE_IMPLEMENT(yq::Polygon3F)
YQ_TYPE_IMPLEMENT(yq::Polygon3I)
YQ_TYPE_IMPLEMENT(yq::Polygon3U)

using namespace yq;

static void reg_polygon3()
{
    {
        auto w = writer<Polygon3D>();
        w.description("3D polygon in double");
        w.property(szCount, &Polygon3D::count).description(szCount_Polygon);
    }

    {
        auto w = writer<Polygon3F>();
        w.description("3D polygon in float");
        w.property(szCount, &Polygon3F::count).description(szCount_Polygon);
    }

    {
        auto w = writer<Polygon3I>();
        w.description("3D polygon in integer");
        w.property(szCount, &Polygon3I::count).description(szCount_Polygon);
    }

    {
        auto w = writer<Polygon3U>();
        w.description("3D polygon in unsigned integer");
        w.property(szCount, &Polygon3U::count).description(szCount_Polygon);
    }
}

YQ_INVOKE(reg_polygon3();)
