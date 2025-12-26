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
    
    void XGDocument::init_meta()
    {
        auto w = writer<XGDocument>();
        w.description("Execution Graph Document");
    }

    
    XGDocument::XGDocument() 
    {
    }
    
    XGDocument::~XGDocument()
    {
    }
}
