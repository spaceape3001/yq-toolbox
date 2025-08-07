////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/Obj.hpp>
#include <yq/art/AbstractMetaWriter.hpp>
#include <type_traits>

namespace yq::art {
    template <typename C>
    class ObjMeta::Writer : public AbstractMeta::Writer<C> {
    public:
        Writer(ObjMeta* dInfo) : AbstractMeta::Writer<C>(dInfo), m_meta(dInfo)
        {
        }
        
        Writer(ObjMeta& dInfo) : Writer(&dInfo)
        {
        }

    private:
        ObjMeta*    m_meta;
    };

    template <typename D>
    class ObjFixer : public ObjectFixer<D> {
    public:
        ObjFixer(std::string_view szName, typename D::MyBase::MyMeta& myBase, const std::source_location& sl = std::source_location::current()) :
            ObjectFixer<D>(szName, myBase, sl)
        {
        }

        #if 0
            // pending....
        virtual Obj*        clone(const Obj* obj) const
        {
            if constexpr (!std::is_abstract_v<D>){
                
            } 
            return nullptr;
        }
        #endif

        virtual Obj*        create(Doc& doc) const
        {
            if constexpr (!std::is_abstract_v<D>){
                return new D(doc);
            } 
            return nullptr;
        }
    };
}

