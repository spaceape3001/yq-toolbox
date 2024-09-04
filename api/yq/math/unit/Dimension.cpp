////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Dimension.hpp"

#include <yq/strings.hpp>
#include <yq/basic/DelayInit.hpp>
#include <yq/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::Dimension)

using namespace yq;

static void reg_dimension()
{
    auto w = writer<Dimension>();
    w.property(szTime,        &Dimension::time).description("Dimension in time (eg Seconds)");
    w.property(szLength,      &Dimension::length).description("Dimension in length (eg Meters)");
    w.property(szAngle,       &Dimension::angle).description("Dimension in angle (eg Radians)");
    w.property(szMass,        &Dimension::mass).description("Dimension in mass (eg Kilograms)");
    w.property(szTemperature, &Dimension::temperature).description("Dimension in temperature (eg Kelvins)");
    w.property(szCurrent,     &Dimension::current).description("Dimension in current (eg Amperes)");
    w.property(szMatter,      &Dimension::matter).description("Dimension in matter (eg Moles)");
    w.property(szIntensity,   &Dimension::intensity).description("Dimension in intensity (eg Candela)");
}

YQ_INVOKE(reg_dimension();)
