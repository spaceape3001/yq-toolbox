////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "MethodInfo.hpp"
#include <yq/errors.hpp>
#include <yq/core/Any.hpp>
#include <yq/core/Logging.hpp>
#include <yq/meta/AnyArgHelper.hpp>
#include <yq/meta/MetaWriter.hpp>
#include <yq/meta/GlobalInfo.hpp>
#include <yq/meta/ObjectInfo.hpp>
#include <yq/meta/TypeInfo.hpp>

namespace yq {
    MethodInfo::MethodInfo(std::string_view zName, const std::source_location& sl, Meta* parentMeta) : Meta(zName, parentMeta, sl)
    {
        assert(parentMeta);

        set(Flag::METHOD);

        if(GlobalInfo* g = to_global(parentMeta)){
            assert(g == &meta<Global>());
            if(g->m_methods.keys.has(zName))
                yCritical() << "Duplicate method on GLOBAL: " << zName;
            g->m_methods << this;
        }
        
        if(ObjectInfo* obj = to_object(parentMeta))
            obj->m_local.methods << this;
        if(TypeInfo* type = to_type(parentMeta))
            type->m_methods << this;
    }
    
    void    MethodInfo::fill_argument_info(size_t n, std::string_view zName, std::string_view zDescription)
    {
        if(n < m_args.size()){
            Meta::Writer w{ const_cast<ArgInfo*>(m_args[n])};
            if(!zName.empty())
                w.name(zName);
            if(!zDescription.empty())
                w.description(zDescription);
        }
    }

    void    MethodInfo::fill_result_info(std::string_view zName, std::string_view zDescription)
    {
        Meta::Writer w{ const_cast<ArgInfo*>(m_result) };
        if(!zName.empty())
            w.name(zName);
        if(!zDescription.empty())
            w.description(zDescription);
    }

    //  INVOKATION
    any_x      MethodInfo::invoke(std::span<const Any> args) const
    {
        return invoke(nullptr, args, false);
    }

    any_x      MethodInfo::invoke(void* obj, std::span<const Any> args) const
    {
        return invoke(obj, args, false);
    }
    
    any_x      MethodInfo::invoke(const void* obj, std::span<const Any> args) const
    {
        return invoke(const_cast<void*>(obj), args, true);
    }

    Expect<Any> MethodInfo::invoke(void* obj, std::span<const TypeInfo* const> types, std::span<const void* const> args, bool constPtr) const
    {
        if(types.size() != args.size())
            return errors::internal_error();
        if(!obj && !is_static())
            return errors::null_object();
        if(obj && constPtr && !is_const())
            return errors::const_object_violation();

        std::vector<const void*>    _args(m_args.size()+1,nullptr);
        std::vector<Any>            _values(m_args.size());

        std::error_code     ec;

        size_t  ac  = 0;
        for(;ac<std::min(m_args.size(), args.size());++ac){
            if(!types[ac])
                return errors::internal_error();
            if(!args[ac])
                return errors::internal_error();
            if(types[ac]->id() == m_args[ac]->type().id()){
                _args[ac]       = args[ac];
            } else if(m_args[ac]->type().is_type()){
                TypeInfo::FNConvert   fn  = types[ac]->converter(static_cast<const TypeInfo&>(m_args[ac]->type()));
                if(!fn)
                    return errors::bad_argument();
            
                _values[ac] = Any(static_cast<const TypeInfo&>(m_args[ac]->type()));
                _args[ac]   = _values[ac].raw_ptr();
                ec = fn((void*) _args[ac], args[ac]);
                if(ec != std::error_code())
                    return errors::bad_argument();
            } else {
                return errors::bad_argument();
            }
        }
        
        for(;ac<m_args.size();++ac){
            if(!m_args[ac]->default_argument())
                return errors::bad_argument();
            _args[ac]   = m_args[ac]->default_argument();
        }

        
            //  guard against results that aren't types
        if(m_result && !m_result->type().is_type())
            return errors::internal_error();


        Any                         result;
        void*                       rptr        = nullptr;

        if(m_result){
            result  = std::move(Any(static_cast<const TypeInfo&>(m_result->type())));
            rptr    = result.raw_ptr();
        }

        ec  = _invoke(rptr, obj, _args.data());
        if(ec != std::error_code())
            return std::unexpected(ec);
        if(m_result)
            return  std::move(result);
        else
            return Any();
    }
    
    any_x      MethodInfo::invoke(void* obj, std::span<const Any> args, bool constPtr) const 
    {
        std::vector<const TypeInfo*>    types;
        std::vector<const void*>        values;
        
        types.reserve(args.size());
        values.reserve(args.size());
        for(const Any& a : args){
            types.push_back(&a.type());
            values.push_back(a.raw_ptr());
        }
        return invoke(obj, types, values, constPtr);
    }

    const TypeInfo*         MethodInfo::result_type() const
    {
        if(!m_result)
            return nullptr;
        return to_type(m_result->type());
    }

    int     MethodInfo::type_match(std::span<const Any> test) const
    {
        std::vector<const TypeInfo*>    types;
        types.reserve(test.size());
        for(const Any& a : test)
            types.push_back(&a.type());
        return type_match(types);
    }

    int     MethodInfo::type_match(std::span<const TypeInfo* const> test) const
    {
        size_t  ac  = 0;
        int     r   = 0;
        for(;ac < std::min(test.size(), m_args.size()); ++ac){
            if(!m_args[ac])     [[unlikely]]
                return -1;
            if(!test[ac])     [[unlikely]]
                return -1;
            
            const TypeInfo& ti = *(test[ac]);
            const Meta&     am = m_args[ac]->type();
            if(!am.is_type())
                continue;
            const TypeInfo& ai = static_cast<const TypeInfo&>(am);
            if(ai.id() == ti.id()) // perfect match
                continue;
            if(ai.id() == any().id()){
                r += 2;
                continue;
            }
            if(ti.can_convert_to(ai)){
                ++r;
                continue;
            }
            
            return -1;  // Incompatible type
        }
        
        for(;ac<m_args.size();++ac){
            if(m_args[ac]->default_argument())
                r += 2;
            else
                return -1;  // unspecified type
        }
        
        if(test.size() > m_args.size()) 
            r += (int)(test.size() - m_args.size());
        return r;
    }
}


