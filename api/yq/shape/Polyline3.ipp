////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Polyline3.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Polyline3.hxx"

YQ_TYPE_IMPLEMENT(yq::Polyline3D)
YQ_TYPE_IMPLEMENT(yq::Polyline3F)
YQ_TYPE_IMPLEMENT(yq::Polyline3I)
YQ_TYPE_IMPLEMENT(yq::Polyline3U)

using namespace yq;

static void reg_polyline3()
{
    {
        auto w = writer<Polyline3D>();
        w.description("3D polyline in double");
        w.property(szCount, &Polyline3D::count).description(szCount_Polyline);
    }

    {
        auto w = writer<Polyline3F>();
        w.description("3D polyline in float");
        w.property(szCount, &Polyline3F::count).description(szCount_Polyline);
    }

    {
        auto w = writer<Polyline3I>();
        w.description("3D polyline in integer");
        w.property(szCount, &Polyline3I::count).description(szCount_Polyline);
    }

    {
        auto w = writer<Polyline3U>();
        w.description("3D polyline in unsigned integer");
        w.property(szCount, &Polyline3U::count).description(szCount_Polyline);
    }
}

YQ_INVOKE(reg_polyline3();)
