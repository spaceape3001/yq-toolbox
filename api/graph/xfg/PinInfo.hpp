////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/preamble.hpp>
#include <0/meta/Meta.hpp>

namespace yq::xfg {
    class PinInfo : public Meta {
    public:
        class Writer;
        PinInfo(std::string_view, NodeInfo&, const std::source_location& sl = std::source_location::current());
        
        size_t  connect_max() const { return m_connectMax; }
        size_t  count_max() const { return m_countMax; }
        size_t  count_min() const { return m_countMin; }
        
    private:
    
        size_t  m_countMax      = 0;
        size_t  m_countMin      = 0;
        size_t  m_connectMax    = 0;
    };
    
    const PinInfo*  to_pin(const Meta*);
}


