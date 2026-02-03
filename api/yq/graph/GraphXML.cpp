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
#include <yq/symbol/Pin.hpp>
#include <yq/xml/XmlUtils.hpp>
#include <rapidxml.hpp>

#include "GDocument.hxx"
#include <yq/resource/Resource.hxx>

namespace yq {

    static std::error_code     read_base(GBaseData& d, const XmlNode&xml)
    {
        if(has_attribute(xml, "parent")){
            auto x = read_attribute(xml, "parent", x_uint64);
            if(!x)
                return x.error();
            d.parent    = *x;
        }

        if(has_attribute(xml, "hidden")){
            auto x = read_attribute(xml, "hidden", x_boolean);
            if(!x)
                return x.error();
            d.hidden    = *x ? Tristate::Yes : Tristate::No;
        } else
            d.hidden    = Tristate::Inherit;

        if(has_attribute(xml, "z")){
            auto x = read_attribute(xml, "z", x_double);
            if(!x)
                return x.error();
            d.z     = *x;
        } else
            d.z     = 0.;
        
        //  attributes/properties TODO
        
        return {};
    }
    
    static std::error_code  read_waypoints(std::vector<GWaypoint>& pts, const XmlNode& xml)
    {
        return errors::todo();
    }

    static std::error_code  read_edge(GDocument& doc, const XmlNode& xml)
    {
        auto x = read_attribute(xml, "id", x_uint64);
        if(!x)
            return x.error();
            
        GEdgeData*  ge  = doc.edge(CREATE, *x);
        if(std::error_code ec = read_base(*ge, xml); ec != std::error_code())
            return ec;
            
        if(auto x = read_attribute(xml, "source", x_uint64))
            ge -> source    = *x;
        if(auto x = read_attribute(xml, "target", x_uint64))
            ge -> target    = *x;
            
        if(std::error_code ec = read_waypoints(ge->waypoints, xml); ec != std::error_code())
            return ec;
        
        // more... ?    
        
        return {};
    }

    static std::error_code  read_graph(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_attribute(xml, "id", x_uint64);
        if(!x)
            return x.error();
        GGraphData*  gg  = doc.graph(CREATE, *x);
        if(std::error_code ec = read_base(*gg, xml); ec != std::error_code())
            return ec;
            
        // more ... ?
        return {};
    }

    static std::error_code  read_line(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_attribute(xml, "id", x_uint64);
        if(!x)
            return x.error();
            
        GLineData*  gl  = doc.line(CREATE, *x);
        if(std::error_code ec = read_base(*gl, xml); ec != std::error_code())
            return ec;
            
        if(std::error_code ec = read_waypoints(gl->waypoints, xml); ec != std::error_code())
            return ec;

        // more ... ?

        return {};
    }

    static std::error_code  read_node(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_attribute(xml, "id", x_uint64);
        if(!x)
            return x.error();
            
        GNodeData*  gn  = doc.node(CREATE, *x);
        if(std::error_code ec = read_base(*gn, xml); ec != std::error_code())
            return ec;

        gn -> type  = read_attribute(xml, "type", x_string);
    
        if(has_attribute(xml, "x")){
            auto v = read_attribute(xml, "x", x_double);
            if(!v)
                return v.error();
            gn -> position.x = *v;
        }
        if(has_attribute(xml, "y")){
            auto v = read_attribute(xml, "y", x_double);
            if(!v)
                return v.error();
            gn -> position.y = *v;
        }
        if(has_attribute(xml, "w")){
            auto v = read_attribute(xml, "w", x_double);
            if(!v)
                return v.error();
            gn -> size.x = *v;
        }
        if(has_attribute(xml, "h")){
            auto v = read_attribute(xml, "h", x_double);
            if(!v)
                return v.error();
            gn -> size.y = *v;
        }

        // more ... ?
            
        return {};
    }

    static std::error_code  read_port(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_attribute(xml, "id", x_uint64);
        if(!x)
            return x.error();
            
        GPortData*  gp  = doc.port(CREATE, *x);
        if(std::error_code ec = read_base(*gp, xml); ec != std::error_code())
            return ec;
        
        gp -> key   = read_attribute(xml, "key", x_string);
        
        if(has_attribute(xml, "input")){
            auto bx = read_attribute(xml, "input", x_boolean);
            if(!bx)
                return bx.error();
            gp -> input  = *bx;
        } else
            gp -> input = false;

        if(has_attribute(xml, "output")){
            auto bx = read_attribute(xml, "output", x_boolean);
            if(!bx)
                return bx.error();
            gp -> input  = *bx;
        } else
            gp -> output    = false;

        // more ... ?
            
        return {};
    }

    static std::error_code read_shape(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_attribute(xml, "id", x_uint64);
        if(!x)
            return x.error();
        GShapeData*  gs  = doc.shape(CREATE, *x);
        if(std::error_code ec = read_base(*gs, xml); ec != std::error_code())
            return ec;
            
        // more ... ?
        return {};
    }

