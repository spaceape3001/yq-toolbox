////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceXmlDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeResource A, typename Pred> 
    class TypedResourceXmlInfoer : public ResourceXmlInfoer {
    public:
        TypedResourceXmlInfoer(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceXmlInfoer(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceXmlInfoer()
        {
        }

        ResourceInfoPtr info(const XmlDocument& file, const ResourceInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceXmlInfoerNoAPI : public ResourceXmlInfoer {
    public:
        TypedResourceXmlInfoerNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceXmlInfoer(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceXmlInfoerNoAPI()
        {
        }

        ResourceInfoPtr info(const XmlDocument& file, const ResourceInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeResource A, typename Pred> 
    class TypedResourceXmlLoader : public ResourceXmlLoader {
    public:
        TypedResourceXmlLoader(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceXmlLoader(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceXmlLoader()
        {
        }

        ResourcePtr load(const XmlDocument& file, const ResourceLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceXmlLoaderNoAPI : public ResourceXmlLoader {
    public:
        TypedResourceXmlLoaderNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceXmlLoader(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceXmlLoaderNoAPI()
        {
        }

        ResourcePtr load(const XmlDocument& file, const ResourceLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };

////////////////////////////////////////////////////////////////////////////////

    template <SomeResource A, typename Pred> 
    class TypedResourceXmlSaver : public ResourceXmlSaver {
    public:
        TypedResourceXmlSaver(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceXmlSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedResourceXmlSaver()
        {
        }

        std::error_code  save(const Resource& resource, XmlDocument& fp, const ResourceSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, fp, api);
        }
        

    private:
        Pred          m_function;
    };
    
    template <SomeResource A, typename Pred> 
    class TypedResourceXmlSaverNoAPI : public ResourceXmlSaver {
    public:
        TypedResourceXmlSaverNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceXmlSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedResourceXmlSaverNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, XmlDocument& fp, const ResourceSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, fp);
        }
        

    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceXmlSaverBool : public ResourceXmlSaver {
    public:
    
        TypedResourceXmlSaverBool(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceXmlSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedResourceXmlSaverBool()
        {
        }

        std::error_code  save(const Resource& resource, XmlDocument& fp, const ResourceSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, fp, api))
                return errors::resource_saving_failed();
            return {};
        }
        

    private:
        Pred          m_function;
    };
    
    template <SomeResource A, typename Pred> 
    class TypedResourceXmlSaverBoolNoAPI : public ResourceXmlSaver {
    public:
    
        TypedResourceXmlSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceXmlSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedResourceXmlSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, XmlDocument& fp, const ResourceSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, fp))
                return errors::resource_saving_failed();
            return {};
        }
        

    private:
        Pred          m_function;
    };
}
