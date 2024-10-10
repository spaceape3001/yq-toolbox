////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "LatLon.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/unit/MKS.hpp>
#include <yq-toolbox/unit/metatype.hpp>

#include "LatLon.hxx"

YQ_TYPE_IMPLEMENT(yq::LL)

using namespace yq;

static void reg_latlon()
{
    {
        auto w = writer<LL>();
        w.description("Latitude/Longitude");
        w.property(szLatitude,  &LL::lat).description(szLatitude_LatLon).alias(szLat);
        w.property(szLongitude, &LL::lon).description(szLongitude_LatLon).alias(szLon);
    }
}

YQ_INVOKE(reg_latlon();)
