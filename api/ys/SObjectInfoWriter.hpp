////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/SObject.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq::spatial {
    template <typename C>
    class SObjectInfo::Writer : public ObjectInfo::Writer<C> {
    public:
        Writer(SObjectInfo* dInfo) : ObjectInfo::Writer<C>(dInfo), m_meta(dInfo)
        {
        }
        
        Writer(SObjectInfo& dInfo) : Writer(&dInfo)
        {
        }
        
        Writer& support_0d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D0;
            return *this;
        }
        
        Writer& support_1d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D1;
            return *this;
        }

        Writer& support_2d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D2;
            return *this;
        }

        Writer& support_3d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D3;
            return *this;
        }

        Writer& support_4d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D4;
            return *this;
        }

        Writer& support_5d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D5;
            return *this;
        }

        Writer& support_6d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D6;
            return *this;
        }
    private:
        SObjectInfo*    m_meta;
    };
    
    template <typename Obj>
    class SObjectFixer : public ObjectFixer<Obj> {
    public:
        SObjectFixer(std::string_view szName, typename Obj::MyBase::MyInfo& myBase, std::source_location sl=std::source_location::current()) : 
            ObjectFixer<Obj>(szName, myBase, sl) 
        {
        }

        
        virtual SObject* create(SDocument&prj) const override
        {
            if constexpr (std::is_constructible_v<Obj, SDocument&> && !std::is_abstract_v<Obj>) {
                if(ObjectInfo::is_abstract())
                    return nullptr;
                return new Obj(prj);
            } else
                return nullptr;
        }
        
        virtual SObject* copy(SDocument&prj, const SObject&obj) const override
        {
            if constexpr (std::is_constructible_v<Obj, SDocument&, const Obj&> && !std::is_abstract_v<Obj>) {
                if(ObjectInfo::is_abstract())
                    return nullptr;
                return new Obj(prj, static_cast<const Obj&>(obj));
            } else
                return nullptr;
        }
    };
}
