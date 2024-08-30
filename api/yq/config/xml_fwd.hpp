////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace rapidxml {
    // Forward declarations
    template<class Ch> class xml_node;
    template<class Ch> class xml_attribute;
    template<class Ch> class xml_document;
    template<class Ch> class xml_base;
}

namespace yq {
    using xml_base_t       = rapidxml::xml_base<char>;
    using xml_node_t       = rapidxml::xml_node<char>;
    using xml_attribute_t  = rapidxml::xml_attribute<char>;
    using xml_document_t   = rapidxml::xml_document<char>;

    using XmlBase       [[deprecated]] = rapidxml::xml_base<char>;
    using XmlNode       [[deprecated]] = rapidxml::xml_node<char>;
    using XmlAttribute  [[deprecated]] = rapidxml::xml_attribute<char>;
    using XmlDocument   [[deprecated]] = rapidxml::xml_document<char>;
}
