////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PropertyInfo.hpp"

#include <yq-toolbox/errors.hpp>
#include <yq-toolbox/basic/Any.hpp>
#include <yq-toolbox/basic/Logging.hpp>
#include <yq-toolbox/meta/GlobalInfo.hpp>
#include <yq-toolbox/meta/ObjectInfo.hpp>
#include <yq-toolbox/meta/TypeInfo.hpp>
#include <yq-toolbox/meta/PropGetter.hpp>
#include <yq-toolbox/meta/PropSetter.hpp>

#include <cassert>

namespace yq {

    PropertyInfo::PropertyInfo(std::string_view zName, const std::source_location& sl, const TypeInfo&theType, Meta* parentMeta) : Meta(zName, parentMeta, sl), m_type(theType)
    {
        assert(parentMeta);
        set(Flag::PROPERTY);

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

    any_x     PropertyInfo::get(const void* obj) const
    {
        if(!m_getter)
            return errors::no_getter();
        Any ret(m_type);
        std::error_code     ec  = m_getter -> get(ret.raw_ptr(), obj);
        if(ec != std::error_code())
            return std::unexpected(ec);
        return ret;
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
        auto v2  = var.convert(m_type);
        if(!v2)
            return errors::incompatible_types();
        if(!v2->is_valid())
            return errors::incompatible_types();
        return m_setter -> set(obj, v2->raw_ptr());
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
