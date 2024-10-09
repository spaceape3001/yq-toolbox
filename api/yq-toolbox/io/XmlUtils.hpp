////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/basic/Enum.hpp>
#include <yq-toolbox/basic/Flag.hpp>
#include <yq-toolbox/text/vsplit.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <yq/typedef/string.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/typedef/xml.hpp>

#include "rapidxml.hpp"
#include <type_traits>
#include <vector>
#include <set>

namespace yq {

    /*! \brief Converts xml node/attribute to boolean
    
        This parses the text contained by the XML node/attribute,
        returns it as a boolean.
    */
    boolean_x               to_boolean(const XmlBase&);

    /*! \brief Converts xml node/attribute to double
    
        This parses the text contained by the XML node/attribute,
        returns it as a double.
    */
    double_x                to_double(const XmlBase&);

    /*! \brief Converts xml node/attribute to float
    
        This parses the text contained by the XML node/attribute,
        returns it as a float.
    */
    float_x                 to_float(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned hexadecimal integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned hexadecimal integer
    */
    unsigned_x              to_hex(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned 8-bit hexadecimal integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned hexadecimal 8-bit integer
    */
    uint8_x                 to_hex8(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned 16-bit hexadecimal integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned hexadecimal 16-bit integer
    */
    uint16_x                to_hex16(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned 32-bit hexadecimal integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned hexadecimal 32-bit integer
    */
    uint32_x                to_hex32(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned 64-bit hexadecimal integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned hexadecimal 64-bit integer
    */
    uint64_x                to_hex64(const XmlBase&);

    /*! \brief Converts xml node/attribute to signed integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an signed integer
    */
    integer_x               to_int(const XmlBase&);

    /*! \brief Converts xml node/attribute to signed integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an signed integer
    */
    integer_x               to_integer(const XmlBase&);

    /*! \brief Converts xml node/attribute to signed 8-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an signed 8-bit integer
    */
    int8_x                  to_int8(const XmlBase&);

    /*! \brief Converts xml node/attribute to signed 16-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an signed 16-bit integer
    */
    int16_x                 to_int16(const XmlBase&);

    /*! \brief Converts xml node/attribute to signed 32-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an signed 32-bit integer
    */
    int32_x                 to_int32(const XmlBase&);

    /*! \brief Converts xml node/attribute to signed 64-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an signed 64-bit integer
    */
    int64_x                 to_int64(const XmlBase&);

    /*! \brief Converts xml node/attribute to signed short integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an signed short integer
    */
    short_x                 to_short(const XmlBase&);
    
    /*! \brief Converts to string 
    
        This converts the first value to a string
    */
    std::string             to_string(const XmlBase&);

    /*! \brief Converts to string view
    
        \note Return value is a REFERENCE to the given data, therefore, copy off if the XML is being altered/destroyed.
    */
    std::string_view        to_string_view(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned integer
    */
    unsigned_x              to_uint(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned 8-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned 8-bit integer
    */
    uint8_x                 to_uint8(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned 16-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned 16-bit integer
    */
    uint16_x                to_uint16(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned 32-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned 32-bit integer
    */
    uint32_x                to_uint32(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned 64-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned 64-bit integer
    */
    uint64_x                to_uint64(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned integer
    */
    unsigned_x              to_uinteger(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned integer
    */
    unsigned_x              to_unsigned(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned short integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned short integer
    */
    ushort_x                to_ushort(const XmlBase&);

    /*! \brief Converts xml node/attribute to enumerated value
    
        This parses the text contained by the XML node/attribute,
        returns it as an enumerate value of type E
        
        \typename E enumeration type to parse for
    */
    template <typename E>
    Expect<E>           to_enum(const XmlBase& xb)
    {
        auto vt  = xb.value();
        if(vt.empty())
            return E::default_value();
        auto   v    = E::value_for(vt);
        if(v)
            return *v;
        return v;
    }

    /*! \brief Parses to bool
    
        Parses the contents of the tag/attribute, interpreting it as boolean true/false.
        
        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    boolean_x               x_boolean(const XmlBase&);

    /*! \brief Converts xml node/attribute to double
    
        This parses the text contained by the XML node/attribute,
        returns it as a double.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    double_x                x_double(const XmlBase&);

    /*! \brief Converts xml node/attribute to float
    
        This parses the text contained by the XML node/attribute,
        returns it as a float.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    float_x                 x_float(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned hexadecimal integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    unsigned_x              x_hex(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned hexadecimal 8-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    uint8_x                 x_hex8(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned hexadecimal 16-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    uint16_x                x_hex16(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned hexadecimal 32-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    uint32_x                x_hex32(const XmlBase&);

    /*! \brief Converts xml node/attribute to unsigned hexadecimal 64-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an unsigned integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    uint64_x                x_hex64(const XmlBase&);

    /*! \brief Converts xml node/attribute to integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    integer_x               x_int(const XmlBase&);

    /*! \brief Converts xml node/attribute to integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    integer_x               x_integer(const XmlBase&);

    /*! \brief Converts xml node/attribute to 8-bit integer
    
        This parses the text contained by the XML node/attribute,
        returns it as an integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    int8_x                  x_int8(const XmlBase&);

    /*! \brief Converts xml node/attribute to 16-bit integer
    
        This parses the text contained by the XML node/attribute, returns it as an integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    int16_x                 x_int16(const XmlBase&);

    /*! \brief Converts xml node/attribute to 32-bit integer
    
        This parses the text contained by the XML node/attribute, returns it as an integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    int32_x                 x_int32(const XmlBase&);

    /*! \brief Converts xml node/attribute to 64-bit integer
    
        This parses the text contained by the XML node/attribute, returns it as an integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    int64_x                 x_int64(const XmlBase&);

    /*! \brief Converts xml node/attribute to a short integer
    
        This parses the text contained by the XML node/attribute, returns it as a short integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    short_x                 x_short(const XmlBase&);
    
    /*! \brief Converts to string 
    
        This returns the string to the FIRST bit of data for the node/attribute, which is normally 
        sufficient for to_(whatever).
    */
    std::string             x_string(const XmlBase&);
    
    /*! \brief Converts to string view
    
        This returns the string view to the FIRST bit of data for the node/attribute, which is normally 
        sufficient for to_(whatever).
    
        \note Return value is a REFERENCE to the given data, therefore, copy off if the XML is being altered/destroyed.
    */
    std::string_view        x_string_view(const XmlBase&);

    /*! \brief Converts xml node/attribute to an unsigned integer
    
        This parses the text contained by the XML node/attribute, returns it as an unsigned integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    unsigned_x              x_uint(const XmlBase&);

    /*! \brief Converts xml node/attribute to an unsigned 8-bit integer
    
        This parses the text contained by the XML node/attribute, returns it as an unsigned 8-bit integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    uint8_x                 x_uint8(const XmlBase&);

    /*! \brief Converts xml node/attribute to an unsigned 16-bit integer
    
        This parses the text contained by the XML node/attribute, returns it as an unsigned 16-bit integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    uint16_x                x_uint16(const XmlBase&);

    /*! \brief Converts xml node/attribute to an unsigned 32-bit integer
    
        This parses the text contained by the XML node/attribute, returns it as an unsigned 32-bit integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    uint32_x                x_uint32(const XmlBase&);

    /*! \brief Converts xml node/attribute to an unsigned 64-bit integer
    
        This parses the text contained by the XML node/attribute, returns it as an unsigned 64-bit integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    uint64_x                x_uint64(const XmlBase&);

    /*! \brief Converts xml node/attribute to an unsigned integer
    
        This parses the text contained by the XML node/attribute, returns it as an unsigned integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    unsigned_x              x_uinteger(const XmlBase&);

    /*! \brief Converts xml node/attribute to an unsigned integer
    
        This parses the text contained by the XML node/attribute, returns it as an unsigned integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    unsigned_x              x_unsigned(const XmlBase&);

    /*! \brief Converts xml node/attribute to an unsigned short integer
    
        This parses the text contained by the XML node/attribute, returns it as an unsigned short integer.

        \note This is the same as the "to", different name to be unique for read_attribute.
    */
    ushort_x                x_ushort(const XmlBase&);

    /*! \brief Converts xml node/attribute to enumerated value
    
        This parses the text contained by the XML node/attribute,
        returns it as an enumerate value of type E
        
        \typename E enumeration type to parse for
    */
    template <typename E>
    Expect<E>           x_enum(const XmlBase& xb)
    {
        return to_enum<E>(xb);
    }
    
    /*! \brief Converts xml node/attribute to flag-set of enumerated value
    
        This parses the text as a comma separated list of enumerations contained by the XML node/attribute,
        returns it as a flag set value of type E
        
        \typename E enumeration type to parse for
    */
    template <typename E>
    Flag<E>             x_flag(const XmlBase& xb)
    {
        Flag<E> ret;
        vsplit(xb.value(), ',', [&](std::string_view k){
            auto    v   = E::value_for(k);
            if(v)
                ret.set(*v);
        });
        return ret;
    }

    /*! \brief Reads and inteprets attribute
    
        This reads the specified attribute, applies the specified converter to return the value.
    
        \param[in]  xn          XmlNode with the desired attribute
        \parma[in]  pszAttr     attribute being searched for
        \param[in]  pred        Converter of XmlAttribute to value (use one of the x_ methods)
    */
    template <typename Pred>
    auto                read_attribute(const XmlNode& xn, std::string_view pszAttr, Pred pred)
    {
        using Res = std::invoke_result_t<Pred, const XmlAttribute&>;
        const XmlAttribute*xa   = xn.first_attribute(pszAttr);
        if(xa)
            return pred(*xa);
        return Res();
    }
    
    /*! \brief Reads the FIRST child with tag
    
        This finds the first child element (tag) with the specified name, parses its text using the predicate,
        and returns the result.
        
        \param[in]  xn          Containing/Parent XmlNode
        \param[in]  pszTag      XML element being searched for
        \param[in]  pred        Converter of XmlNode to value (use one of the x_ or xn_ methods)
    */
    template <typename Pred>
    auto                read_child(const XmlNode& xn, std::string_view pszTag, Pred pred)
    {
        using Res = std::invoke_result_t<Pred, const XmlNode&>;
        const XmlNode*      xb  = xn.first_node(pszTag);
        if(xb)
            return pred(*xb);
        return Res();
    }

    /*! \brief Reads ALL children with tag
    
        This finds ALL child elements with the specified name, parsed using the predicate, and returns the result
        as a vector.
        
        \param[in]  xn          Containing/Parent XmlNode
        \param[in]  pszTag      XML element being searched for
        \param[in]  pred        Converter of XmlNode to value (use one of the x_ or xn_ methods)
    */
    template <typename Pred>
    auto                read_children(const XmlNode& xn, std::string_view pszTag, Pred pred)
    {
        using Res = std::invoke_result_t<Pred, const XmlNode&>;
        std::vector<Res> ret;
        for(const XmlNode* xb = xn.first_node(pszTag); xb; xb = xb -> next_sibling(pszTag))
            ret.push_back(pred(*xb));
        return ret;
    }
    
    /*! \brief Reads ALL children with tag as set of string
    
        This finds ALL child elements with the specified name, returning the result as a string set
        
        \param[in]  xn          Containing/Parent XmlNode
        \param[in]  pszTag      XML element being searched for
    */
    string_set_t        read_child_string_set(const XmlNode& xn, std::string_view pszTag);


    /*! \brief Counts the child elements with specified name
    
        This finds ALL child elements with the specified name, returning the count.

        \param[in]  xn          Containing/Parent XmlNode
        \param[in]  pszTag      XML element being searched for
    */
    size_t              count_children(const XmlNode&, std::string_view pszTag);


    /*
        With the exception of bool, the rest use the xml document for allocation purposes
    */

    /*! \brief Determine the document for the given xml object
    */
    XmlDocument*         document_for(XmlBase& xb);

    /*! \brief Writes value as hex
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_hex(XmlBase& xb, uint8_t v);

    /*! \brief Writes value as hex
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_hex(XmlBase& xb, uint16_t v);

    /*! \brief Writes value as hex
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_hex(XmlBase& xb, uint32_t v);

    /*! \brief Writes value as hex
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_hex(XmlBase& xb, uint64_t v);

    /*! \brief Writes value as true/false
    
        This writes the value to the specified Xml object, embeds it as true/false
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, bool v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, double v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, float v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, int8_t v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, int16_t v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, int32_t v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, int64_t v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, uint8_t v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, uint16_t v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, uint32_t v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, uint64_t v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    void                 write_x(XmlBase& xb, std::string_view v);

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    template <typename E>
    void                 write_x(XmlBase& xb, EnumImpl<E> v)
    {
        write_x(xb, v.key());
    }

    /*! \brief Writes value to XML
    
        This writes the value to the specified Xml object.
        
        \param[in] xb   XmlBase object to write to (ie node, attribute, etc)
        \param[in] v    Value to write
    */
    template <typename E>
    void                 write_x(XmlBase& xb, Flag<E> v)
    {
        std::string     build   = v.as_string(","sv);
        write_x(xb, build);
    }

    /*! \brief Writes value to XML Node
    
        This writes the value to the specified Xml node.
        
        \param[in] xn   Xml Node to write to
        \param[in] v    Value to write
    */
    template <typename T>
    void                write_xn(XmlNode& xn, const T& val) 
    {
        write_x(xn, val);
    }


    /*! \brief Writes attribute to node 
    
        This writes the specified attribute to node, needs "write_x" defined for type T.
        
        \param[in] xb       Node to attach attribute to
        \param[in] pszAttr  Attribute name/key
        \param[in] value    Value to record
        \param[in] copyAttr TRUE to actually copy the attribute key into the XML
        
        \note For performance, the const char* is assumed to be a program constant, ie, "key" and is therefore
        not going to die between the invocation of this method and the actual write/destruction.  If this assumption
        is violated, bad things will happen; therefore, setting the copyAttr to TRUE will explicitly allocate/copy
        the attribute name/key into strings for the XML and thereby dodge the dragons.
    */
    template <typename T>
    void                write_attribute(XmlNode& xb, std::string_view pszAttr, const T& value)
    {
        XmlDocument*    doc = xb.document();
        assert(doc);
        XmlAttribute*   xa  = doc -> allocate_attribute(pszAttr);
        xb.append_attribute(xa);
        write_x(*xa, value);
    }

    void                write_cdata(XmlNode&xb, std::string_view szTag, std::string_view szValue);


    /*! \brief Writes value to child node
    
        This writes the specified value as a child-node to the given node, needs "write_xn" defined for type T.
        
        \param[in] xb       Parent node
        \param[in] pszTag   Name/key for the child node
        \param[in] value    Value to record
        
        \note For performance, the const char* is assumed to be a program constant, ie, "key" and is therefore
        not going to die between the invocation of this method and the actual write/destruction.  If this assumption
        is violated, bad things will happen; therefore, setting the copyTag to TRUE will explicitly allocate/copy
        the element name/key into strings for the XML and thereby dodge the dragons.
    */
    template <typename T>
    XmlNode*             write_child(XmlNode& xb, std::string_view pszTag, const T& value)
    {
        XmlDocument*    doc = xb.document();
        assert(doc);
        XmlNode*        xn  = doc -> allocate_element(pszTag);
        xb.append_node(xn);
        write_xn(*xn, value);
        return xn;
    }

    template <typename T, typename Pred>
    XmlNode*             write_child(XmlNode& xb, std::string_view pszTag, const T& value, Pred pred)
    {
        XmlDocument*    doc = xb.document();
        assert(doc);
        XmlNode*        xn  = doc -> allocate_element(pszTag);
        xb.append_node(xn);
        pred(*xn, value);
        return xn;
    }

    /*! \brief Writes set values as child nodes
    
        This writes the entire set as a series of child-nodes to the given node.  Needs "write_xn" defined for type T
        
        \param[in] xb       Parent node
        \param[in] pszTag   Name/key for the child node
        \param[in] values   Values to record
    */
    template <typename T,typename C>
    void    write_children(XmlNode& xb, std::string_view pszTag, const std::set<T,C>& values)
    {
        XmlDocument*    doc = xb.document();
        assert(doc);
        for(const T& v : values){
            XmlNode*    xn  = doc -> allocate_element(pszTag);
            xb.append_node(xn);
            write_xn(*xn, v);
        }
    }

    /*! \brief Writes vector as child nodes
    
        This writes the entire vector as a series of child-nodes to the given node.  Needs "write_xn" defined for type T
        
        \param[in] xb       Parent node
        \param[in] pszTag   Name/key for the child node
        \param[in] values   Values to record
    */
    template <typename T>
    void    write_children(XmlNode& xb, std::string_view pszTag, const std::vector<T>& values)
    {
        XmlDocument*    doc = xb.document();
        assert(doc);
        for(const T& v : values){
            XmlNode*    xn  = doc -> allocate_element(pszTag);
            xb.append_node(xn);
            write_xn(*xn, v);
        }
    }

    template <typename T, typename Pred>
    void    write_children(XmlNode& xb, std::string_view pszTag, const std::vector<T>& values, Pred p)
    {
        XmlDocument*    doc = xb.document();
        assert(doc);
        for(const T& v : values){
            XmlNode*    xn  = doc -> allocate_element(pszTag);
            xb.append_node(xn);
            p(*xn, v);
        }
    }
    
    //! Adds the customary <?xml version=" ... line
    void    xml_start(XmlDocument&);
    
    XmlNode*            create_child(XmlNode&, std::string_view pszTag);
    
    std::error_code     read_file(XmlDocument&, const filesystem_path_t&);
    std::error_code     save_file(const XmlDocument&, const filesystem_path_t&);
}
