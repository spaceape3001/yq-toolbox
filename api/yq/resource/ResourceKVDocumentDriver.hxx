////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceKVDocumentDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeResource A, typename Pred> 
    class TypedResourceKVDocumentInfoer : public ResourceKVDocumentInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const KVDocument&, const ResourceInfoAPI&)>;
    
        TypedResourceKVDocumentInfoer(const string_vector_t& exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            ResourceKVDocumentInfoer(meta<A>(), exts, sl, recursive), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceKVDocumentInfoer()
        {
        }

        ResourceInfoPtr info(const KVDocument& file, const ResourceInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceKVDocumentInfoerNoAPI : public ResourceKVDocumentInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const KVDocument&)>;
    
        TypedResourceKVDocumentInfoerNoAPI(const string_vector_t& exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            ResourceKVDocumentInfoer(meta<A>(), exts, sl, recursive), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceKVDocumentInfoerNoAPI()
        {
        }

        ResourceInfoPtr info(const KVDocument& file, const ResourceInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    

    template <SomeResource A, typename Pred> 
    class TypedResourceKVDocumentLoader : public ResourceKVDocumentLoader {
    public:
        //using Pred    = std::function<A*(const KVDocument&, const ResourceLoadAPI&)>;
        
        TypedResourceKVDocumentLoader(const string_vector_t& exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            ResourceKVDocumentLoader(meta<A>(), exts, sl, recursive), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceKVDocumentLoader()
        {
        }

        ResourcePtr load(const KVDocument& file, const ResourceLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };


    template <SomeResource A, typename Pred> 
    class TypedResourceKVDocumentLoaderNoAPI : public ResourceKVDocumentLoader {
    public:
        //using Pred    = std::function<A*(const KVDocument&)>;
    
        TypedResourceKVDocumentLoaderNoAPI(const string_vector_t& exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            ResourceKVDocumentLoader(meta<A>(), exts, sl, recursive), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceKVDocumentLoaderNoAPI()
        {
        }

        ResourcePtr info(const KVDocument& file, const ResourceLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
    //template <SomeResource A>
    //void    Resource::add_loader(const string_vector_t& exts, std::function<A*(const KVDocument&)>&&fn, const std::source_location& sl) 
    //{
        //add_loader(new TypedResourceKVDocumentLoaderNoAPI<A>(exts, std::move(fn), false, sl));
    //}
    
    //template <SomeResource A>
    //void    Resource::add_loader(const string_vector_t& exts, recursive_k, std::function<A*(const KVDocument&)>&&fn, const std::source_location& sl) 
    //{
        //add_loader(new TypedResourceKVDocumentLoaderNoAPI<A>(exts, std::move(fn), true, sl));
    //}

////////////////////////////////////////////////////////////////////////////////

    template <SomeResource A, typename Pred> 
    class TypedResourceKVDocumentSaver : public ResourceKVDocumentSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, KVDocument&, const ResourceSaveAPI&)>;

        TypedResourceKVDocumentSaver(const string_vector_t& exts, Pred&& fn, bool recurse, const std::source_location& sl) :
            ResourceKVDocumentSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceKVDocumentSaver()
        {
        }

        std::error_code  save(const Resource& resource, KVDocument& bytes, const ResourceSaveAPI& api) const override
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
    class TypedResourceKVDocumentSaverNoAPI : public ResourceKVDocumentSaver {
        //using Pred    = std::function<std::error_code(const A&, KVDocument&)>;

        TypedResourceKVDocumentSaverNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceKVDocumentSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceKVDocumentSaverNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, KVDocument& bytes, const ResourceSaveAPI&) const override
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
    class TypedResourceKVDocumentSaverBool : public ResourceKVDocumentSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, KVDocument&, const ResourceSaveAPI&)>;

        TypedResourceKVDocumentSaverBool(const string_vector_t& exts, Pred&& fn, bool recurse, const std::source_location& sl) :
            ResourceKVDocumentSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceKVDocumentSaverBool()
        {
        }

        std::error_code  save(const Resource& resource, KVDocument& bytes, const ResourceSaveAPI& api) const override
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
    class TypedResourceKVDocumentSaverBoolNoAPI : public ResourceKVDocumentSaver {
//        using Pred    = std::function<bool(const A&, KVDocument&)>;

        TypedResourceKVDocumentSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            ResourceKVDocumentSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedResourceKVDocumentSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, KVDocument& bytes, const ResourceSaveAPI&) const override
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
