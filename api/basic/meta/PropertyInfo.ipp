////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/meta/PropertyInfo.hpp>
#include <basic/meta/GlobalInfo.hpp>
#include <basic/meta/ObjectInfo.hpp>
#include <basic/meta/TypeInfo.hpp>
#include <basic/meta/PropGetter.hpp>
#include <basic/meta/PropSetter.hpp>

#include <basic/Any.hpp>
#include <basic/Errors.hpp>
#include <basic/Logging.hpp>
#include <cassert>

namespace yq {

    PropertyInfo::PropertyInfo(std::string_view zName, const std::source_location& sl, const TypeInfo&theType, Meta* parentMeta, options_t opts) : Meta(zName, parentMeta, sl), m_type(theType)
    {
        assert(parentMeta);

        m_flags |= PROPERTY | opts;

        if(GlobalInfo* g = to_global(parentMeta)){
            assert(g == &meta<Global>());
            if(g->m_properties.keys.has(zName))
                yCritical() << "Duplicate property on GLOBAL: " << zName;
            g->m_properties << this;
        }
        
        if(ObjectInfo* obj = to_object(parentMeta)){
            if(obj->m_local.properties.keys.has(zName))
                yCritical() << "Duplicate property on object (" << obj->name() << "): " << zName;
            obj->m_local.properties << this;
        }
        
        if(TypeInfo* type = to_type(parentMeta)){
            if(type -> m_properties.keys.has(zName))
                yCritical() << "Duplicate property on type (" << type->name() << "): " << zName;
            type->m_properties << this;
        }
    }

    any_error_t     PropertyInfo::get(const void* obj) const
    {
        if(!m_getter)
            return { Any(), errors::no_getter() };
        
        Any ret(m_type);
        std::error_code     ec  = m_getter -> get(ret.raw_ptr(), obj);
        if(ec != std::error_code())
            return { Any(), ec };
        return { ret, ec };
    }

    bool        PropertyInfo::is_state() const
    {
        return static_cast<bool>(flags() & STATE);
    }
    
    bool        PropertyInfo::is_static() const
    {
        return static_cast<bool>(flags() & STATIC);
    }
    
    std::error_code PropertyInfo::print(const void*obj, Stream&str) const
    {
        if(!m_getter)
            return errors::no_getter();
        return m_getter -> print(str, obj);
    }

    std::error_code PropertyInfo::set(void* obj, const Any&var) const
    {
        if(!m_setter)
            return errors::no_setter();
        if(var.type().id() == m_type.id())
            return m_setter -> set(obj, var.raw_ptr());
        auto [v2, ec]  = var.convert(m_type);
        if(!v2.is_valid())
            return errors::incompatible_types();
        if( ec != std::error_code())
            return ec;
        return m_setter -> set(obj, v2.raw_ptr());
    }

    std::error_code PropertyInfo::set(void* obj, std::string_view var) const
    {
        if(!m_setter)
            return errors::no_setter();
        return m_setter -> set(obj, var);
    }

    std::error_code PropertyInfo::write(const void*obj, Stream&str) const
    {
        if(!m_getter)
            return errors::no_getter();
        return m_getter -> write(str, obj);
    }
        

}
