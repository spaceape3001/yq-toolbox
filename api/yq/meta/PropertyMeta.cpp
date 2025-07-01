////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PropertyMeta.hpp"

#include <yq/errors.hpp>
#include <yq/core/Any.hpp>
#include <yq/core/Logging.hpp>
#include <yq/meta/GlobalMeta.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/meta/TypeMeta.hpp>
#include <yq/meta/PropGetter.hpp>
#include <yq/meta/PropSetter.hpp>

#include <cassert>

namespace yq {

    PropertyMeta::PropertyMeta(std::string_view zName, const std::source_location& sl, const TypeMeta&theType, Meta* parentMeta) : 
        Meta(zName, parentMeta, sl), m_type(theType)
    {
        assert(parentMeta);
        set(Flag::PROPERTY);
        
        theType.m_ctorCopyB(m_default, theType.m_default);

        if(GlobalMeta* g = to_global(parentMeta)){
            assert(g == &meta<Global>());
            if(g->m_properties.keys.has(zName))
                yCritical() << "Duplicate property on GLOBAL: " << zName;
            g->m_properties << this;
        }
        
        if(ObjectMeta* obj = to_object(parentMeta)){
            if(obj->m_local.properties.keys.has(zName))
                yCritical() << "Duplicate property on object (" << obj->name() << "): " << zName;
            obj->m_local.properties << this;
        }
        
        if(TypeMeta* type = to_type(parentMeta)){
            if(type -> m_properties.keys.has(zName))
                yCritical() << "Duplicate property on type (" << type->name() << "): " << zName;
            type->m_properties << this;
        }
    }

    any_x     PropertyMeta::get(const void* obj) const
    {
        if(!m_getter)
            return errors::no_getter();
        Any ret(m_type);
        std::error_code     ec  = m_getter -> get(ret.raw_ptr(), obj);
        if(ec != std::error_code())
            return std::unexpected(ec);
        return ret;
    }

    bool            PropertyMeta::is_default(const Any& value) const
    {
        if(value.type().id() != m_type.id())
            return false;
        return m_type.m_equal(m_default, value.data());
    }
    
    std::error_code PropertyMeta::print(const void*obj, Stream&str) const
    {
        if(!m_getter)
            return errors::no_getter();
        return m_getter -> print(str, obj);
    }

    std::error_code PropertyMeta::set(void* obj, const Any&var) const
    {
        if(!m_setter)
            return errors::no_setter();
        if(var.type().id() == m_type.id())
            return m_setter -> set(obj, var.raw_ptr());
        auto v2  = var.convert(m_type);
        if(!v2)
            return errors::incompatible_types();
        if(!v2->is_valid())
            return errors::incompatible_types();
        return m_setter -> set(obj, v2->raw_ptr());
    }

    std::error_code PropertyMeta::set(void* obj, std::string_view var) const
    {
        if(!m_setter)
            return errors::no_setter();
        return m_setter -> set(obj, var);
    }

    std::error_code  PropertyMeta::set(void*obj, default_k) const
    {
        if(!m_setter)
            return errors::no_setter();
        return m_setter -> set(obj, m_type.is_small() ? (const void*) m_default.Data : m_default.Pointer);
    }

    std::error_code PropertyMeta::write(const void*obj, Stream&str) const
    {
        if(!m_getter)
            return errors::no_getter();
        return m_getter -> write(str, obj);
    }
}
