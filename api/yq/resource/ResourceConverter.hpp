////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/resource.hpp>
#include <source_location>

namespace yq {    
    class ResourceConverter {
    public:
    
        //! Code location to where the driver was registered.
        constexpr const std::source_location& location() const { return m_location; }
        
        const ResourceMeta& source() const { return m_source; }
        const ResourceMeta& target() const { return m_target; }
        
        virtual ResourcePtr convert(const Resource&) const = 0;
        
    protected:
        friend class Resource;
        
        ResourceConverter(const ResourceMeta&src, const ResourceMeta&tgt, const std::source_location&);
        virtual ~ResourceConverter();
    
    private:
        const ResourceMeta&     m_source;
        const ResourceMeta&     m_target;
        std::source_location    m_location;
    };
}
