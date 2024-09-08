////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "LatLonAlt.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/unit/MKS.hpp>
#include <yq-toolbox/unit/metatype.hpp>

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
