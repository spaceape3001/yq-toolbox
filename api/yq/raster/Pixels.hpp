////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/raster/Pixmap.hpp>
#include <yq/coord/Coord.hpp>

namespace yq {
    template <uint8_t DIMS, class C>
    struct Pixels : public PixmapN<DIMS>, public raster::array<DIMS,C> {
    
        static_assert(DIMS && (DIMS<=6), "Pixel dimensions limited 1 to 6");
        static_assert(is_type_v<C>, "Pixel data must be meta-capable!  (Missing a declare macro?)");
    
        using base_t                            = PixmapN<DIMS>;
        using index_t                           = raster::index_t;
        using index_span_t                      = raster::index_span_t;
        using coord_t                           = Coord<index_t, DIMS>;
        using array_t                           = raster::array<DIMS,C>;
        using color_t                           = C;
        static constexpr uint8_t  kDimensions   = DIMS;
        using array_t::count;

        static coord_t  coord(index_span_t pix);
        
        Pixels();
        Pixels(coord_t, const C& def={});
        Pixels(coord_t, copy_k, const C*);
        ~Pixels();
        
        size_t          bytes(pixel_k) const override;
        size_t          bytes(total_k) const override;
        bool            contains(const coord_t&) const;
        uint8_t         count(dimensions_k) const override;
        size_t          count(i_k) const override;
        size_t          count(j_k) const override;
        size_t          count(k_k) const override;
        size_t          count(l_k) const override;
        size_t          count(m_k) const override;
        size_t          count(n_k) const override;
        size_t          count(pixels_k) const override;
        index_span_t    dimensions() const override;

        bool            empty() const override;

        Any             get(const coord_t& cc) const override;
        Any             get(index_span_t pix) const override;

        size_t          index(index_span_t) const override;
        size_t          index(const coord_t&) const override;

        bool            inside(const coord_t&) const override;
        bool            inside(index_span_t) const override;

        Memory          memory(ref_k) const override;
        Memory          memory(copy_k) const override;


        C               pixel(const coord_t& coord) const;
        const void*     pointer(data_k) const override;
        virtual bool    set(const coord_t& cc, const Any& val) override;
        virtual bool    set(index_span_t pix, const Any& val) override;
        
        bool            set(const coord_t& cc, const C& val) ;

        const TypeInfo& type(pixel_k) const override;
    };
}
