////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include <yq/raster/Painter.hpp>
#include <yq/typedef/vector2.hpp>

namespace yq::raster {

    class Painter2 : public Painter {
    public:
    
    
        Painter2(
        
        );
        
        virtual Any     get_pixel(index_t, index_t) const = 0;
        virtual Any     get_pixel(index_span_t) const = 0;
        virtual Any     get_pixel(const vector2_t&) const = 0;

        virtual bool    set_pixel(index_span_t, const Any&) = 0;
        virtual bool    set_pixel(const vector2_t&, const Any&) = 0;
        virtual bool    set_pixel(index_t, index_t, const Any&) = 0;

        virtual void    draw_line(const vector2_t&, const vector2_t&, const Any&) const = 0;
        virtual void    draw_line(index_t, index_t, index_t, index_t, const Any&) const = 0;
    };
    
    template <typename C>
    class Paint2 : public Painter2 {
    public:
        
        virtual Any     get_pixel(index_span_t) const override;
        virtual bool    set_pixel(index_span_t, const Any&) override;

        virtual void    draw_line(const vector2_t&, const vector2_t&, const Any&) const override;
        virtual void    draw_line(index_t, index_t, index_t, index_t, const Any&) const override;

    
    };

}
