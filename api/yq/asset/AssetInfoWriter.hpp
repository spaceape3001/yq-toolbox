////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/Asset.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq {
    template <typename C>
    class AssetInfo::Writer : public ObjectInfo::Writer<C> {
    public:
        Writer(AssetInfo* assetInfoPtr) : ObjectInfo::Writer<C>(assetInfoPtr)
        {
        }
        
        Writer(AssetInfo& assetInfoRef) : Writer(&assetInfoRef)
        {
        }
    };

    /////////////////////////////////////////////////////

    template <typename A>
    concept HasCache = 
        requires(A a) {
            { A::cache() };
        };
    
    template <typename A>
    concept HasLoad = 
        requires(A a) {
            { A::load(std::string_view()) };
        };

    template <typename C>
    class Asset::Fixer : public ObjectFixer<C> {
    public:

        Fixer(std::string_view zName, typename C::MyBase::MyInfo& base, const std::source_location& sl=std::source_location::current()) : 
            ObjectFixer<C>(zName, base, sl)
        {
        }
        
        
        virtual AssetFactory*   factory() const override 
        {
            if constexpr (HasCache<C>){
                return &C::cache();
            }
            return nullptr;
        }
        
        virtual AssetCPtr       load(std::string_view sv) const
        {
            if constexpr (HasLoad<C>){
                return C::load(sv);
            }
            return {};
        }
        
    };
}
