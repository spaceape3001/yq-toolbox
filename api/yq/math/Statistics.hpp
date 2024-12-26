////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <span>
#include <yq/trait/square.hpp>

namespace yq {    
    template <typename T>
    struct Statistics {
        T               mean{};
        T               min{};
        T               max{};
        T               norm1{};
        T               norm2{};
        T               normI{};
        square_t<T>     variance{};
        T               stddev{};
        size_t          count{};
    };

    template <typename T>
    Statistics<T>   statistics(std::span<const T> values);
}
