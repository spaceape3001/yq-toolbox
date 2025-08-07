////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/Doc.hpp>
#include <yq/art/AbstractMetaWriter.hpp>

namespace yq::art {
    template <typename C>
    class DocMeta::Writer : public AbstractMeta::Writer<C> {
    public:
        Writer(DocMeta* dInfo) : AbstractMeta::Writer<C>(dInfo), m_meta(dInfo)
        {
        }
        
        Writer(DocMeta& dInfo) : Writer(&dInfo)
        {
        }

    private:
        DocMeta*    m_meta;
    };
    
    template <typename D>
    class DocFixer : public ObjectFixer<D> {
    public:
        DocFixer(std::string_view szName, typename D::MyBase::MyMeta& myBase, const std::source_location& sl = std::source_location::current()) :
            ObjectFixer<D>(szName, myBase, sl)
        {
        }
    };
}

