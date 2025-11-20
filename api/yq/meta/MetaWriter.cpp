////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/meta/MetaWriter.hpp>
#include <yq/core/Any.hpp>
#include <cassert>

namespace yq {        
    
    Meta::Writer::Writer(Meta* myMeta) : m_meta(myMeta) 
    {
        assert(thread_safe_write());
    }


    Meta::Writer&     Meta::Writer::_1d()
    {
        if(m_meta && thread_safe_write())
            m_meta -> set(Flag::D1);
        return *this;
    }
    
    Meta::Writer&     Meta::Writer::_2d()
    {
        if(m_meta && thread_safe_write())
            m_meta -> set(Flag::D2);
        return *this;
    }

    Meta::Writer&     Meta::Writer::_3d()
    {
        if(m_meta && thread_safe_write())
            m_meta -> set(Flag::D3);
        return *this;
    }

    Meta::Writer&     Meta::Writer::_4d()
    {
        if(m_meta && thread_safe_write())
            m_meta -> set(Flag::D4);
        return *this;
    }
    
    Meta::Writer&     Meta::Writer::_5d()
    {
        if(m_meta && thread_safe_write())
            m_meta -> set(Flag::D5);
        return *this;
    }

    Meta::Writer&     Meta::Writer::_6d()
    {
        if(m_meta && thread_safe_write())
            m_meta -> set(Flag::D6);
        return *this;
    }

    Meta::Writer&     Meta::Writer::alias(std::string_view zAlias)
    {
        if(m_meta && thread_safe_write())
            m_meta -> add_alias(zAlias);
        return *this;
    }
    
    Meta::Writer&     Meta::Writer::alias(std::initializer_list<std::string_view> zAlias)
    {
        if(m_meta && thread_safe_write()){
            for(std::string_view z : zAlias)
                m_meta -> add_alias(z);
        }
        return *this;
    }

    Meta::Writer&     Meta::Writer::description(std::string_view zDescription)
    {
        if(m_meta && thread_safe_write())
            m_meta -> m_description = std::string_view(zDescription);
        return *this;
    }

    Meta::Writer&     Meta::Writer::icon(icon_size_t n, std::string_view zIcon)
    {
        if(m_meta && thread_safe_write())
            m_meta -> m_icons[n] = zIcon;
        return *this;
    }

    Meta::Writer&     Meta::Writer::label(std::string_view zLabel)
    {
        if(m_meta && thread_safe_write())
            m_meta -> m_label = std::string_view(zLabel);
        return *this;
    }
    
    std::string_view Meta::Writer::name() const
    {
        if(!m_meta)
            return "(null meta)";
        return m_meta -> name();
    }

    Meta::Writer&     Meta::Writer::name(std::string_view zName)
    {
        if(m_meta && thread_safe_write())
            m_meta -> m_name = std::string_view(zName);
        return *this;
    }

    Meta::Writer&     Meta::Writer::options(options_t opts)
    {
        if(m_meta)
            m_meta -> set(opts);
        return *this;
    }

    Meta::Writer&     Meta::Writer::set(Flag f)
    {
        if(m_meta && thread_safe_write())
            m_meta -> set(f);
        return *this;
    }

    Meta::Writer&     Meta::Writer::tag(int k)
    {
        return tag(k, Any(true));
    }

    Meta::Writer&     Meta::Writer::tag(std::initializer_list<int> ks)
    {
        for(auto& k : ks)
            tag(k);
        return *this;
    }

    Meta::Writer&     Meta::Writer::tag(int k, Any&&value)
    {
        if(m_meta && thread_safe_write()){
            assert("Tag already set!" && !m_meta->m_tagsByInt.contains(k));
            m_meta -> m_tagsByInt[k] = std::move(value);
        }
        return *this;
    }
    
    Meta::Writer&     Meta::Writer::tag(int k, const Any&value)
    {
        if(m_meta && thread_safe_write()){
            assert("Tag already set!" && !m_meta->m_tagsByInt.contains(k));
            m_meta -> m_tagsByInt[k] = value;
        }
        return *this;
    }
    
    Meta::Writer&     Meta::Writer::tag(std::string_view zKey)
    {   
        return tag(zKey, Any(true));
    }

    
    Meta::Writer&     Meta::Writer::tag(std::string_view zKey, Any&& value)
    {
        if(m_meta && thread_safe_write()){
            assert("Tag already set!" && !m_meta->m_tagsByString.contains(zKey));
            m_meta -> m_tagsByString[zKey] = std::move(value);
        }
        return *this;
    }
    

    Meta::Writer&     Meta::Writer::tag(std::string_view zKey, const Any& value)
    {
        if(m_meta && thread_safe_write()){
            assert("Tag already set!" && !m_meta->m_tagsByString.contains(zKey));
            m_meta -> m_tagsByString[zKey] = value;
        }
        return *this;
    }
    
    Meta::Writer&   Meta::Writer::tls()
    {
        if(m_meta && thread_safe_write())
            m_meta -> set(Flag::TLS);
        return *this;
    }

    Meta::Writer&   Meta::Writer::todo()
    {
        if(m_meta && thread_safe_write())
            m_meta -> set(Flag::TODO);
        return *this;
    }

    Meta::Writer&     Meta::Writer::verbose()
    {
        if(m_meta && thread_safe_write())
            m_meta -> set(Flag::VERBOSE);
        return *this;
    }
}
