////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Painter.hpp"
//#include <yq/raster/Pixmap.hpp>
//#include <yq/core/Any.hpp>

namespace yq::raster {
    Painter::Painter()
    {
    }
    
    #if 0
    Painter::Painter(DataFormat, std::initializer_list<uint32_t> dims)
    {
    }
    #endif
    
    #if 0
    Painter::Painter(std::shared_ptr<Pixmap> p) : m_pixmap(p.get()), m_shared(p)
    {
    }
    
    Painter::Painter(Pixmap& p) : m_pixmap(&p)
    {
    }
    #endif
    
    Painter::~Painter()
    {
    }
    
    #if 0
    Any     Painter::get_pixel(index_span_t coords) const
    {
        if(m_pixmap)
            return m_pixmap->get(coords);
        return Any();
    }
    
    bool    Painter::set_pixel(index_span_t coords, const Any& val)
    {
        if(!m_pixmap)
            return false;
        return m_pixmap->set(coords, val);
    }
    #endif
}
