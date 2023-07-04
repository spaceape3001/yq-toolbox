////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <meta/MethodInfo.hpp>
#include <meta/MetaWriter.hpp>
#include <meta/GlobalInfo.hpp>
#include <meta/ObjectInfo.hpp>
#include <meta/TypeInfo.hpp>
#include <basic/Any.hpp>
#include <basic/errors.hpp>
#include <basic/Logging.hpp>
#include "AnyArgHelper.hpp"

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
    Expect<Any>      MethodInfo::invoke(std::span<const Any> args) const
    {
        return invoke(nullptr, args, false);
    }

    Expect<Any>      MethodInfo::invoke(void* obj, std::span<const Any> args) const
    {
        return invoke(obj, args, false);
    }
    
    Expect<Any>      MethodInfo::invoke(const void* obj, std::span<const Any> args) const
    {
        return invoke(const_cast<void*>(obj), args, true);
    }

    Expect<Any>      MethodInfo::invoke(void* obj, std::span<const Any> args, bool constPtr) const 
    {
        size_t  ac  = arg_count();
        if(args.size() < ac)
            return errors::insufficient_arguments();
        if(!obj && !is_static())
            return errors::null_object();
        if(obj && constPtr && !is_const())
            return errors::const_object_violation();
        if(m_args.size() < ac)
            return errors::internal_error();
        
        Any                         result;
        void*                       rptr        = nullptr;
        AnyArgHelper                aaa;
        //std::vector<const void*>    ptrs;
        //std::vector<Any>            data;

            //  guard against results that aren't types
        if(m_result && !m_result->type().is_type())
            return errors::internal_error();
        
        std::error_code ec  = aaa.construct(m_args, args);
        if(ec)
            return std::unexpected(ec);
    
        if(m_result){
            result  = std::move(Any(static_cast<const TypeInfo&>(m_result->type())));
            rptr    = result.raw_ptr();
        }
        
        ec  = _invoke(rptr, obj, aaa);
        if(ec != std::error_code())
            return std::unexpected(ec);
        if(m_result)
            return  std::move(result);
        else
            return Any();
    }
}


