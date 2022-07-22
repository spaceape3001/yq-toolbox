////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Object.hpp>
#include <basic/XmlSerialize.hpp>

namespace yq {
    class XmlObject : public Object, public XmlSerialize {
        YQ_OBJECT_DECLARE(XmlObject, Object)
    public:
        virtual bool    load(const XmlNode*) override;
        virtual bool    save(XmlNode*) const override;
    };
}
