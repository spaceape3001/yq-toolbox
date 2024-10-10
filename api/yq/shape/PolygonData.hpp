////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>

namespace yq {
    /*! \brief Structure for polygon data
    */
    template <typename V>
    struct PolygonData {
        std::vector<V>  vertex;
        constexpr bool operator==(const PolygonData&) const noexcept = default;
    };
}

