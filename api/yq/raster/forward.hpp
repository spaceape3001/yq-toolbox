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

namespace yq::raster {
    using   index_t         = unsigned;
    using   index_span_t    = std::span<const index_t>;
    template <uint8_t N>
    using   config          = ArrayConfig<index_t,N,false,false>;
    template <uint8_t N, class C>
    using   array           = Array<C,config<N>>;
}

