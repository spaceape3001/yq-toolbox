////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/Asset.hpp>
#include <yq/asset/AssetInfoMetaWriter.hpp>

namespace yq {
    template <typename C>
    class AssetMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(AssetMeta* assetInfoPtr) : ObjectMeta::Writer<C>(assetInfoPtr)
        {
        }
        
        Writer(AssetMeta& assetInfoRef) : Writer(&assetInfoRef)
        {
        }
    };

    template <typename C> 
    class AssetFixer : public ObjectFixer<C> {
    public:
    
        AssetFixer(std::string_view zName, typename C::MyBase::MyMeta& base, const std::source_location& sl=std::source_location::current()) : 
            ObjectFixer<C>(zName, base, sl)
        {
        }
        
        virtual AssetInfo*  createInfo() const 
        { 
            return new typename C::MyInfo; 
        }
        
        virtual void        sweep_impl()
        {
            ObjectFixer<C>::sweep_impl();
            auto w = writer<typename C::MyInfo>();
            w.template asset<C>();
        }
    };
}
