////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GDocument.hpp"
#include "GraphXML.hpp"
#include <yq/errors.hpp>
#include <yq/container/ByteArray.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/graph/logging.hpp>
#include <yq/graph/GEdgeData.hpp>
#include <yq/graph/GGraphData.hpp>
#include <yq/graph/GLineData.hpp>
#include <yq/graph/GNodeData.hpp>
#include <yq/graph/GPortData.hpp>
#include <yq/graph/GShapeData.hpp>
#include <yq/graph/GTextData.hpp>
#include <yq/resource/ResourceDriverAPI.hpp>
#include <yq/text/match.hpp>
#include <yq/xml/XmlUtils.hpp>
#include <rapidxml.hpp>

#include "GDocument.hxx"
#include <yq/resource/Resource.hxx>

namespace yq {

    static Expect<uint64_t>    read_id(const XmlNode&xml)
    {
        return errors::todo();
    }
    
    static std::error_code     read_base(GBaseData&, const XmlNode&xml)
    {
        return errors::todo();
    }

    static std::error_code  read_edge(GDocument& doc, const XmlNode& xml)
    {
        auto x = read_id(xml);
        if(!x)
            return x.error();
        GEdgeData*  ge  = doc.edge(CREATE, *x);
        std::error_code ec = read_base(*ge, xml);
        if(ec != std::error_code())
            return ec;
            
        return errors::todo();
    }

    static std::error_code  read_graph(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_id(xml);
        if(!x)
            return x.error();
        GGraphData*  gg  = doc.graph(CREATE, *x);
        std::error_code ec = read_base(*gg, xml);
        if(ec != std::error_code())
            return ec;
            
        return errors::todo();
    }

    static std::error_code  read_line(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_id(xml);
        if(!x)
            return x.error();
        GLineData*  gl  = doc.line(CREATE, *x);
        std::error_code ec = read_base(*gl, xml);
        if(ec != std::error_code())
            return ec;
            
        return errors::todo();
    }

    static std::error_code  read_node(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_id(xml);
        if(!x)
            return x.error();
        GNodeData*  gn  = doc.node(CREATE, *x);
        std::error_code ec = read_base(*gn, xml);
        if(ec != std::error_code())
            return ec;
            
        return errors::todo();
    }

    static std::error_code  read_port(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_id(xml);
        if(!x)
            return x.error();
        GPortData*  gp  = doc.port(CREATE, *x);
        std::error_code ec = read_base(*gp, xml);
        if(ec != std::error_code())
            return ec;
            
        return errors::todo();
    }

    static std::error_code read_shape(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_id(xml);
        if(!x)
            return x.error();
        GShapeData*  gs  = doc.shape(CREATE, *x);
        std::error_code ec = read_base(*gs, xml);
        if(ec != std::error_code())
            return ec;
            
        return errors::todo();
    }

    static std::error_code  read_text(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_id(xml);
        if(!x)
            return x.error();
        GTextData*  gt  = doc.text(CREATE, *x);
        std::error_code ec = read_base(*gt, xml);
        if(ec != std::error_code())
            return ec;
            
        return errors::todo();
    }

