////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/preamble.hpp>
#include <yq/meta/Meta.hpp>

namespace yq::xfg {
    class PinMeta : public Meta {
    public:
        class Writer;
        PinMeta(std::string_view, NodeMeta&, const std::source_location& sl = std::source_location::current());
        
        size_t  connect_max() const { return m_connectMax; }
        size_t  count_max() const { return m_countMax; }
        size_t  count_min() const { return m_countMin; }
        
    private:
    
        size_t  m_countMax      = 0;
        size_t  m_countMin      = 0;
        size_t  m_connectMax    = 0;
    };
    
    const PinMeta*  to_pin(const Meta*);
}


