////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/data/AxisScaling.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/typedef/string_maps.hpp>

namespace yq::data {
    struct GriddedAxis {
        string_any_map_t    attributes;
        size_t              count   = 0;                    //!< Count of "cells" to the values
        bool                edges   = true;                 //!< TRUE if the edges are the values
        std::vector<double> intervals;                      //!< intervals to the cells... if no edges, it'll default to 0.5
        std::string         name;
        AxisScaling         scaling = AxisScaling::Linear;  //!< Type of the axis
        size_t              size    = 0;                    //!< Total number of values per axis { count * #intervals + #edges }
        const TypeMeta*     type    = &meta<float>();       //!< Data type to the axis values
        std::vector<double> values;                         //!< values, two will define edges
        
        GriddedAxis();
        GriddedAxis(const GriddedAxis&);
        GriddedAxis(GriddedAxis&&);
        virtual ~GriddedAxis();
        GriddedAxis& operator=(const GriddedAxis&);
        GriddedAxis& operator=(GriddedAxis&&);
    };
    
}
