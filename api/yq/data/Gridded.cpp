////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GriddedAxis.hpp"
#include "AxisScaling.hpp"
#include "Gridded.hpp"
#include <yq/meta/Init.hpp>
#include <yq/resource/ResourceMetaWriter.hpp>

YQ_TYPE_IMPLEMENT(yq::data::AxisScaling)
YQ_RESOURCE_IMPLEMENT(yq::data::Gridded)

namespace yq::data {
    Gridded::Gridded()
    {
    }
    
    Gridded::~Gridded()
    {
    }
}
