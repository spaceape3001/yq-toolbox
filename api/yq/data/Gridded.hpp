////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Memory.hpp>
#include <yq/data/AxisType.hpp>
#include <yq/resource/Resource.hpp>

namespace yq::data {
    struct GriddedAxis {
        size_t              count   = 0;                    //!< Count of "cells" to the values
        bool                edges   = true;                 //!< TRUE if the edges are the values
        std::vector<double> intervals;                      //!< intervals to the cells... if no edges, it'll default to 0.5
        const TypeMeta*     meta    = nullptr;              //!< Data type to the axis values
        std::string         name;
        size_t              size    = 0;                    //!< Total number of values per axis { count * #intervals + #edges }
        AxisType            type    = AxisType::Linear;     //!< Type of the axis
        std::vector<double> values;                         //!< values, two will define edges
    };
    
    struct GriddedInfo {
        std::vector<GriddedAxis>    axes;
        
        
        
    };

    class Gridded : public Resource {
        YQ_RESOURCE_DECLARE(Gridded, Resource)
    public:
    
        std::vector<GriddedAxis>    axes;
        GriddedAxis                 value;
        Memory                      memory;
        
        Gridded();
        ~Gridded();
    };
}

