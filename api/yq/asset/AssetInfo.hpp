////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/asset.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/Ref.hpp>
#include <yq/net/Url.hpp>

namespace yq {
    class AssetInfoMeta : public ObjectMeta {
    public:
        template <typename> class Writer;
        
        //! Constructor of asset info, used by the meta system to initialize the thing (so... don't need to call this outside of that context)
        AssetInfoMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());

        const AssetInfo*        asset() const { return m_asset; }
        
    private:
        const AssetInfo*        m_asset = nullptr;
    };
    

    //! Meant to be a *LIGHTWEIGHT* container for getting information about an asset.
    class AssetInfo : public Object, public RefCount {
        YQ_OBJECT_META(AssetInfoMeta)
        YQ_OBJECT_DECLARE(AssetInfo, Object)
    public:
        
        const Url&  url() const { return m_url; }
        
        //! Estimated data size (error on overcounting if unsure)
        size_t      bytes() const { return m_bytes; }

        static void init_meta();
        
        //! ID of the asset (if loaded), zero otherwise
        uint64_t    id() const { return m_id; }
    
        AssetInfo();
        virtual ~AssetInfo();
    
    private:
        Url                 m_url;
        size_t              m_bytes  = SIZE_MAX;
        uint64_t            m_id        = 0;
    };
}
