////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ResourceDriver.hpp"
#include "ResourceDriverAPI.hpp"
#include "ResourceIO.hpp"

namespace yq {

////////////////////////////////////////////////////////////////////////////////

    ResourceDriver::ResourceDriver(const ResourceMeta&resource, const string_vector_t& exts, const std::source_location& loc, Type type) :
        m_resource(resource), m_extensions(exts), m_location(loc), m_type(type)
    {
    }
    
    ResourceDriver::~ResourceDriver()
    {
    }

////////////////////////////////////////////////////////////////////////////////

    ResourceInfoer::ResourceInfoer(const ResourceMeta& resource, const string_vector_t& exts, const std::source_location& sl, Type type) :
        ResourceDriver(resource, exts, sl, type)
    {
    }
    
    ResourceInfoer::~ResourceInfoer()
    {
    }

////////////////////////////////////////////////////////////////////////////////

    ResourceLoader::ResourceLoader(const ResourceMeta& resource, const string_vector_t& exts, const std::source_location& sl, Type type) :
        ResourceDriver(resource, exts, sl, type)
    {
    }
    
    ResourceLoader::~ResourceLoader()
    {
    }

////////////////////////////////////////////////////////////////////////////////


    ResourceSaver::ResourceSaver(const ResourceMeta& resource, const string_vector_t& exts, const std::source_location& sl, Type type) :
        ResourceDriver(resource, exts, sl, type)
    {
    }
    
    ResourceSaver::~ResourceSaver()
    {
    }

////////////////////////////////////////////////////////////////////////////////

    ResourceInfoAPI::ResourceInfoAPI(const ResourceInfoOptions& options) : m_options(options)
    {
    }

    ResourceInfoAPI::~ResourceInfoAPI()
    {
    }

    bool        ResourceInfoAPI::contains(uint32_t k) const
    {
        return m_options.iparams.contains(k);
    }
    
    bool        ResourceInfoAPI::contains(const std::string& k) const
    {
        return m_options.sparams.contains(k);
    }

    const Any&  ResourceInfoAPI::operator[](uint32_t k) const
    {
        static Any s_null;
        auto itr = m_options.iparams.find(k);
        if(itr == m_options.iparams.end())
            return s_null;
        return itr -> second;
    }
    
    const Any&  ResourceInfoAPI::operator[](const std::string&k) const
    {
        static Any s_null;
        auto itr = m_options.sparams.find(k);
        if(itr == m_options.sparams.end())
            return s_null;
        return itr -> second;
    }

////////////////////////////////////////////////////////////////////////////////

    ResourceLoadAPI::ResourceLoadAPI(const ResourceLoadOptions& options) : m_options(options)
    {
    }
    
    ResourceLoadAPI::~ResourceLoadAPI()
    {
    }

    bool        ResourceLoadAPI::contains(uint32_t k) const
    {
        return m_options.iparams.contains(k);
    }
    
    bool        ResourceLoadAPI::contains(const std::string&k) const
    {
        return m_options.sparams.contains(k);
    }

    const Any&  ResourceLoadAPI::operator[](uint32_t k) const
    {
        static Any s_null;
        auto itr = m_options.iparams.find(k);
        if(itr == m_options.iparams.end())
            return s_null;
        return itr -> second;
    }
    
    const Any&  ResourceLoadAPI::operator[](const std::string&k) const
    {
        static Any s_null;
        auto itr = m_options.sparams.find(k);
        if(itr == m_options.sparams.end())
            return s_null;
        return itr -> second;
    }

////////////////////////////////////////////////////////////////////////////////

    ResourceSaveAPI::ResourceSaveAPI(const ResourceSaveOptions& options) : m_options(options)
    {
    }
    
    ResourceSaveAPI::~ResourceSaveAPI()
    {
    }

    bool        ResourceSaveAPI::contains(uint32_t k) const
    {
        return m_options.iparams.contains(k);
    }
    
    bool        ResourceSaveAPI::contains(const std::string&k) const
    {
        return m_options.sparams.contains(k);
    }

    const Any&  ResourceSaveAPI::operator[](uint32_t k) const
    {
        static Any s_null;
        auto itr = m_options.iparams.find(k);
        if(itr == m_options.iparams.end())
            return s_null;
        return itr -> second;
    }
    
    const Any&  ResourceSaveAPI::operator[](const std::string&k) const
    {
        static Any s_null;
        auto itr = m_options.sparams.find(k);
        if(itr == m_options.sparams.end())
            return s_null;
        return itr -> second;
    }

}
