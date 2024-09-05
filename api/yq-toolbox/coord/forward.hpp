////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>
#include <yq-toolbox/unit/declare.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    class Stream;

    template <typename> struct LatLon;
    template <typename, typename> struct LatLonAlt;
    template <typename, typename> struct Polar2;
    template <typename, typename> struct Cylindrical3;

    using LL                    = LatLon<unit::Radian>;
    using LLH                   = LatLonAlt<unit::Radian,double>;
    using LLM                   = LatLonAlt<unit::Radian,unit::Meter>;
    
    using Polar2D               = Polar2<unit::Radian,double>;
    using Polar2M               = Polar2<unit::Radian,unit::Meter>;
    
    using Cylindrical3D         = Cylindrical3<unit::Radian,double>;
    using Cylindrical3M         = Cylindrical3<unit::Radian,unit::Meter>;
    
}
