////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/typedef/array.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <span>

namespace yq {
    template <typename> class Ref;
    template <typename, uint8_t> struct Coord;
}

namespace yq::pixel {
    using   index_t         = unsigned;
    using   index_span_t      = std::span<const index_t>;
    template <uint8_t N>
    using   config          = ArrayConfig<index_t,N,false,false>;
    template <uint8_t N, class C>
    using   array           = Array<C,config<N>>;

    class Pixmap;
    class Painter;

    using PixmapUPtr        = std::unique_ptr<Pixmap>;
    using PixmapSPtr        = std::shared_ptr<Pixmap>;
    using PixmapSCPtr       = std::shared_ptr<const Pixmap>;

    template <uint8_t>
    class PixmapN;
    
    using Pixmap1           = PixmapN<1>;
    using Pixmap2           = PixmapN<2>;
    using Pixmap3           = PixmapN<3>;
    using Pixmap4           = PixmapN<4>;
    
    template <uint8_t, class>
    struct Pixels;
    
    template <class C> using Pixels1 = Pixels<1,C>;
    template <class C> using Pixels2 = Pixels<2,C>;
    template <class C> using Pixels3 = Pixels<3,C>;
    template <class C> using Pixels4 = Pixels<4,C>;
}