    gdocument_ptr_x   loadGraphXML(const XmlDocument&xdoc, const Url&u)
    {
        const XmlNode* xroot = xdoc.first_node("graphxml");
        if(!xroot)
            return unexpected<"Graphxml missing root!">();
        GDocumentPtr   doc = new GDocument;
        doc -> set_url(u);
        doc -> type(SET, read_attribute(*xroot, "type", x_string));
            
        for(const XmlNode* x = xroot->first_node(); x; x = x->next_sibling()){
            if(is_similar(x->name(), "edge")){
                std::error_code ec = read_edge(*doc, *x);
                if(ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "graph")){
                std::error_code ec = read_graph(*doc, *x);
                if(ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "line")){
                std::error_code ec = read_line(*doc, *x);
                if(ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "node")){
                std::error_code ec = read_node(*doc, *x);
                if(ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "port")){
                std::error_code ec = read_port(*doc, *x);
                if(ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "shape")){
                std::error_code ec = read_shape(*doc, *x);
                if(ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "text")){
                std::error_code ec = read_text(*doc, *x);
                if(ec != std::error_code())
                    return unexpected(ec);
            }
        }
        return doc;
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    static void     write_base(const GBaseData&d, XmlNode&)
    {
    }
    
    static void     write_edge(const GEdgeData&d, XmlNode&xml)
    {
        write_base(d,xml);
    }
    
    static void     write_graph(const GGraphData&d, XmlNode&xml)
    {
        write_base(d,xml);
    }

    static void     write_line(const GLineData&d, XmlNode&xml)
    {
        write_base(d,xml);
    }
    
    static void     write_node(const GNodeData&d, XmlNode&xml)
    {
        write_base(d,xml);
    }

    static void     write_port(const GPortData&d, XmlNode&xml)
    {
        write_base(d,xml);
    }

    static void     write_shape(const GShapeData&d, XmlNode&xml)
    {
        write_base(d,xml);
    }

    static void     write_text(const GTextData&d, XmlNode&xml)
    {
        write_base(d,xml);
    }

    std::error_code saveGraphXML(const GDocument&gdoc, XmlDocument&xdoc)
    {
        auto& xroot = *xdoc.create_element("graphxml");
        if(auto t = gdoc.type(); !t.empty())
            write_attribute(xroot, "type", t);
        gdoc.datas(FOR, [&](const GBaseData& gb) {
            if(gb.is_edge()){
                auto&  x    = *xroot.create_element("edge");
                write_edge(static_cast<const GEdgeData&>(gb), x);
            }
            if(gb.is_graph()){
                auto&  x    = *xroot.create_element("graph");
                write_graph(static_cast<const GGraphData&>(gb), x);
            }
            if(gb.is_line()){
                auto&  x    = *xroot.create_element("line");
                write_line(static_cast<const GLineData&>(gb), x);
            }
            if(gb.is_node()){
                auto&  x    = *xroot.create_element("node");
                write_node(static_cast<const GNodeData&>(gb), x);
            }
            if(gb.is_port()){
                auto&  x    = *xroot.create_element("port");
                write_port(static_cast<const GPortData&>(gb), x);
            }
            if(gb.is_shape()){
                auto&  x    = *xroot.create_element("shape");
                write_shape(static_cast<const GShapeData&>(gb), x);
            }
            if(gb.is_text()){
                auto&  x    = *xroot.create_element("text");
                write_text(static_cast<const GTextData&>(gb), x);
            }
            
        });
        
        return {};
    }
    
    
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    
    gdocument_ptr_x   loadGraphXML(const std::filesystem::path&fp)
    {
        ByteArray   bytes   = file_bytes(fp);
        if(bytes.empty())
            return unexpected<"No XML data read">();
        XmlDocument doc;
        std::error_code ec  = parse_xml(doc, bytes);
        if(ec != std::error_code())
            return unexpected(ec);
        return loadGraphXML(doc, to_url(fp));
    }
    
    std::error_code saveGraphXML(const GDocument&gdoc, const std::filesystem::path&fp)
    {
        XmlDocument xdoc;
        std::error_code ec  = saveGraphXML(gdoc, xdoc);
        if(ec != std::error_code()) 
            return ec;
        return save_file(xdoc, fp);
    }
    
    static GDocumentPtr      loadGraphXML_xml(const XmlDocument&doc, const ResourceLoadAPI& api)
    {
        auto x = loadGraphXML(doc, api.url());
        if(!x){
            graphWarning << "Unable to load (" << api.url() << "): " << x.error().message();
            return {};
        }
        return *x;
    }
    
    static std::error_code  saveGraphXML_xml(const GDocument&doc, XmlDocument&xdoc, const ResourceSaveAPI&api)
    {
        return saveGraphXML(doc, xdoc);
    }
    
    static void reg_graphXML()
    {
        GDocument::IO::add_loader({.extensions={"gx"}}, loadGraphXML_xml);
        GDocument::IO::add_saver({.extensions={"gx"}}, saveGraphXML_xml);
    }
    
    YQ_INVOKE(reg_graphXML();)
}
