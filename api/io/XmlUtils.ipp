////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Set.hpp>
#include <basic/TextUtils.hpp>
#include <io/XmlUtils.hpp>

namespace yq {

    size_t  count_children(const XmlNode*xn, const char* pszTag)
    {
        size_t cnt=0;
        for(const XmlNode* xb = xn->first_node(pszTag); xb; xb = xb -> next_sibling(pszTag))
            ++cnt;
        return cnt;
    }

    Expect<bool>            to_boolean(const XmlBase*xb)
    {
        return to_boolean(xb->value(), xb->value_size());
    }

    Expect<double>          to_double(const XmlBase* xb)
    {
        return to_double(xb->value(), xb->value_size());
    }

    Expect<float>           to_float(const XmlBase* xb)
    {
        return to_float(xb->value(), xb->value_size());
    }

    Expect<unsigned>        to_hex(const XmlBase*xb)
    {
        return to_hex(xb->value(), xb->value_size());
    }

    Expect<uint8_t>         to_hex8(const XmlBase*xb)
    {
        return to_hex8(xb->value(), xb->value_size());
    }

    Expect<uint16_t>        to_hex16(const XmlBase*xb)
    {
        return to_hex16(xb->value(), xb->value_size());
    }

    Expect<uint32_t>        to_hex32(const XmlBase*xb)
    {
        return to_hex32(xb->value(), xb->value_size());
    }

    Expect<uint64_t>        to_hex64(const XmlBase*xb)
    {
        return to_hex64(xb->value(), xb->value_size());
    }

    Expect<int>             to_int(const XmlBase*xb)
    {
        return to_int(xb->value(), xb->value_size());
    }

    Expect<int>             to_integer(const XmlBase*xb)
    {
        return to_integer(xb->value(), xb->value_size());
    }

    Expect<int8_t>          to_int8(const XmlBase*xb)
    {
        return to_int8(xb->value(), xb->value_size());
    }

    Expect<int16_t>         to_int16(const XmlBase*xb)
    {
        return to_int16(xb->value(), xb->value_size());
    }

    Expect<int32_t>         to_int32(const XmlBase*xb)
    {
        return to_int32(xb->value(), xb->value_size());
    }

    Expect<int64_t>         to_int64(const XmlBase*xb)
    {
        return to_int64(xb->value(), xb->value_size());
    }

    Expect<short>           to_short(const XmlBase*xb)
    {
        return to_short(xb->value(), xb->value_size());
    }
        
    std::string_view        to_string_view(const XmlBase*xb)
    {
        return std::string_view(xb->value(), xb->value_size());
    }

    Expect<unsigned>        to_uint(const XmlBase*xb)
    {
        return to_uint(xb->value(), xb->value_size());
    }

    Expect<uint8_t>         to_uint8(const XmlBase*xb)
    {
        return to_uint8(xb->value(), xb->value_size());
    }

    Expect<uint16_t>        to_uint16(const XmlBase*xb)
    {
        return to_uint16(xb->value(), xb->value_size());
    }

    Expect<uint32_t>        to_uint32(const XmlBase*xb)
    {
        return to_uint32(xb->value(), xb->value_size());
    }

    Expect<uint64_t>        to_uint64(const XmlBase*xb)
    {
        return to_uint64(xb->value(), xb->value_size());
    }

    Expect<unsigned>        to_uinteger(const XmlBase*xb)
    {
        return to_uinteger(xb->value(), xb->value_size());
    }

    Expect<unsigned>        to_unsigned(const XmlBase*xb)
    {
        return to_unsigned(xb->value(), xb->value_size());
    }

    Expect<unsigned short>  to_ushort(const XmlBase*xb)
    {
        return to_ushort(xb->value(), xb->value_size());
    }
    
    //  //////////////////

    Expect<bool>            x_boolean(const XmlBase*xb)
    {
        return to_boolean(xb->value(), xb->value_size());
    }

    Expect<double>          x_double(const XmlBase* xb)
    {
        return to_double(xb->value(), xb->value_size());
    }

    Expect<float>           x_float(const XmlBase* xb)
    {
        return to_float(xb->value(), xb->value_size());
    }

    Expect<unsigned>        x_hex(const XmlBase*xb)
    {
        return to_hex(xb->value(), xb->value_size());
    }

    Expect<uint8_t>         x_hex8(const XmlBase*xb)
    {
        return to_hex8(xb->value(), xb->value_size());
    }

