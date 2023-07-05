////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <graph/Graph.hpp>
#include <basic/errors.hpp>
#include <io/XmlUtils.hpp>

namespace yq::g {
    std::error_code  load(Document&doc, const std::filesystem::path&fp, std::string_view rootTagName)
    {
        XmlDocument xml;
        std::error_code ec  = read_file(xml, fp);
        if(ec)
            return ec;
        return load(doc, xml, rootTagName, fp.string());
    }
    
    std::error_code  load(Document&doc, const XmlDocument&xml, std::string_view rootTagName, std::string_view fileName)
    {
        return errors::todo();
    }

    std::error_code  save(const std::filesystem::path&fp, const Document&doc, std::string_view rootTagName)
    {
        XmlDocument xml;
        std::error_code ec  = save(xml, doc, rootTagName);
        if(ec)
            return ec;
        return save_file(xml, fp);
    }
    
    std::error_code  save(XmlDocument& xml, const Document& doc, std::string_view rootTagName)
    {
        xml_start(xml);
        XmlNode*    root    = xml.allocate_element(rootTagName);
        xml.append_node(root);
        
        return errors::todo();
    }
}
