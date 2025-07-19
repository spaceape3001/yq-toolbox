////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceKVTreeDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeResource A, typename Pred> 
    class TypedResourceKVTreeInfoer : public ResourceKVTreeInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const KVTree&, const ResourceInfoAPI&)>;
    
        TypedResourceKVTreeInfoer(const string_vector_t& exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            ResourceKVTreeInfoer(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceKVTreeInfoer()
        {
        }

        ResourceInfo* info(const KVTree& file, const ResourceInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceKVTreeInfoerNoAPI : public ResourceKVTreeInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const KVTree&)>;
    
        TypedResourceKVTreeInfoerNoAPI(const string_vector_t& exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            ResourceKVTreeInfoer(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceKVTreeInfoerNoAPI()
        {
        }

        ResourceInfo* info(const KVTree& file, const ResourceInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    

    template <SomeResource A, typename Pred> 
    class TypedResourceKVTreeLoader : public ResourceKVTreeLoader {
    public:
        //using Pred    = std::function<A*(const KVTree&, const ResourceLoadAPI&)>;
        
        TypedResourceKVTreeLoader(const string_vector_t& exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            ResourceKVTreeLoader(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceKVTreeLoader()
        {
        }

        Resource* load(const KVTree& file, const ResourceLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };


    template <SomeResource A, typename Pred> 
    class TypedResourceKVTreeLoaderNoAPI : public ResourceKVTreeLoader {
    public:
        //using Pred    = std::function<A*(const KVTree&)>;
    
        TypedResourceKVTreeLoaderNoAPI(const string_vector_t& exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            ResourceKVTreeLoader(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceKVTreeLoaderNoAPI()
        {
        }

        Resource* info(const KVTree& file, const ResourceLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeResource A, typename Pred> 
    class TypedResourceKVTreeSaver : public ResourceKVTreeSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, KVTree&, const ResourceSaveAPI&)>;

        TypedResourceKVTreeSaver(const string_vector_t& exts, Pred&& fn, bool recurse, const std::source_location& sl) :
            ResourceKVTreeSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceKVTreeSaver()
        {
        }

        std::error_code  save(const Resource& resource, KVTree& bytes, const ResourceSaveAPI& api) const override
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
    class TypedResourceKVTreeSaverNoAPI : public ResourceKVTreeSaver {
        //using Pred    = std::function<std::error_code(const A&, KVTree&)>;

        TypedResourceKVTreeSaverNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceKVTreeSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedResourceKVTreeSaverNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, KVTree& bytes, const ResourceSaveAPI&) const override
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
    class TypedResourceKVTreeSaverBool : public ResourceKVTreeSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, KVTree&, const ResourceSaveAPI&)>;

        TypedResourceKVTreeSaverBool(const string_vector_t& exts, Pred&& fn, bool recurse, const std::source_location& sl) :
            ResourceKVTreeSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceKVTreeSaverBool()
        {
        }

        std::error_code  save(const Resource& resource, KVTree& bytes, const ResourceSaveAPI& api) const override
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
    class TypedResourceKVTreeSaverBoolNoAPI : public ResourceKVTreeSaver {
        //using Pred    = std::function<bool(const A&, KVTree&)>;

        TypedResourceKVTreeSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceKVTreeSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedResourceKVTreeSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, KVTree& bytes, const ResourceSaveAPI&) const override
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