    Expect<uint16_t>        x_hex16(const XmlBase*xb)
    {
        return to_hex16(xb->value(), xb->value_size());
    }

    Expect<uint32_t>        x_hex32(const XmlBase*xb)
    {
        return to_hex32(xb->value(), xb->value_size());
    }

    Expect<uint64_t>        x_hex64(const XmlBase*xb)
    {
        return to_hex64(xb->value(), xb->value_size());
    }

    Expect<int>             x_int(const XmlBase*xb)
    {
        return to_int(xb->value(), xb->value_size());
    }

    Expect<int>             x_integer(const XmlBase*xb)
    {
        return to_integer(xb->value(), xb->value_size());
    }

    Expect<int8_t>          x_int8(const XmlBase*xb)
    {
        return to_int8(xb->value(), xb->value_size());
    }

    Expect<int16_t>         x_int16(const XmlBase*xb)
    {
        return to_int16(xb->value(), xb->value_size());
    }

    Expect<int32_t>         x_int32(const XmlBase*xb)
    {
        return to_int32(xb->value(), xb->value_size());
    }

    Expect<int64_t>         x_int64(const XmlBase*xb)
    {
        return to_int64(xb->value(), xb->value_size());
    }

    Expect<short>           x_short(const XmlBase*xb)
    {
        return to_short(xb->value(), xb->value_size());
    }
        
    std::string_view        x_string_view(const XmlBase*xb)
    {
        return std::string_view(xb->value(), xb->value_size());
    }

    std::string             x_string(const XmlBase*xb)
    {
        return std::string(xb->value(), xb->value_size());
    }

    Expect<unsigned>        x_uint(const XmlBase*xb)
    {
        return to_uint(xb->value(), xb->value_size());
    }

    Expect<uint8_t>         x_uint8(const XmlBase*xb)
    {
        return to_uint8(xb->value(), xb->value_size());
    }

    Expect<uint16_t>        x_uint16(const XmlBase*xb)
    {
        return to_uint16(xb->value(), xb->value_size());
    }

    Expect<uint32_t>        x_uint32(const XmlBase*xb)
    {
        return to_uint32(xb->value(), xb->value_size());
    }

    Expect<uint64_t>        x_uint64(const XmlBase*xb)
    {
        return to_uint64(xb->value(), xb->value_size());
    }

    Expect<unsigned>        x_uinteger(const XmlBase*xb)
    {
        return to_uinteger(xb->value(), xb->value_size());
    }

    Expect<unsigned>        x_unsigned(const XmlBase*xb)
    {
        return to_unsigned(xb->value(), xb->value_size());
    }

    Expect<unsigned short>  x_ushort(const XmlBase*xb)
    {
        return to_ushort(xb->value(), xb->value_size());
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    XmlDocument*         document_for(XmlBase* xb)
    {
        XmlNode*    xn  = xb -> parent();
        if(xn)
            return xn -> document();
        return nullptr;
    }

    string_set_t         read_child_string_set(const XmlNode*xn, const char* pszTag)
    {
        string_set_t    ret;
        for(const XmlNode* xb = xn->first_node(pszTag); xb; xb = xb -> next_sibling(pszTag))
            ret << x_string(xb);
        return ret;
    }


    void                 write_hex(XmlBase* xb, uint8_t v)
    {
        write_x(xb, fmt_hex(v));
    }

    void                 write_hex(XmlBase* xb, uint16_t v)
    {
        write_x(xb, fmt_hex(v));
    }

    void                 write_hex(XmlBase* xb, uint32_t v) 
    {
        write_x(xb, fmt_hex(v));
    }

    void                 write_hex(XmlBase* xb, uint64_t v)
    {
        write_x(xb, fmt_hex(v));
    }


    void                 write_x(XmlBase* xb, bool f)
    {
        xb->value( f ? "true" : "false");
    }

    void                 write_x(XmlBase* xb, double v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase* xb, float v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase* xb, int8_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase* xb, int16_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase* xb, int32_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase* xb, int64_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase* xb, uint8_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase* xb, uint16_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase* xb, uint32_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase* xb, uint64_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase* xb, std::string_view v)
    {
        XmlDocument*doc = document_for(xb);
        if(doc && !v.empty())
            xb -> value(doc -> allocate_string(v.data(), v.size()), v.size());
    }

    void    xml_start(XmlDocument&doc)
    {
        doc.append_node(doc.allocate_node(rapidxml::node_pi, "xml", "version=\"1.0\" encoding=\"UTF-8\""));
    }
}
