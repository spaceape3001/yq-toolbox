////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Geodetic3.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Geodetic3.hxx"

YQ_TYPE_IMPLEMENT(yq::Geodetic3DF)
YQ_TYPE_IMPLEMENT(yq::Geodetic3DM)
YQ_TYPE_IMPLEMENT(yq::Geodetic3RF)
YQ_TYPE_IMPLEMENT(yq::Geodetic3RM)

using namespace yq;

static void reg_geodetic3()
{
    {
        auto w = writer<Geodetic3DF>();
        w.description("3D geodetic using degrees & feet");
        w.property(szAltitude,  &Geodetic3DF::altitude).description(szAltitude_Geodetic).alias(szAlt);
        w.property(szLatitude,  &Geodetic3DF::latitude).description(szLatitude_Geodetic).alias(szLat);
        w.property(szLongitude, &Geodetic3DF::longitude).description(szLongitude_Geodetic).alias(szLon);
    }

    {
        auto w = writer<Geodetic3DM>();
        w.description("3D geodetic using degrees & meters");
        w.property(szAltitude,  &Geodetic3DM::altitude).description(szAltitude_Geodetic).alias(szAlt);
        w.property(szLatitude,  &Geodetic3DM::latitude).description(szLatitude_Geodetic).alias(szLat);
        w.property(szLongitude, &Geodetic3DM::longitude).description(szLongitude_Geodetic).alias(szLon);
    }

    {
        auto w = writer<Geodetic3RF>();
        w.description("3D geodetic using radians & feet");
        w.property(szAltitude,  &Geodetic3RF::altitude).description(szAltitude_Geodetic).alias(szAlt);
        w.property(szLatitude,  &Geodetic3RF::latitude).description(szLatitude_Geodetic).alias(szLat);
        w.property(szLongitude, &Geodetic3RF::longitude).description(szLongitude_Geodetic).alias(szLon);
    }

    {
        auto w = writer<Geodetic3RM>();
        w.description("3D geodetic using radians & meters");
        w.property(szAltitude,  &Geodetic3RM::altitude).description(szAltitude_Geodetic).alias(szAlt);
        w.property(szLatitude,  &Geodetic3RM::latitude).description(szLatitude_Geodetic).alias(szLat);
        w.property(szLongitude, &Geodetic3RM::longitude).description(szLongitude_Geodetic).alias(szLon);
    }
}

YQ_INVOKE(reg_geodetic3();)
