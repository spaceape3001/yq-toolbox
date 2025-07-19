////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ResourceStreamDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeResource A, typename Pred> 
    class TypedResourceStreamInfoer : public ResourceStreamInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(std::istream&, const ResourceInfoAPI&)>;
    
        TypedResourceStreamInfoer(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            ResourceStreamInfoer(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceStreamInfoer()
        {
        }

        ResourceInfo* info(std::istream& file, const ResourceInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceStreamInfoerNoAPI : public ResourceStreamInfoer {
    public:
//        using Pred    = std::function<typename A::MyInfo*(std::istream&)>;
    
        TypedResourceStreamInfoerNoAPI(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            ResourceStreamInfoer(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceStreamInfoerNoAPI()
        {
        }

        ResourceInfo* info(std::istream& file, const ResourceInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceStreamLoader : public ResourceStreamLoader {
    public:
        //using Pred    = std::function<A*(std::istream&, const ResourceLoadAPI&)>;
        
        TypedResourceStreamLoader(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            ResourceStreamLoader(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceStreamLoader()
        {
        }

        Resource* load(std::istream& file, const ResourceLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeResource A, typename Pred> 
    class TypedResourceStreamLoaderNoAPI : public ResourceStreamLoader {
    public:
        //using Pred    = std::function<A*(std::istream&)>;
    
        TypedResourceStreamLoaderNoAPI(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            ResourceStreamLoader(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedResourceStreamLoaderNoAPI()
        {
        }

        Resource* info(std::istream& file, const ResourceLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeResource A, typename Pred> 
    class TypedResourceStreamSaver : public ResourceStreamSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, std::ostream&, const ResourceSaveAPI&)>;

        TypedResourceStreamSaver(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            ResourceStreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedResourceStreamSaver()
        {
        }

        std::error_code  save(const Resource& resource, std::ostream& str, const ResourceSaveAPI& api) const override
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
    class TypedResourceStreamSaverNoAPI : public ResourceStreamSaver {
        //using Pred    = std::function<std::error_code(const A&, std::ostream&)>;

        TypedResourceStreamSaverNoAPI(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            ResourceStreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedResourceStreamSaverNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, std::ostream& str, const ResourceSaveAPI&) const override
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
    class TypedResourceStreamSaverBool : public ResourceStreamSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, std::ostream&, const ResourceSaveAPI&)>;

        TypedResourceStreamSaverBool(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            ResourceStreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedResourceStreamSaverBool()
        {
        }

        std::error_code  save(const Resource& resource, std::ostream& str, const ResourceSaveAPI& api) const override
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

#if 0
    template <SomeResource A>
    void    Resource::add_saver(const string_vector_t& exts, std::function<bool(const A&, std::ostream&, const ResourceSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedResourceStreamSaverBool<A>(exts, std::move(fn), false, sl));
    }
        
    template <SomeResource A>
    void    Resource::add_saver(const string_vector_t& exts, binary_k, std::function<bool(const A&, std::ostream&, const ResourceSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedResourceStreamSaverBool<A>(exts, std::move(fn), true, sl));
    }
#endif
    
    template <SomeResource A, typename Pred> 
    class TypedResourceStreamSaverBoolNoAPI : public ResourceStreamSaver {
        //using Pred    = std::function<bool(const A&, std::ostream&)>;

        TypedResourceStreamSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            ResourceStreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedResourceStreamSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Resource& resource, std::ostream& str, const ResourceSaveAPI&) const override
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
