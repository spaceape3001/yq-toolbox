////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGDocument.hpp"
#include <yq/resource/ResourceMetaWriter.hpp>

YQ_RESOURCE_IMPLEMENT(yq::xg::XGDocument)

namespace yq::xg {
    XGDocItem::XGDocItem(Type t) : type(t)
    {
    }
    
    XGDocItem::~XGDocItem()
    {
    }
    
    void XGDocument::init_meta()
    {
        auto w = writer<XGDocument>();
        w.description("Execution Graph Document");
    }

    
    XGDocument::XGDocument() : content(XGDocItem::Type::Document)
    {
    }
    
    XGDocument::~XGDocument()
    {
    }
}
