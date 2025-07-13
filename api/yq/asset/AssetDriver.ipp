////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AssetDriver.hpp"
#include "AssetDriverAPI.hpp"
#include "AssetIO.hpp"

namespace yq {

////////////////////////////////////////////////////////////////////////////////

    static string_set_t    make_set(const string_view_initializer_list_t& svs)
    {
        string_set_t ret;
        for(auto& sv : ret)
            ret.insert(std::string(sv));
        return ret;
    }
    

////////////////////////////////////////////////////////////////////////////////

    AssetDriver::AssetDriver(const AssetMeta&asset, string_view_initializer_list_t exts, const std::source_location& loc, Type type) :
        m_asset(asset), m_extensions(make_set(exts)), m_location(loc), m_type(type)
    {
    }
    
    AssetDriver::~AssetDriver()
    {
    }

////////////////////////////////////////////////////////////////////////////////

    AssetInfoer::AssetInfoer(const AssetMeta& asset, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        AssetDriver(asset, exts, sl, type)
    {
    }
    
    AssetInfoer::~AssetInfoer()
    {
    }

////////////////////////////////////////////////////////////////////////////////

    AssetLoader::AssetLoader(const AssetMeta& asset, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        AssetDriver(asset, exts, sl, type)
    {
    }
    
    AssetLoader::~AssetLoader()
    {
    }

////////////////////////////////////////////////////////////////////////////////


    AssetSaver::AssetSaver(const AssetMeta& asset, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        AssetDriver(asset, exts, sl, type)
    {
    }
    
    AssetSaver::~AssetSaver()
    {
    }

////////////////////////////////////////////////////////////////////////////////

    AssetInfoAPI::AssetInfoAPI(const AssetInfoOptions& options) : m_options(options)
    {
    }

    AssetInfoAPI::~AssetInfoAPI()
    {
    }

    bool        AssetInfoAPI::contains(uint32_t k) const
    {
        return m_options.iparams.contains(k);
    }
    
    bool        AssetInfoAPI::contains(const std::string& k) const
    {
        return m_options.sparams.contains(k);
    }

    const Any&  AssetInfoAPI::operator[](uint32_t k) const
    {
        static Any s_null;
        auto itr = m_options.iparams.find(k);
        if(itr == m_options.iparams.end())
            return s_null;
        return itr -> second;
    }
    
    const Any&  AssetInfoAPI::operator[](const std::string&k) const
    {
        static Any s_null;
        auto itr = m_options.sparams.find(k);
        if(itr == m_options.sparams.end())
            return s_null;
        return itr -> second;
    }

////////////////////////////////////////////////////////////////////////////////

    AssetLoadAPI::AssetLoadAPI(const AssetLoadOptions& options) : m_options(options)
    {
    }
    
    AssetLoadAPI::~AssetLoadAPI()
    {
    }

    bool        AssetLoadAPI::contains(uint32_t k) const
    {
        return m_options.iparams.contains(k);
    }
    
    bool        AssetLoadAPI::contains(const std::string&k) const
    {
        return m_options.sparams.contains(k);
    }

    const Any&  AssetLoadAPI::operator[](uint32_t k) const
    {
        static Any s_null;
        auto itr = m_options.iparams.find(k);
        if(itr == m_options.iparams.end())
            return s_null;
        return itr -> second;
    }
    
    const Any&  AssetLoadAPI::operator[](const std::string&k) const
    {
        static Any s_null;
        auto itr = m_options.sparams.find(k);
        if(itr == m_options.sparams.end())
            return s_null;
        return itr -> second;
    }

////////////////////////////////////////////////////////////////////////////////

    AssetSaveAPI::AssetSaveAPI(const AssetSaveOptions& options) : m_options(options)
    {
    }
    
    AssetSaveAPI::~AssetSaveAPI()
    {
    }

    bool        AssetSaveAPI::contains(uint32_t k) const
    {
        return m_options.iparams.contains(k);
    }
    
    bool        AssetSaveAPI::contains(const std::string&k) const
    {
        return m_options.sparams.contains(k);
    }

    const Any&  AssetSaveAPI::operator[](uint32_t k) const
    {
        static Any s_null;
        auto itr = m_options.iparams.find(k);
        if(itr == m_options.iparams.end())
            return s_null;
        return itr -> second;
    }
    
    const Any&  AssetSaveAPI::operator[](const std::string&k) const
    {
        static Any s_null;
        auto itr = m_options.sparams.find(k);
        if(itr == m_options.sparams.end())
            return s_null;
        return itr -> second;
    }

}
