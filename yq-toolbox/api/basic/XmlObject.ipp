////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/XmlObject.hpp>
#include <basic/DelayInit.hpp>
#include <basic/meta/ObjectInfoWriter.hpp>

namespace yq {

    bool    XmlObject::load(const XmlNode*)
    {
        return true;
    }
    
    bool    XmlObject::save(XmlNode*) const
    {
        return true;
    }
    
}

YQ_OBJECT_IMPLEMENT(yq::XmlObject)

YQ_INVOKE(
    yq::writer<yq::XmlObject>().abstract();
)

