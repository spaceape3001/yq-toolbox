////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Weekday.hpp"

#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include <yq/core/Enumeration.hxx>

YQ_ENUM_IMPLEMENT(yq::Weekday)
YQ_TYPE_IMPLEMENT(yq::Weekday)

using namespace yq;

YQ_INVOKE(
    writer<Weekday>();
)
