////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Geodetic2.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Geodetic2.hxx"

YQ_TYPE_IMPLEMENT(yq::Geodetic2D)
YQ_TYPE_IMPLEMENT(yq::Geodetic2R)

using namespace yq;

static void reg_geodetic2()
{
    {
        auto w = writer<Geodetic2D>();
        w.description("2D geodetic using degrees");
        w.property(szLatitude,  &Geodetic2D::latitude).description(szLatitude_Geodetic).alias(szLat);
        w.property(szLongitude, &Geodetic2D::longitude).description(szLongitude_Geodetic).alias(szLon);
    }
    {
        auto w = writer<Geodetic2R>();
        w.description("2D geodetic using radians");
        w.property(szLatitude,  &Geodetic2R::latitude).description(szLatitude_Geodetic).alias(szLat);
        w.property(szLongitude, &Geodetic2R::longitude).description(szLongitude_Geodetic).alias(szLon);
    }
}

YQ_INVOKE(reg_geodetic2();)
