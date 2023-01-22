////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Global.hpp>
#include <basic/meta/GlobalInfo.hpp>
#include <basic/Errors.hpp>

namespace yq {
    namespace global {
        namespace function {
        
            const MethodInfo*           info(std::string_view k)
            {
                return GlobalInfo::instance().methods().lut.first(k, nullptr);
            }
            
            
            const std::vector<const MethodInfo*>& infos()
            {
                return GlobalInfo::instance().methods().all;
            }

            std::vector<const MethodInfo*>  infos(std::string_view k)
            {
                return GlobalInfo::instance().methods().lut.get(k);
            }
            
            //! Invokes the specified name
            std::pair<Any,std::error_code>  invoke(std::string_view k)
            {
                return { Any(), errors::todo() };
            }
            
            std::pair<Any,std::error_code>  invoke(std::string_view k, const std::vector<Any>&)
            {
                return { Any(), errors::todo() };
            }
            
            std::pair<Any,std::error_code>  invoke(std::string_view k, std::initializer_list<Any>)
            {
                return { Any(), errors::todo() };
            }
    
            //! ALL function names
            const string_view_set_t&   names()
            {
                return GlobalInfo::instance().methods().keys;
            }
        }

        namespace variable {

            std::pair<Any,std::error_code>  get(std::string_view k)
            {
                const PropertyInfo* pi  = info(k);
                if(!pi)
                    return { Any(), errors::name_lookup_failed() };
                return pi -> get(nullptr);
            }
        
            const string_view_set_t&   names()
            {
                return GlobalInfo::instance().properties().keys;
            }
            
            //! Gets the varaible information
            const PropertyInfo* info(std::string_view k)
            {   
                return GlobalInfo::instance().properties().lut.first(k);
            }

            //! Informantion to ALL variables
            const std::vector<const PropertyInfo*>& infos()
            {
                return GlobalInfo::instance().properties().all;
            }

            //! Sets the variable
            std::error_code    set(std::string_view k, const Any&v)
            {
                const PropertyInfo* pi = info(k);
                if(!pi)
                    return errors::name_lookup_failed();
                
                return pi->set(nullptr, v);
            }

            std::error_code    set(std::string_view k, std::string_view v)
            {
                const PropertyInfo* pi = info(k);
                if(!pi)
                    return errors::name_lookup_failed();
                
                return pi->set(nullptr, v);
            }
        }
    }
}

