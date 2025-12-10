////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AxisType.hpp"
#include "Gridded.hpp"
#include <yq/meta/Init.hpp>
#include <yq/resource/ResourceMetaWriter.hpp>

YQ_TYPE_IMPLEMENT(yq::data::AxisType)
YQ_RESOURCE_IMPLEMENT(yq::data::Gridded)

namespace yq::data {
    Gridded::Gridded()
    {
    }
    
    Gridded::~Gridded()
    {
    }
}
