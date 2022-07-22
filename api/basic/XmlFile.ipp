////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/ByteArray.hpp>
#include <basic/Logging.hpp>
#include <basic/Stream.hpp>
#include <basic/XmlFile.hpp>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"


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

        bool    XmlFile::read(ByteArray&&buffer, std::string_view fname )
        {
            ByteArray   chars   = std::move(buffer);

            chars << '\0';
            XmlDocument     doc;
            try {
                doc.parse<0>(chars.data());
            } catch(const rapidxml::parse_error& pe){
                size_t  pt  = pe.where<char>() - buffer.data();
                yError() << "Xml parse error: " << pe.what() << " (at byte " << pt << ") : " << fname;
                return false;
            }
            
            return read(doc,fname);
        }

        bool    XmlFile::write(yq::Stream & str) const
        {
            Vector<char>    s;
            XmlDocument     doc;
            XmlNode*        x   = doc.allocate_node(rapidxml::node_pi, "xml", "version=\"1.0\" encoding=\"UTF-8\"");
            doc.append_node(x);
            write(doc);
            rapidxml::print(std::back_inserter(s), doc, 0);
            str.write(s.data(), s.size());
            return true;
        }

}
