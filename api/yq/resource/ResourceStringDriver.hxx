////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceStringDriver.hpp>
#include <yq/errors.hpp>

namespace yq {
    template <SomeResource A, typename Pred> 
    class TypedResourceStringInfoer : public ResourceStringInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const std::string&, const ResourceInfoAPI&)>;
    
        TypedResourceStringInfoer(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceStringInfoer(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceStringInfoer()
        {
        }

        ResourceInfoPtr info(const std::string& file, const ResourceInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeResource A, typename Pred> 
    class TypedResourceStringInfoerNoAPI : public ResourceStringInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const std::string&)>;
    
        TypedResourceStringInfoerNoAPI(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceStringInfoer(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceStringInfoerNoAPI()
        {
        }

        ResourceInfoPtr info(const std::string& file, const ResourceInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceStringLoader : public ResourceStringLoader {
    public:
        //using Pred    = std::function<A*(const std::string&, const ResourceLoadAPI&)>;
        
        TypedResourceStringLoader(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceStringLoader(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceStringLoader()
        {
        }

        ResourcePtr load(const std::string& file, const ResourceLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceStringLoaderNoAPI : public ResourceStringLoader {
    public:
        //using Pred    = std::function<A*(const std::string&)>;
    
        TypedResourceStringLoaderNoAPI(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceStringLoader(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceStringLoaderNoAPI()
        {
        }

        ResourcePtr info(const std::string& file, const ResourceLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeResource A, typename Pred> 
    class TypedResourceStringSaver : public ResourceStringSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, std::string&, const ResourceSaveAPI&)>;

        TypedResourceStringSaver(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceStringSaver(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceStringSaver()
        {
        }

        std::error_code  save(const Resource& resource, std::string& str, const ResourceSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, str, api);
        }
        

    private:
        Pred          m_function;
    };

    
    template <SomeResource A, typename Pred> 
    class TypedResourceStringSaverNoAPI : public ResourceStringSaver {
        //using Pred    = std::function<std::error_code(const A&, std::string&)>;

        TypedResourceStringSaverNoAPI(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceStringSaver(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceStringSaverNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, std::string& str, const ResourceSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, str);
        }
        

    private:
        Pred          m_function;
    };


    template <SomeResource A, typename Pred> 
    class TypedResourceStringSaverBool : public ResourceStringSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, std::string&, const ResourceSaveAPI&)>;

        TypedResourceStringSaverBool(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceStringSaver(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceStringSaverBool()
        {
        }

        std::error_code  save(const Resource& resource, std::string& str, const ResourceSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, str, api))
                return errors::resource_saving_failed();
            return {};
        }
        

    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceStringSaverBoolNoAPI : public ResourceStringSaver {
        //using Pred    = std::function<bool(const A&, std::string&)>;

        TypedResourceStringSaverBoolNoAPI(const ResourceIOSpec& spec, Pred&& fn, const std::source_location& sl) :
            ResourceStringSaver(meta<A>(), spec, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceStringSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, std::string& str, const ResourceSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, str))
                return errors::resource_saving_failed();
            return {};
        }
        

    private:
        Pred          m_function;
    };
}
