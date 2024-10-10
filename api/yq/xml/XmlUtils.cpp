////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/errors.hpp>
#include <yq/container/ByteArray.hpp>
#include <yq/container/Set.hpp>
#include <yq/container/set_utils.hpp>
#include <yq/core/Logging.hpp>
//#include <0/basic/TextUtils.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/xml/XmlUtils.hpp>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

namespace yq {

    size_t  count_children(const XmlNode&xn, std::string_view pszTag)
    {
        size_t cnt=0;
        for(const XmlNode* xb = xn.first_node(pszTag); xb; xb = xb -> next_sibling(pszTag))
            ++cnt;
        return cnt;
    }

    boolean_x           to_boolean(const XmlBase&xb)
    {
        return to_boolean(xb.value());
    }

    double_x            to_double(const XmlBase& xb)
    {
        return to_double(xb.value());
    }

    float_x             to_float(const XmlBase& xb)
    {
        return to_float(xb.value());
    }

    unsigned_x          to_hex(const XmlBase&xb)
    {
        return to_hex(xb.value());
    }

    uint8_x             to_hex8(const XmlBase&xb)
    {
        return to_hex8(xb.value());
    }

    uint16_x            to_hex16(const XmlBase&xb)
    {
        return to_hex16(xb.value());
    }

    uint32_x            to_hex32(const XmlBase&xb)
    {
        return to_hex32(xb.value());
    }

    uint64_x            to_hex64(const XmlBase&xb)
    {
        return to_hex64(xb.value());
    }

    integer_x           to_int(const XmlBase&xb)
    {
        return to_int(xb.value());
    }

    integer_x           to_integer(const XmlBase&xb)
    {
        return to_integer(xb.value());
    }

    int8_x              to_int8(const XmlBase&xb)
    {
        return to_int8(xb.value());
    }

    int16_x             to_int16(const XmlBase&xb)
    {
        return to_int16(xb.value());
    }

    int32_x             to_int32(const XmlBase&xb)
    {
        return to_int32(xb.value());
    }

    int64_x             to_int64(const XmlBase&xb)
    {
        return to_int64(xb.value());
    }

    short_x             to_short(const XmlBase&xb)
    {
        return to_short(xb.value());
    }
        
    std::string_view    to_string_view(const XmlBase&xb)
    {
        return std::string_view(xb.value());
    }

    unsigned_x          to_uint(const XmlBase&xb)
    {
        return to_uint(xb.value());
    }

    uint8_x             to_uint8(const XmlBase&xb)
    {
        return to_uint8(xb.value());
    }

    uint16_x            to_uint16(const XmlBase&xb)
    {
        return to_uint16(xb.value());
    }

    uint32_x            to_uint32(const XmlBase&xb)
    {
        return to_uint32(xb.value());
    }

    uint64_x            to_uint64(const XmlBase&xb)
    {
        return to_uint64(xb.value());
    }

    unsigned_x          to_uinteger(const XmlBase&xb)
    {
        return to_uinteger(xb.value());
    }

    unsigned_x          to_unsigned(const XmlBase&xb)
    {
        return to_unsigned(xb.value());
    }

    ushort_x            to_ushort(const XmlBase&xb)
    {
        return to_ushort(xb.value());
    }
    
    //  //////////////////

    boolean_x           x_boolean(const XmlBase&xb)
    {
        return to_boolean(xb.value());
    }

    double_x            x_double(const XmlBase& xb)
    {
        return to_double(xb.value());
    }

    float_x             x_float(const XmlBase& xb)
    {
        return to_float(xb.value());
    }

    unsigned_x          x_hex(const XmlBase&xb)
    {
        return to_hex(xb.value());
    }

    uint8_x             x_hex8(const XmlBase&xb)
    {
        return to_hex8(xb.value());
    }

    uint16_x            x_hex16(const XmlBase&xb)
    {
        return to_hex16(xb.value());
    }

    uint32_x            x_hex32(const XmlBase&xb)
    {
        return to_hex32(xb.value());
    }

    uint64_x            x_hex64(const XmlBase&xb)
    {
        return to_hex64(xb.value());
    }

    integer_x           x_int(const XmlBase&xb)
    {
        return to_int(xb.value());
    }

    integer_x           x_integer(const XmlBase&xb)
    {
        return to_integer(xb.value());
    }

    int8_x              x_int8(const XmlBase&xb)
    {
        return to_int8(xb.value());
    }

    int16_x             x_int16(const XmlBase&xb)
    {
        return to_int16(xb.value());
    }

    int32_x             x_int32(const XmlBase&xb)
    {
        return to_int32(xb.value());
    }

    int64_x             x_int64(const XmlBase&xb)
    {
        return to_int64(xb.value());
    }

    short_x             x_short(const XmlBase&xb)
    {
        return to_short(xb.value());
    }
        
