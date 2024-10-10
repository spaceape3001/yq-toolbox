////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/Any.hpp>
#include <yq/core/Global.hpp>
#include <yq/meta/GlobalInfo.hpp>
#include <yq/errors.hpp>

namespace yq::global {
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
        any_x invoke(std::string_view k)
        {
            const MethodInfo*   mi  = info(k);
            if(!mi)
                return errors::name_lookup_failed();
        
            return mi->invoke(const_any_span_t());
        }
        
        any_x invoke(std::string_view k, const std::vector<Any>& args)
        {
            const MethodInfo*   mi  = info(k);
            if(!mi)
                return errors::name_lookup_failed();
            return mi->invoke(args);
        }
        
        any_x invoke(std::string_view k, std::initializer_list<Any> args)
        {
            const MethodInfo*   mi  = info(k);
            if(!mi)
                return errors::name_lookup_failed();

            return mi->invoke(args);
        }

        //! ALL function names
        const string_view_set_t&   names()
        {
            return GlobalInfo::instance().methods().keys;
        }
    }

    namespace variable {

        any_x get(std::string_view k)
        {
            const PropertyInfo* pi  = info(k);
            if(!pi)
                return errors::name_lookup_failed();
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

