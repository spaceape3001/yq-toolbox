////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Polyline4.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Polyline4.hxx"

YQ_TYPE_IMPLEMENT(yq::Polyline4D)
YQ_TYPE_IMPLEMENT(yq::Polyline4F)
YQ_TYPE_IMPLEMENT(yq::Polyline4I)
YQ_TYPE_IMPLEMENT(yq::Polyline4U)

using namespace yq;

static void reg_polyline4()
{
    {
        auto w = writer<Polyline4D>();
        w.description("4D polyline in double");
        w.property(szCount, &Polyline4D::count).description(szCount_Polyline);
    }

    {
        auto w = writer<Polyline4F>();
        w.description("4D polyline in float");
        w.property(szCount, &Polyline4F::count).description(szCount_Polyline);
    }

    {
        auto w = writer<Polyline4I>();
        w.description("4D polyline in integer");
        w.property(szCount, &Polyline4I::count).description(szCount_Polyline);
    }

    {
        auto w = writer<Polyline4U>();
        w.description("4D polyline in unsigned integer");
        w.property(szCount, &Polyline4U::count).description(szCount_Polyline);
    }
}

YQ_INVOKE(reg_polyline4();)
