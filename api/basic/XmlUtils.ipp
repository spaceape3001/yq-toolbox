////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/Set.hpp>
#include <basic/TextUtils.hpp>
#include <basic/XmlUtils.hpp>

namespace yq {



        size_t  count_children(const XmlNode*xn, const char* pszTag)
        {
            size_t cnt=0;
            for(const XmlNode* xb = xn->first_node(pszTag); xb; xb = xb -> next_sibling(pszTag))
                ++cnt;
            return cnt;
        }

        boolean_r            to_boolean(const XmlBase*xb)
        {
            return to_boolean(xb->value(), xb->value_size());
        }

        double_r             to_double(const XmlBase* xb)
        {
            return to_double(xb->value(), xb->value_size());
        }

        float_r              to_float(const XmlBase* xb)
        {
            return to_float(xb->value(), xb->value_size());
        }

        unsigned_r           to_hex(const XmlBase*xb)
        {
            return to_hex(xb->value(), xb->value_size());
        }

        uint8_r              to_hex8(const XmlBase*xb)
        {
            return to_hex8(xb->value(), xb->value_size());
        }

        uint16_r             to_hex16(const XmlBase*xb)
        {
            return to_hex16(xb->value(), xb->value_size());
        }

        uint32_r             to_hex32(const XmlBase*xb)
        {
            return to_hex32(xb->value(), xb->value_size());
        }

        uint64_r             to_hex64(const XmlBase*xb)
        {
            return to_hex64(xb->value(), xb->value_size());
        }

        int_r                to_int(const XmlBase*xb)
        {
            return to_int(xb->value(), xb->value_size());
        }

        int_r                to_integer(const XmlBase*xb)
        {
            return to_integer(xb->value(), xb->value_size());
        }

        int8_r               to_int8(const XmlBase*xb)
        {
            return to_int8(xb->value(), xb->value_size());
        }

        int16_r              to_int16(const XmlBase*xb)
        {
            return to_int16(xb->value(), xb->value_size());
        }

        int32_r              to_int32(const XmlBase*xb)
        {
            return to_int32(xb->value(), xb->value_size());
        }

        int64_r              to_int64(const XmlBase*xb)
        {
            return to_int64(xb->value(), xb->value_size());
        }

        short_r              to_short(const XmlBase*xb)
        {
            return to_short(xb->value(), xb->value_size());
        }
            
        std::string_view    to_string_view(const XmlBase*xb)
        {
            return std::string_view(xb->value(), xb->value_size());
        }

        unsigned_r           to_uint(const XmlBase*xb)
        {
            return to_uint(xb->value(), xb->value_size());
        }

        uint8_r              to_uint8(const XmlBase*xb)
        {
            return to_uint8(xb->value(), xb->value_size());
        }

        uint16_r             to_uint16(const XmlBase*xb)
        {
            return to_uint16(xb->value(), xb->value_size());
        }

        uint32_r             to_uint32(const XmlBase*xb)
        {
            return to_uint32(xb->value(), xb->value_size());
        }

        uint64_r             to_uint64(const XmlBase*xb)
        {
            return to_uint64(xb->value(), xb->value_size());
        }

        unsigned_r           to_uinteger(const XmlBase*xb)
        {
            return to_uinteger(xb->value(), xb->value_size());
        }

        unsigned_r           to_unsigned(const XmlBase*xb)
        {
            return to_unsigned(xb->value(), xb->value_size());
        }

        ushort_r             to_ushort(const XmlBase*xb)
        {
            return to_ushort(xb->value(), xb->value_size());
        }
        
        //  //////////////////

        boolean_r            x_boolean(const XmlBase*xb)
        {
            return to_boolean(xb->value(), xb->value_size());
        }

        double_r             x_double(const XmlBase* xb)
        {
            return to_double(xb->value(), xb->value_size());
        }

        float_r              x_float(const XmlBase* xb)
        {
            return to_float(xb->value(), xb->value_size());
        }

        unsigned_r           x_hex(const XmlBase*xb)
        {
            return to_hex(xb->value(), xb->value_size());
        }

        uint8_r              x_hex8(const XmlBase*xb)
        {
            return to_hex8(xb->value(), xb->value_size());
        }

        uint16_r             x_hex16(const XmlBase*xb)
        {
            return to_hex16(xb->value(), xb->value_size());
        }

        uint32_r             x_hex32(const XmlBase*xb)
        {
            return to_hex32(xb->value(), xb->value_size());
        }

        uint64_r             x_hex64(const XmlBase*xb)
        {
            return to_hex64(xb->value(), xb->value_size());
        }

        int_r                x_int(const XmlBase*xb)
        {
            return to_int(xb->value(), xb->value_size());
        }

        int_r                x_integer(const XmlBase*xb)
        {
            return to_integer(xb->value(), xb->value_size());
        }

        int8_r               x_int8(const XmlBase*xb)
        {
            return to_int8(xb->value(), xb->value_size());
        }

        int16_r              x_int16(const XmlBase*xb)
        {
            return to_int16(xb->value(), xb->value_size());
        }

        int32_r              x_int32(const XmlBase*xb)
        {
            return to_int32(xb->value(), xb->value_size());
        }

        int64_r              x_int64(const XmlBase*xb)
        {
            return to_int64(xb->value(), xb->value_size());
        }

        short_r              x_short(const XmlBase*xb)
        {
            return to_short(xb->value(), xb->value_size());
        }
            
        std::string_view    x_string_view(const XmlBase*xb)
        {
            return std::string_view(xb->value(), xb->value_size());
        }

        std::string         x_string(const XmlBase*xb)
        {
            return std::string(xb->value(), xb->value_size());
        }

        unsigned_r           x_uint(const XmlBase*xb)
        {
            return to_uint(xb->value(), xb->value_size());
        }

        uint8_r              x_uint8(const XmlBase*xb)
        {
            return to_uint8(xb->value(), xb->value_size());
        }

        uint16_r             x_uint16(const XmlBase*xb)
        {
            return to_uint16(xb->value(), xb->value_size());
        }

        uint32_r             x_uint32(const XmlBase*xb)
        {
            return to_uint32(xb->value(), xb->value_size());
        }

        uint64_r             x_uint64(const XmlBase*xb)
        {
            return to_uint64(xb->value(), xb->value_size());
        }

        unsigned_r           x_uinteger(const XmlBase*xb)
        {
            return to_uinteger(xb->value(), xb->value_size());
        }

        unsigned_r           x_unsigned(const XmlBase*xb)
        {
            return to_unsigned(xb->value(), xb->value_size());
        }

        ushort_r             x_ushort(const XmlBase*xb)
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
