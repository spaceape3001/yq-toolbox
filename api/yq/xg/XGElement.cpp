////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGElement.hpp"
#include "XGElementMetaWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::XGElement)

namespace yq {
    void XGElement::init_meta()
    {
        auto w = writer<XGElement>();
        w.description("Executive Graph Element");
    }

    XGElement::XGElement()
    {
    }
    
    XGElement::~XGElement()
    {
    }

    xg_result_t    XGElement::execute(XGContext&)
    {
        return {};
    }

    bool    XGElement::initialize(const XGDocNode&)
    {
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////

    struct XGElementMeta::Repo {
        MetaLookup<XGElementMeta>   elements;
    };
    
    const std::vector<const XGElementMeta*>& XGElementMeta::all()
    {
        return repo().elements.all;
    }

    XGElementMeta::Repo&    XGElementMeta::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    XGElementMeta::XGElementMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) : 
        ObjectMeta(zName, base, sl)
    {
        repo().elements << this;
    }
}
