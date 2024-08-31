////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AnyArgHelper.hpp"
#include <0/meta/ArgInfo.hpp>
#include <0/basic/Any.hpp>
#include <yq/basic/errors.hpp>

namespace yq {
    AnyArgHelper::AnyArgHelper()
    {
    }
    
    AnyArgHelper::~AnyArgHelper()
    {
    }
    

    std::error_code     AnyArgHelper::construct(std::span<const ArgInfo* const> spec, const std::span<const Any> data)
    {
        if(m_constructed)
            return create_error<"AnyArgHelper already constructed">();
        if(data.size() < spec.size())
            return errors::insufficient_arguments();

        if(!spec.empty()){
            for(const ArgInfo* ai : spec){
                if(!ai)
                    return errors::null_pointer();
                if(!ai->type().is_type())
                    return errors::internal_error();
            }
            
            size_t      ac = spec.size();
            
            m_data.resize(ac);
            m_pointers.resize(ac, nullptr);
            
            for(size_t n=0; n<ac; ++n){
                const ArgInfo&  ai  = *spec[n];
                const Any&      arg = data[n];
                
                // the fast way
                if(&arg.type() == &ai.type()){
                    m_pointers[n]   = arg.raw_ptr();
                    continue;
                }

                auto v      = arg.convert(static_cast<const TypeInfo&>(ai.type()));
                if(!v)
                    return errors::bad_argument();
                
                m_data[n]       = std::move(*v);
                m_pointers[n]   = data[n].raw_ptr();
            }
        }
        
        m_constructed   = true;
        return std::error_code();
    }
}

