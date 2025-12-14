////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Memory.hpp>
#include <yq/data/AxisScaling.hpp>
#include <yq/resource/Resource.hpp>
#include <yq/typedef/string_maps.hpp>

namespace yq::data {
    struct GriddedValue {
        const TypeMeta*     type    = &yq::meta<float>();  //!< Data type to the values
    };
    
    struct GriddedInfo {
        std::vector<GriddedAxis>        axes;
        std::vector<GriddedValue>       values;
    };

    class Gridded : public Resource {
        YQ_RESOURCE_DECLARE(Gridded, Resource)
    public:
        GriddedInfo     info;
        Memory          memory; // need binary flexibility here...
        
        Gridded();
        ~Gridded();
    };
}

