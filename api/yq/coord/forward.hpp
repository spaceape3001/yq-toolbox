////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>
#include <yq/math/unit/declare.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    class Stream;

    template <typename T, uint8_t N> struct Coord;

    template <typename T> using Coord1 = Coord<T,1>;
    using Coord1D   = Coord1<double>;
    using Coord1F   = Coord1<float>;
    using Coord1I   = Coord1<int>;
    using Coord1U   = Coord1<unsigned int>;
    using Coord1Z   = Coord1<size_t>;

    template <typename T> using Coord2 = Coord<T,2>;
    using Coord2D   = Coord2<double>;
    using Coord2F   = Coord2<float>;
    using Coord2I   = Coord2<int>;
    using Coord2U   = Coord2<unsigned int>;
    using Coord2Z   = Coord2<size_t>;

    template <typename T> using Coord3 = Coord<T,3>;
    using Coord3D   = Coord3<double>;
    using Coord3F   = Coord3<float>;
    using Coord3I   = Coord3<int>;
    using Coord3U   = Coord3<unsigned int>;
    using Coord3Z   = Coord3<size_t>;

    template <typename T> using Coord4 = Coord<T,4>;
    using Coord4D   = Coord4<double>;
    using Coord4F   = Coord4<float>;
    using Coord4I   = Coord4<int>;
    using Coord4U   = Coord4<unsigned int>;
    using Coord4Z   = Coord4<size_t>;

    template <typename T> using Coord5 = Coord<T,5>;
    using Coord5D   = Coord5<double>;
    using Coord5F   = Coord5<float>;
    using Coord5I   = Coord5<int>;
    using Coord5U   = Coord5<unsigned int>;
    using Coord5Z   = Coord5<size_t>;

    template <typename T> using Coord6 = Coord<T,6>;
    using Coord6D   = Coord6<double>;
    using Coord6F   = Coord6<float>;
    using Coord6I   = Coord6<int>;
    using Coord6U   = Coord6<unsigned int>;
    using Coord6Z   = Coord6<size_t>;

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
