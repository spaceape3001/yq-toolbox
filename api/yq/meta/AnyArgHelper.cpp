////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AnyArgHelper.hpp"
#include <yq/errors.hpp>
#include <yq/core/Any.hpp>
#include <yq/meta/ArgMeta.hpp>

namespace yq {
    AnyArgHelper::AnyArgHelper()
    {
    }
    
    AnyArgHelper::~AnyArgHelper()
    {
    }
    

    std::error_code     AnyArgHelper::construct(std::span<const ArgMeta* const> spec, const std::span<const Any> data)
    {
        if(m_constructed)
            return create_error<"AnyArgHelper already constructed">();
        if(data.size() < spec.size())
            return errors::insufficient_arguments();

        if(!spec.empty()){
            for(const ArgMeta* ai : spec){
                if(!ai)
                    return errors::null_pointer();
                if(!ai->type().is_type())
                    return errors::internal_error();
            }
            
            size_t      ac = spec.size();
            
            m_data.resize(ac);
            m_pointers.resize(ac, nullptr);
            
            for(size_t n=0; n<ac; ++n){
                const ArgMeta&  ai  = *spec[n];
                const Any&      arg = data[n];
                
                // the fast way
                if(&arg.type() == &ai.type()){
                    m_pointers[n]   = arg.raw_ptr();
                    continue;
                }

                auto v      = arg.convert(static_cast<const TypeMeta&>(ai.type()));
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

