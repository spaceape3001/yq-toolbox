////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "LatLonAlt.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/unit/MKS.hpp>
#include <yq/unit/metatype.hpp>

#include "LatLonAlt.hxx"

YQ_TYPE_IMPLEMENT(yq::LLH)
YQ_TYPE_IMPLEMENT(yq::LLM)

using namespace yq;

static void reg_latlonalt()
{
    {
        auto w = writer<LLH>();
        w.description("Latitude/Longitude/Altitude (in double)");
        w.property(szLatitude,  &LLH::lat).description(szLatitude_LatLonAlt).alias(szLat);
        w.property(szLongitude, &LLH::lon).description(szLongitude_LatLonAlt).alias(szLon);
        w.property(szAltitude, &LLH::alt).description(szAltitude_LatLonAlt).alias(szAlt);
    }
    
    {
        auto w = writer<LLM>();
        w.description("Latitude/Longitude/Altitude (in meters)");
        w.property(szLatitude,  &LLM::lat).description(szLatitude_LatLonAlt).alias(szLat);
        w.property(szLongitude, &LLM::lon).description(szLongitude_LatLonAlt).alias(szLon);
        w.property(szAltitude, &LLM::alt).description(szAltitude_LatLonAlt).alias(szAlt);
    }
}

YQ_INVOKE(reg_latlonalt();)
