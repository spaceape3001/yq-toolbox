////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceByteDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeResource A, typename Pred> 
    class TypedResourceByteInfoer : public ResourceByteInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const ByteArray&, const ResourceInfoAPI&)>;
    
        TypedResourceByteInfoer(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceByteInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceByteInfoer()
        {
        }

        ResourceInfo* info(const ByteArray& file, const ResourceInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    
    template <SomeResource A, typename Pred> 
    class TypedResourceByteInfoerNoAPI : public ResourceByteInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const ByteArray&)>;
    
        TypedResourceByteInfoerNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceByteInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceByteInfoerNoAPI()
        {
        }

        ResourceInfo* info(const ByteArray& file, const ResourceInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    

    template <SomeResource A, typename Pred> 
    class TypedResourceByteLoader : public ResourceByteLoader {
    public:
        //using Pred    = std::function<A*(const ByteArray&, const ResourceLoadAPI&)>;
        
        TypedResourceByteLoader(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceByteLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceByteLoader()
        {
        }

        Resource* load(const ByteArray& file, const ResourceLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    
    template <SomeResource A, typename Pred> 
    class TypedResourceByteLoaderNoAPI : public ResourceByteLoader {
    public:
        //using Pred    = std::function<A*(const ByteArray&)>;
    
        TypedResourceByteLoaderNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceByteLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceByteLoaderNoAPI()
        {
        }

        Resource* info(const ByteArray& file, const ResourceLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeResource A, typename Pred> 
    class TypedResourceByteSaver : public ResourceByteSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, ByteArray&, const ResourceSaveAPI&)>;

        TypedResourceByteSaver(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceByteSaver()
        {
        }

        std::error_code  save(const Resource& resource, ByteArray& bytes, const ResourceSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, bytes, api);
        }
        

    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceByteSaverNoAPI : public ResourceByteSaver {
        //using Pred    = std::function<std::error_code(const A&, ByteArray&)>;

        TypedResourceByteSaverNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceByteSaverNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, ByteArray& bytes, const ResourceSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, bytes);
        }
        

    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceByteSaverBool : public ResourceByteSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, ByteArray&, const ResourceSaveAPI&)>;

        TypedResourceByteSaverBool(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceByteSaverBool()
        {
        }

        std::error_code  save(const Resource& resource, ByteArray& bytes, const ResourceSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, bytes, api))
                return errors::resource_saving_failed();
            return {};
        }
        

    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceByteSaverBoolNoAPI : public ResourceByteSaver {
        //using Pred    = std::function<bool(const A&, ByteArray&)>;

        TypedResourceByteSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceByteSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, ByteArray& bytes, const ResourceSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&resource);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, bytes))
                return errors::resource_saving_failed();
            return {};
        }
        

    private:
        Pred          m_function;
    };
}
