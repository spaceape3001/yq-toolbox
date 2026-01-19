////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceUrlDriver.hpp>
#include <yq/errors.hpp>

namespace yq {
    template <SomeResource A, typename Pred> 
    class TypedResourceUrlInfoer : public ResourceUrlInfoer {
    public:
        // using Pred    = std::function<typename A::MyInfo*(const UrlView&, const ResourceInfoAPI&)>;
    
        TypedResourceUrlInfoer(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceUrlInfoer(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceUrlInfoer()
        {
        }

        ResourceInfoPtr info(const UrlView& url, const ResourceInfoAPI& api) const override
        {
            return m_function(url, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceUrlInfoerNoAPI : public ResourceUrlInfoer {
    public:
        // using Pred    = std::function<typename A::MyInfo*(const UrlView&)>;
    
        TypedResourceUrlInfoerNoAPI(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceUrlInfoer(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceUrlInfoerNoAPI()
        {
        }

        ResourceInfoPtr info(const UrlView& url, const ResourceInfoAPI&) const override
        {
            return m_function(url);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeResource A, typename Pred> 
    class TypedResourceUrlLoader : public ResourceUrlLoader {
    public:
        //using Pred    = std::function<A*(const UrlView&, const ResourceLoadAPI&)>;
        
        TypedResourceUrlLoader(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceUrlLoader(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceUrlLoader()
        {
        }

        ResourcePtr load(const UrlView& url, const ResourceLoadAPI& api) const override
        {
            return m_function(url, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceUrlLoaderNoAPI : public ResourceUrlLoader {
    public:
        // using Pred    = std::function<A*(const UrlView&)>;
    
        TypedResourceUrlLoaderNoAPI(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceUrlLoader(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceUrlLoaderNoAPI()
        {
        }

        ResourcePtr info(const UrlView& url, const ResourceLoadAPI&) const override
        {
            return m_function(url);
        }
        
    private:
        Pred          m_function;
    };
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeResource A, typename Pred> 
    class TypedResourceUrlSaver : public ResourceUrlSaver {
    public:
    
        // using Pred    = std::function<std::error_code(const A&, const UrlView&, const ResourceSaveAPI&)>;

        TypedResourceUrlSaver(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceUrlSaver(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceUrlSaver()
        {
        }

        std::error_code  save(const Resource& resource, const UrlView& fp, const ResourceSaveAPI& api) const override
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
    class TypedResourceUrlSaverNoAPI : public ResourceUrlSaver {
        // using Pred    = std::function<std::error_code(const A&, const UrlView&)>;

        TypedResourceUrlSaverNoAPI(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceUrlSaver(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceUrlSaverNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, const UrlView& fp, const ResourceSaveAPI&) const override
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
    class TypedResourceUrlSaverBool : public ResourceUrlSaver {
    public:
        TypedResourceUrlSaverBool(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceUrlSaver(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceUrlSaverBool()
        {
        }

        std::error_code  save(const Resource& resource, const UrlView& fp, const ResourceSaveAPI& api) const override
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
    class TypedResourceUrlSaverBoolNoAPI : public ResourceUrlSaver {
        //using Pred    = std::function<bool(const A&, const UrlView&)>;

        TypedResourceUrlSaverBoolNoAPI(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceUrlSaver(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceUrlSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, const UrlView& fp, const ResourceSaveAPI&) const override
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
