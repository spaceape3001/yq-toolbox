////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/basic/XmlObject.hpp>
#include <yq/basic/DelayInit.hpp>
#include <0/meta/ObjectInfoWriter.hpp>

namespace yq {

    bool    XmlObject::load(const XmlNode&)
    {
        return true;
    }
    
    bool    XmlObject::save(XmlNode&) const
    {
        return true;
    }
    
}

YQ_OBJECT_IMPLEMENT(yq::XmlObject)

YQ_INVOKE(
    auto w   = yq::writer<yq::XmlObject>();
    w.abstract();
)

