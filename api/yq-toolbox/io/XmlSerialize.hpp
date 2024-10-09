////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/xml.hpp>

namespace yq {

    // Base class for xml serialization
    struct XmlSerialize {
        virtual bool    load(const XmlNode&) { return true; }
        virtual bool    save(XmlNode&) const { return true; }
    };
}

