////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/typedef/xml.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <system_error>

namespace yq {
    //! Writes the contents of the buffer to the attribute's value
    std::error_code write_xml(unsafe_k, XmlAttribute&, const TypeMeta&, const void*);

    //! Writes the contents of the buffer to the xml's value
    std::error_code write_xml(unsafe_k, XmlBase&, const TypeMeta&, const void*);

    //! Writes the contents of the buffer to the node's value
    std::error_code write_xml(unsafe_k, XmlNode&, const TypeMeta&, const void*);
    
    //! Writes the contents of the ANY to the attribute
    //! \note DOES NOT DO ANY TYPE ATTRIBUTES
    std::error_code write_xml_any(XmlAttribute&, const Any&);
    
    //! Writes the contents of the ANY to the xml thing
    //! \note DOES NOT DO ANY TYPE ATTRIBUTES
    std::error_code write_xml_any(XmlBase&, const Any&);

    //! Writes the contents of the ANY to the xml node
    //! \note DOES NOT DO ANY TYPE ATTRIBUTES
    std::error_code write_xml_any(XmlNode&, const Any&);

    template <typename T>
    requires is_type_v<T>
    std::error_code  write_xml(XmlAttribute&x, const T&val)
    {
        return write_xml(UNSAFE, x, meta<T>(), &val);
    }

    template <typename T>
    requires is_type_v<T>
    std::error_code  write_xml(XmlBase&x, const T&val)
    {
        return write_xml(UNSAFE, x, meta<T>(), &val);
    }
    
    template <typename T>
    requires is_type_v<T>
    std::error_code  write_xml(XmlNode&x, const T&val)
    {
        return write_xml(UNSAFE, x, meta<T>(), &val);
    }

    std::error_code read_xml(unsafe_k, const XmlAttribute&, const TypeMeta&, void*);
    std::error_code read_xml(unsafe_k, const XmlBase&, const TypeMeta&, void*);
    std::error_code read_xml(unsafe_k, const XmlNode&, const TypeMeta&, void*);
    
    template <typename T>
    requires is_type_v<T>
    std::error_code read_xml(const XmlAttribute&x, T& val)
    {
        return read_xml(UNSAFE, x, meta<T>(), &val);
    }

    template <typename T>
    requires is_type_v<T>
    std::error_code read_xml(const XmlBase&x, T& val)
    {
        return read_xml(UNSAFE, x, meta<T>(), &val);
    }

    template <typename T>
    requires is_type_v<T>
    std::error_code read_xml(const XmlNode&x, T& val)
    {
        return read_xml(UNSAFE, x, meta<T>(), &val);
    }
    
    //! Reads/parses the xml as the given data type (in the any)
    //! \note DOES NOT DO ANY TYPE ATTRIBUTES (CALLER DOES THAT)
    //! \note SET Any to desired type FIRST, then call (ie, use a default constructed)
    std::error_code read_xml_any(const XmlAttribute&, Any&);

    //! Reads/parses the xml as the given data type (in the any)
    //! \note DOES NOT DO ANY TYPE ATTRIBUTES (CALLER DOES THAT)
    //! \note SET Any to desired type FIRST, then call (ie, use a default constructed)
    std::error_code read_xml_any(const XmlBase&, Any&);

    //! Reads/parses the xml as the given data type (in the any)
    //! \note DOES NOT DO ANY TYPE ATTRIBUTES (CALLER DOES THAT)
    //! \note SET Any to desired type FIRST, then call (ie, use a default constructed)
    std::error_code read_xml_any(const XmlNode&, Any&);
}

