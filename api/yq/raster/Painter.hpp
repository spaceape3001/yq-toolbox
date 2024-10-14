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
        
        virtual Pixmap& pixmap() = 0;
        virtual Pixmap& pixmap() const = 0;
        
        //virtual Any     get_pixel(index_span_t) const = 0;
        //virtual bool    set_pixel(index_span_t, const Any&) = 0;
        
    protected:
        Painter();
        ~Painter();
        
        // Disabled until we determine how to address data format
        // Painter(DataFormat, std::initializer_list<uint32_t> dims);
        
    };

}
