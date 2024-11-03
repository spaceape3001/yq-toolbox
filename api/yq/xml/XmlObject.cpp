////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/meta/ObjectInfoWriter.hpp>
#include <yq/xml/XmlObject.hpp>

namespace yq {

    bool    XmlObject::load(const XmlNode&)
    {
        return true;
    }
    
    bool    XmlObject::save(XmlNode&) const
    {
        return true;
    }
    
    void    XmlObject::init_info()
    {
        auto w = writer<XmlObject>();
        w.abstract();
        w.description("Xml based object");
    }

}

YQ_OBJECT_IMPLEMENT(yq::XmlObject)

