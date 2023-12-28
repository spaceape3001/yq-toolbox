////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

//#include "SatelliteTLE.ipp"

#include "Date.ipp"
#include "JDay.ipp"
#include "Time.ipp"
#include "Geodetic2.hpp"
#include "Geodetic3.hpp"
#include <math/unit/MKS.hpp>
#include <math/unit/SCALED.hpp>


//#include "EarthDate.ipp"

#include "enum/Calendar.hpp"
#include "enum/Weekday.hpp"

#include <meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::Calendar)
YQ_TYPE_IMPLEMENT(yq::Date)
YQ_TYPE_IMPLEMENT(yq::Geodetic2D)
YQ_TYPE_IMPLEMENT(yq::Geodetic2R)
YQ_TYPE_IMPLEMENT(yq::Geodetic3DF)
YQ_TYPE_IMPLEMENT(yq::Geodetic3DM)
YQ_TYPE_IMPLEMENT(yq::Geodetic3RF)
YQ_TYPE_IMPLEMENT(yq::Geodetic3RM)
YQ_TYPE_IMPLEMENT(yq::JDay)
YQ_TYPE_IMPLEMENT(yq::Time)
YQ_TYPE_IMPLEMENT(yq::Weekday)
