////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/xml.hpp>
#include <yq/core/Object.hpp>
#include <yq/xml/XmlSerialize.hpp>

namespace yq {
    class XmlObject : public Object, public XmlSerialize {
        YQ_OBJECT_DECLARE(XmlObject, Object)
    public:
        virtual bool    load(const XmlNode&) override;
        virtual bool    save(XmlNode&) const override;
        
        static void init_info();
    };
}
