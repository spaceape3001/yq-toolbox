////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceJsonDriver.hpp>
#include <yq/errors.hpp>

namespace yq {
    template <SomeResource A, typename Pred> 
    class TypedResourceJsonInfoer : public ResourceJsonInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const json&, const ResourceInfoAPI&)>;
    
        TypedResourceJsonInfoer(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceJsonInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceJsonInfoer()
        {
        }

        ResourceInfoPtr info(const json& file, const ResourceInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeResource A, typename Pred> 
    class TypedResourceJsonInfoerNoAPI : public ResourceJsonInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const json&)>;
    
        TypedResourceJsonInfoerNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceJsonInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceJsonInfoerNoAPI()
        {
        }

        ResourceInfoPtr info(const json& file, const ResourceInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeResource A, typename Pred> 
    class TypedResourceJsonLoader : public ResourceJsonLoader {
    public:
        //using Pred    = std::function<A*(const json&, const ResourceLoadAPI&)>;
        
        TypedResourceJsonLoader(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceJsonLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceJsonLoader()
        {
        }

        ResourcePtr load(const json& file, const ResourceLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeResource A, typename Pred> 
    class TypedResourceJsonLoaderNoAPI : public ResourceJsonLoader {
    public:
        //using Pred    = std::function<A*(const json&)>;
    
        TypedResourceJsonLoaderNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceJsonLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceJsonLoaderNoAPI()
        {
        }

        ResourcePtr load(const json& file, const ResourceLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeResource A, typename Pred> 
    class TypedResourceJsonSaver : public ResourceJsonSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, json&, const ResourceSaveAPI&)>;

        TypedResourceJsonSaver(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceJsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceJsonSaver()
        {
        }

        std::error_code  save(const Resource& resource, json& fp, const ResourceSaveAPI& api) const override
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
    class TypedResourceJsonSaverNoAPI : public ResourceJsonSaver {
        //using Pred    = std::function<std::error_code(const A&, json&)>;

        TypedResourceJsonSaverNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceJsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceJsonSaverNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, json& fp, const ResourceSaveAPI&) const override
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
    class TypedResourceJsonSaverBool : public ResourceJsonSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, json&, const ResourceSaveAPI&)>;

        TypedResourceJsonSaverBool(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceJsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceJsonSaverBool()
        {
        }

        std::error_code  save(const Resource& resource, json& fp, const ResourceSaveAPI& api) const override
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
    class TypedResourceJsonSaverBoolNoAPI : public ResourceJsonSaver {
        //using Pred    = std::function<bool(const A&, json&)>;

        TypedResourceJsonSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceJsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceJsonSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, json& fp, const ResourceSaveAPI&) const override
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
