////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/array.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <span>

namespace yq::raster {
    class Pixmap;
    using PixmapUPtr        = std::unique_ptr<Pixmap>;
    using PixmapSPtr        = std::shared_ptr<Pixmap>;
    using PixmapSCPtr       = std::shared_ptr<const Pixmap>;

    template <uint8_t>
    class PixmapN;
    
    using Pixmap1           = PixmapN<1>;
    using Pixmap2           = PixmapN<2>;
    using Pixmap3           = PixmapN<3>;
    using Pixmap4           = PixmapN<4>;
}