    std::string             to_string(const XmlBase& xb)
    {
        return std::string(xb.value());
    }

    std::string_view    x_string_view(const XmlBase&xb)
    {
        return std::string_view(xb.value());
    }

    std::string         x_string(const XmlBase&xb)
    {
        return std::string(xb.value());
    }

    unsigned_x          x_uint(const XmlBase&xb)
    {
        return to_uint(xb.value());
    }

    uint8_x             x_uint8(const XmlBase&xb)
    {
        return to_uint8(xb.value());
    }

    uint16_x            x_uint16(const XmlBase&xb)
    {
        return to_uint16(xb.value());
    }

    uint32_x            x_uint32(const XmlBase&xb)
    {
        return to_uint32(xb.value());
    }

    uint64_x            x_uint64(const XmlBase&xb)
    {
        return to_uint64(xb.value());
    }

    unsigned_x          x_uinteger(const XmlBase&xb)
    {
        return to_uinteger(xb.value());
    }

    unsigned_x          x_unsigned(const XmlBase&xb)
    {
        return to_unsigned(xb.value());
    }

    ushort_x            x_ushort(const XmlBase&xb)
    {
        return to_ushort(xb.value());
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    XmlNode*    create_child(XmlNode& xn, std::string_view pszTag)
    {
        XmlDocument*    doc = document_for(xn);
        if(!doc)
            return nullptr;
        XmlNode*        n   = doc -> allocate_element(pszTag);
        xn.append_node(n);
        return n;
    }


    XmlDocument*         document_for(XmlBase& xb)
    {
        XmlNode*    xn  = xb.parent();
        if(xn)
            return xn -> document();
        return nullptr;
    }

    string_set_t         read_child_string_set(const XmlNode&xn, std::string_view pszTag)
    {
        string_set_t    ret;
        for(const XmlNode* xb = xn.first_node(pszTag); xb; xb = xb -> next_sibling(pszTag))
            ret << x_string(*xb);
        return ret;
    }

    void                write_cdata(XmlNode&xb, std::string_view szTag, std::string_view szValue)
    {
        XmlDocument*    doc     = xb.document();
        assert(doc);
        XmlNode*  xn  = doc->allocate_element(szTag);
        xb.append_node(xn);
        xn->append_node(doc->allocate_cdata(szValue));
    }

    void                 write_hex(XmlBase& xb, uint8_t v)
    {
        write_x(xb, fmt_hex(v));
    }

    void                 write_hex(XmlBase& xb, uint16_t v)
    {
        write_x(xb, fmt_hex(v));
    }

    void                 write_hex(XmlBase& xb, uint32_t v) 
    {
        write_x(xb, fmt_hex(v));
    }

    void                 write_hex(XmlBase& xb, uint64_t v)
    {
        write_x(xb, fmt_hex(v));
    }


    void                 write_x(XmlBase& xb, bool f)
    {
        xb.value( f ? "true" : "false");
    }

    void                 write_x(XmlBase& xb, double v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase& xb, float v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase& xb, int8_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase& xb, int16_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase& xb, int32_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase& xb, int64_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase& xb, uint8_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase& xb, uint16_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase& xb, uint32_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase& xb, uint64_t v)
    {
        write_x(xb, to_string_view(v));
    }

    void                 write_x(XmlBase& xb, std::string_view v)
    {
        XmlDocument*doc = document_for(xb);
        if(doc && !v.empty())
            xb.value(doc -> allocate_string(v.data(), v.size()), v.size());
    }

    void    xml_start(XmlDocument&doc)
    {
        doc.append_node(doc.allocate_node(rapidxml::node_pi, "xml", "version=\"1.0\" encoding=\"UTF-8\""));
    }

    std::error_code     read_file(XmlDocument&doc, const filesystem_path_t&fp)
    {
        if(fp.empty())
            return errors::filepath_empty();
        if(!file_exists(fp))
            return errors::file_not_found();
        ByteArray       ba  = file_bytes(fp);
        if(ba.empty())
            return errors::failed_to_read_file();
        ba << '\0';
        try {
            doc.parse<0>(ba.data());
        } catch(const rapidxml::parse_error& pe){
            size_t  pt  = pe.where<char>() - ba.data();
            yError() << "Xml parse error: " << pe.what() << " (at byte " << pt << ") : " << fp.string();
            return errors::xml_bad_syntax();
        }
        return errors::none();
    }
    
    std::error_code     save_file(const XmlDocument&doc, const filesystem_path_t&fp)
    {
        if(fp.empty())
            return errors::filepath_empty();

        // export to a buffer
        std::vector<char> s;
        rapidxml::print(std::back_inserter(s), doc, 0);
        if(!file_backup(fp.c_str()))
            return errors::failed_to_backup_file();
        if(!file_write(fp, s))
            return errors::failed_to_write_file();
        return errors::none();
    }

}