    static std::error_code  read_text(GDocument& doc, const XmlNode&xml)
    {
        auto x = read_attribute(xml, "id", x_uint64);
        if(!x)
            return x.error();
        GTextData*  gt  = doc.text(CREATE, *x);
        if(std::error_code ec = read_base(*gt, xml); ec != std::error_code())
            return ec;
            
        // more ... ?
        return {};
    }

    gdocument_ptr_x   loadGraphXML(const XmlDocument&xdoc, const Url&u)
    {
        const XmlNode* xroot = xdoc.first_node("graphxml");
        if(!xroot)
            return unexpected<"Graphxml missing root!">();
        GDocumentPtr   doc = new GDocument;
        doc -> set_url(u);
        doc -> kind(SET, read_attribute(*xroot, "kind", x_string));
            
        for(const XmlNode* x = xroot->first_node(); x; x = x->next_sibling()){
            if(is_similar(x->name(), "edge")){
                if(std::error_code ec = read_edge(*doc, *x); ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "graph")){
                if(std::error_code ec = read_graph(*doc, *x); ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "line")){
                if(std::error_code ec = read_line(*doc, *x); ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "node")){
                if(std::error_code ec = read_node(*doc, *x); ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "port")){
                if(std::error_code ec = read_port(*doc, *x); ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "shape")){
                if(std::error_code ec = read_shape(*doc, *x); ec != std::error_code())
                    return unexpected(ec);
            }
            if(is_similar(x->name(), "text")){
                if(std::error_code ec = read_text(*doc, *x); ec != std::error_code())
                    return unexpected(ec);
            }
        }
        return doc;
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    static std::string  _deresolve(const std::string& k)
    {
        if(!starts_igCase(k, "file:///"))
            return k;
        
        auto ux = to_url_view(k);
        if(!ux.good)
            return k;
        
        std::string pp  = Resource::deresolve(ux.value.path);
        if(pp.empty())
            return k;
            
        Url u   = copy(ux.value);
        u.path  = std::string(pp);
        return to_string(u);
    }

    static void     write_base(const GBaseData&d, XmlNode& xn)
    {
        write_attribute(xn, "id", d.id);
        if(d.parent)
            write_attribute(xn, "parent", d.parent);
            
        if((d.z != 0.) && !is_nan(d.z))
            write_attribute(xn, "z", d.z);

        switch(d.hidden){
        case Tristate::No:
            write_attribute(xn, "hidden", "no"sv);
            break;
        case Tristate::Yes:
            write_attribute(xn, "hidden", "yes"sv);
            break;
        default:
            break;
        }
        
        //  attributes....
    }
    
    static void     write_waypoints(const std::vector<GWaypoint>& points, XmlNode& xml)
    {
    }
    
    static void     write_edge(const GEdgeData&d, XmlNode&xml)
    {
        write_base(d,xml);
        if(d.source)
            write_attribute(xml, "source", d.source);
        if(d.target)
            write_attribute(xml, "target", d.target);
        write_waypoints(d.waypoints, xml);
    }
    
    static void     write_graph(const GGraphData&d, XmlNode&xml)
    {
        write_base(d,xml);
    }

    static void     write_line(const GLineData&d, XmlNode&xml)
    {
        write_base(d,xml);
        write_waypoints(d.waypoints, xml);
    }
    
    static void     write_node(const GNodeData&d, XmlNode&xml)
    {
        write_base(d,xml);
        if(!d.type.empty())
            write_attribute(xml, "type", _deresolve(d.type));
        if(!is_nan(d.position)){
            write_attribute(xml, "x", d.position.x );
            write_attribute(xml, "y", d.position.y );
        }
        if(!is_nan(d.size)){
            write_attribute(xml, "w", d.size.x);
            write_attribute(xml, "h", d.size.y);
        }
    }

    static void     write_port(const GPortData&d, XmlNode&xml)
    {
        write_base(d,xml);
        if(d.input)
            write_attribute(xml, "input", "true"sv);
        if(d.output)
            write_attribute(xml, "output", "true"sv);
        if(!d.key.empty())
            write_attribute(xml, "key", d.key);
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
        if(auto t = gdoc.kind(); !t.empty())
            write_attribute(xroot, "kind", t);
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
        if(std::error_code ec  = parse_xml(doc, bytes); ec != std::error_code())
            return unexpected(ec);
        return loadGraphXML(doc, to_url(fp));
    }
    
    std::error_code saveGraphXML(const GDocument&gdoc, const std::filesystem::path&fp)
    {
        XmlDocument xdoc;
        if(std::error_code ec  = saveGraphXML(gdoc, xdoc); ec != std::error_code()) 
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
        GDocument::IO::add_loader({.extensions={"g"}}, loadGraphXML_xml);
        GDocument::IO::add_saver({.extensions={"g"}}, saveGraphXML_xml);
    }
    
    YQ_INVOKE(reg_graphXML();)
}
