////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/array.hpp>
#include <yq/typedef/pixels.hpp>
#include <yq/typedef/pixmap.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <span>

namespace yq {
    template <typename> struct Vector1;
    template <typename> struct Vector2;
    template <typename> struct Vector3;
    template <typename> struct Vector4;
}

namespace yq::raster {
    using   index_t         = unsigned;
    using   index_span_t    = std::span<const index_t>;
    template <uint8_t N>
    using   config          = ArrayConfig<index_t,N,false,false>;
    template <uint8_t N, class C>
    using   array           = Array<C,config<N>>;
    
    using   vector1_t       = Vector1<index_t>;
    using   vector2_t       = Vector2<index_t>;
    using   vector3_t       = Vector3<index_t>;
    using   vector4_t       = Vector4<index_t>;
}

