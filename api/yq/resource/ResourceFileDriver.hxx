////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceFileDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeResource A, typename Pred> 
    class TypedResourceFileInfoer : public ResourceFileInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const std::filesystem::path&, const ResourceInfoAPI&)>;
    
        TypedResourceFileInfoer(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceFileInfoer(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceFileInfoer()
        {
        }

        ResourceInfo* info(const std::filesystem::path& file, const ResourceInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    
    template <SomeResource A, typename Pred> 
    class TypedResourceFileInfoerNoAPI : public ResourceFileInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const std::filesystem::path&)>;
    
        TypedResourceFileInfoerNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceFileInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceFileInfoerNoAPI()
        {
        }

        ResourceInfo* info(const std::filesystem::path& file, const ResourceInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceFileLoader : public ResourceFileLoader {
    public:
        //using Pred    = std::function<A*(const std::filesystem::path&, const ResourceLoadAPI&)>;
        
        TypedResourceFileLoader(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceFileLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceFileLoader()
        {
        }

        Resource* load(const std::filesystem::path& file, const ResourceLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceFileLoaderNoAPI : public ResourceFileLoader {
    public:
        //using Pred    = std::function<A*(const std::filesystem::path&)>;
    
        TypedResourceFileLoaderNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceFileLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceFileLoaderNoAPI()
        {
        }

        Resource* load(const std::filesystem::path& file, const ResourceLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    

////////////////////////////////////////////////////////////////////////////////

    template <SomeResource A, typename Pred> 
    class TypedResourceFileSaver : public ResourceFileSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, const std::filesystem::path&, const ResourceSaveAPI&)>;

        TypedResourceFileSaver(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceFileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceFileSaver()
        {
        }

        std::error_code  save(const Resource& resource, const std::filesystem::path& fp, const ResourceSaveAPI& api) const override
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
    class TypedResourceFileSaverNoAPI : public ResourceFileSaver {
    public:
        //using Pred    = std::function<std::error_code(const A&, const std::filesystem::path&)>;

        TypedResourceFileSaverNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceFileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceFileSaverNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, const std::filesystem::path& fp, const ResourceSaveAPI&) const override
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
    class TypedResourceFileSaverBool : public ResourceFileSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, const std::filesystem::path&, const ResourceSaveAPI&)>;

        TypedResourceFileSaverBool(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceFileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceFileSaverBool()
        {
        }

        std::error_code  save(const Resource& resource, const std::filesystem::path& fp, const ResourceSaveAPI& api) const override
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
    class TypedResourceFileSaverBoolNoAPI : public ResourceFileSaver {
    public:
        //using Pred    = std::function<bool(const A&, const std::filesystem::path&)>;

        TypedResourceFileSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceFileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceFileSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, const std::filesystem::path& fp, const ResourceSaveAPI&) const override
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
