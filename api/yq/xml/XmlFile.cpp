////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/container/ByteArray.hpp>
#include <yq/core/Logging.hpp>
#include <yq/core/Stream.hpp>
#include <yq/xml/XmlFile.hpp>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"


namespace yq {


    //  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  XML FILE
    //  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

        XmlFile::XmlFile()
        {
        }

        XmlFile::~XmlFile()
        {
        }

        std::error_code    XmlFile::read(ByteArray&&buffer, std::string_view fname )
        {
            ByteArray   chars   = std::move(buffer);

            chars << '\0';
            XmlDocument     doc;
            try {
                doc.parse<0>(chars.data());
            } catch(const rapidxml::parse_error& pe){
                size_t  pt  = pe.where<char>() - buffer.data();
                yError() << "Xml parse error: " << pe.what() << " (at byte " << pt << ") : " << fname;
                return errors::xml_bad_syntax();
            }
            
            return read(doc,fname);
        }

        std::error_code    XmlFile::write(yq::Stream & str) const
        {
            Vector<char>    s;
            XmlDocument     doc;
            XmlNode*        x   = doc.allocate_node(rapidxml::node_pi, "xml", "version=\"1.0\" encoding=\"UTF-8\"");
            doc.append_node(x);
            std::error_code ec = write(doc);
            if(ec != std::error_code())
                return ec;
            rapidxml::print(std::back_inserter(s), doc, 0);
            str.write(s.data(), s.size());
            return std::error_code();
        }

}
