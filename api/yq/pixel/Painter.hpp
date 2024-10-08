////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-graphics/typedef/pixels.hpp>
#include <yq-vulqan/data/DataFormat.hpp>

namespace yq::tachyon {

    using Pixmap = pixel::Pixmap;
    

    class Painter {
    public:
        
        using index_span_t = pixel::index_span_t;
    
        Painter();
        Painter(DataFormat, std::initializer_list<uint32_t> dims);
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
