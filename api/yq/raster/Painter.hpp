////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/raster/forward.hpp>
//#include <yq-vulqan/data/DataFormat.hpp>

namespace yq {
    class Any;
}

namespace yq::raster {


    class Painter {
    public:
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
