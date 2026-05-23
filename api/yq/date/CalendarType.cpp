////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "CalendarType.hpp"

#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include <yq/core/Enumeration.hxx>

YQ_ENUM_IMPLEMENT(yq::CalendarType)
YQ_TYPE_IMPLEMENT(yq::CalendarType)

using namespace yq;

YQ_INVOKE(
    writer<CalendarType>();
)
