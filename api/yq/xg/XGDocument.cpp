////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGDocBase.hpp"
#include "XGDocument.hpp"
#include <yq/resource/ResourceMetaWriter.hpp>

YQ_RESOURCE_IMPLEMENT(yq::XGDocument)

namespace yq {

    XGDocBase::XGDocBase() = default;
    XGDocBase::XGDocBase(const XGDocBase&) = default;
    XGDocBase::XGDocBase(XGDocBase&&) = default;
    XGDocBase::~XGDocBase() = default;
    XGDocBase& XGDocBase::operator=(const XGDocBase&) = default;
    XGDocBase& XGDocBase::operator=(XGDocBase&&) = default;
    bool    XGDocBase::operator==(const XGDocBase&) const = default;

    ////////////////////////////////////////////////
    
    void XGDocument::init_meta()
    {
        auto w = writer<XGDocument>();
        w.description("Execution Graph Document");
    }

    XGDocument::XGDocument() 
    {
    }
    
    XGDocument::XGDocument(const XGDocument&cp ) : Resource(), XGDocDoc(cp)
    {
    }

    XGDocument::~XGDocument()
    {
    }

    size_t  XGDocument::data_size() const 
    {
        return 0;   // TODO
    }
    
}
