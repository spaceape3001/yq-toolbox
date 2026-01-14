////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGDocument.hpp"
#include "XGXmlIO.hpp"
#include <yq/errors.hpp>

namespace yq {

    xg_document_ptr_x   loadXGXML(const std::filesystem::path&)
    {
        return errors::todo();
    }
    
    xg_document_ptr_x   loadXGXML(const XmlDocument&, const Url&)
    {
        return errors::todo();
    }

    bool                saveXGXML(const XGDocument&, const std::filesystem::path&)
    {
        return false;
    }
    
    bool                saveXGXML(const XGDocument&, XmlDocument&)
    {
        return false;
    }
}
