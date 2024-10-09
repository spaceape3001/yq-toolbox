////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/pixel/pixels_fwd.hpp>
//#include <yq-vulqan/data/DataFormat.hpp>

namespace yq {
    class Any;
}

namespace yq::pixel {


    class Painter {
    public:
        
        using index_span_t = pixel::index_span_t;
    
        Painter();
        
        // Disabled until we determine how to address data format
        // Painter(DataFormat, std::initializer_list<uint32_t> dims);
        
        Painter(std::shared_ptr<Pixmap>);
        Painter(Pixmap&);
        ~Painter();
        
        Any     get_pixel(index_span_t) const;
        bool    set_pixel(index_span_t, const Any&);
        
    private:
        Pixmap*                     m_pixmap;
        std::shared_ptr<Pixmap>     m_shared;
    };

}
