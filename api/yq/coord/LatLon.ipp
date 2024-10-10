////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "LatLon.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/unit/MKS.hpp>
#include <yq/unit/metatype.hpp>

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
