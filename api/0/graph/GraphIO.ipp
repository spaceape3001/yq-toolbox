////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/graph/Graph.hpp>
#include <yq/errors.hpp>
#include <0/io/XmlUtils.hpp>

namespace yq::g {
    using yq::write_x;
    using yq::write_xn;

    static constexpr std::string_view   szData          = "data";
    static constexpr std::string_view   szDescription   = "description";
    static constexpr std::string_view   szCountDef      = "count_def";
    static constexpr std::string_view   szCountMax      = "count_max";
    static constexpr std::string_view   szCountMin      = "count_min";
    static constexpr std::string_view   szEdge          = "edge";
    static constexpr std::string_view   szFlow          = "flow";
    static constexpr std::string_view   szFormat        = "format";
    static constexpr std::string_view   szGraph         = "graph";
    static constexpr std::string_view   szName          = "name";
    static constexpr std::string_view   szNode          = "node";
    static constexpr std::string_view   szNotes         = "notes";
    static constexpr std::string_view   szOption        = "option";
    static constexpr std::string_view   szPin           = "pin";
    static constexpr std::string_view   szProperty      = "property";
    static constexpr std::string_view   szSource        = "source";
    static constexpr std::string_view   szSub           = "sub";
    static constexpr std::string_view   szTarget        = "target";
    static constexpr std::string_view   szType          = "type";
    static constexpr std::string_view   szValue         = "value";
    static constexpr std::string_view   szVersion       = "1";

    template <typename T>
    std::error_code load(std::vector<T>&v, const XmlNode& xml, std::string_view tag)
    {
        v.reserve(count_children(xml, tag));
        for(const XmlNode* xn = xml.first_node(tag); xn; xn = xn->next_sibling(tag)){
            v.push_back(T());
            std::error_code ec  = load((T&) v.back(), *xn);
            if(ec)
                return ec;
        }
        return errors::none();
    }
    
    Any     xn_any(const XmlNode& xml)
    {
        return Any();       // TODO
    }

    
    std::error_code load(TND& v, const XmlNode& xml)
    {
        v.name          = read_attribute(xml, szName, x_string);
        v.type          = read_attribute(xml, szType, x_string);
        v.description   = read_attribute(xml, szDescription, x_string);
        v.notes         = read_child(xml, szNotes, x_string); // warning...cdata might be needed here... TODO
        v.options       = read_attribute(xml, szOption, x_flag<Option>);
        return errors::none();
    }

    std::error_code load(Property& v, const XmlNode& xml)
    {
        std::error_code ec = load((TND&) v, xml);
        if(ec)
            return ec;

        return errors::todo(); // TODO
    }
            
    std::error_code load(Base& v, const XmlNode& xml)
    {
        std::error_code ec = load((TND&) v, xml);
        if(ec)
            return ec;

        return errors::todo(); // TODO
    }
    
    std::error_code load(Pin& v, const XmlNode& xml)
    {
        std::error_code ec = load((Base&) v, xml);
        if(ec)
            return ec;
        
        return errors::todo(); // TODO
    }

    std::error_code load(Pinned& v, const XmlNode& xml)
    {
        std::error_code ec = load((Base&) v, xml);
        if(ec)
            return ec;
        return load(v.pins, xml, szPin);
    }

    std::error_code load(Node& v, const XmlNode& xml)
    {
        return load((Pinned&) v, xml);
    }

    Socket xn_socket(const XmlNode& xml)
    {
        Socket  v;
        v.node  = read_attribute(xml, szNode, x_string);
        v.pin   = read_attribute(xml, szPin, x_string);
        v.sub   = read_attribute(xml, szSub, x_string);
        v.nodes = read_children(xml, szNode, x_string);
        return v;
    }
    
    std::error_code load(Edge& v, const XmlNode& xml)
    {
        std::error_code ec = load((Base&) v, xml);
        if(ec)
            return ec;
        
        v.source    = read_child(xml, szSource, xn_socket);
        v.target    = read_child(xml, szTarget, xn_socket);
        v.datas     = read_children(xml, szData, x_string);
        return errors::none();
    }


    std::error_code load(Graph& v, const XmlNode& xml)
    {
        std::error_code ec = load((Pinned&) v, xml);
        if(ec)
            return ec;
        
        ec  = load(v.nodes, xml, szNode);
        if(ec)
            return ec;
        
        ec  = load(v.edges, xml, szEdge);
        return ec;
    }

    std::error_code load(Document& v, const XmlNode& xml)
    {
        std::error_code     ec   = load((Base&) v, xml);
        if(ec)
            return ec;
        return load(v.graphs, xml, szGraph);
    }
    
    
    std::error_code load(Document& doc, const std::filesystem::path&fp, std::string_view rootTagName)
    {
        XmlDocument xml;
        std::error_code ec  = read_file(xml, fp);
        if(ec)
            return ec;
        return load(doc, xml, rootTagName, fp.string());
    }
    
    std::error_code load(Document& doc, const XmlDocument&xml, std::string_view rootTagName, std::string_view fileName)
    {
        const XmlNode*  root    = xml.first_node(rootTagName);
        if(!root)
            return errors::xml_no_root_element();
        const XmlAttribute* attr    = root->first_attribute(szFormat);
        if(!attr)
            return errors::wrong_format();
        if(attr->value() != szVersion)
            return errors::wrong_format();
        return load(doc, *root);
    }


    void    write_any(XmlNode& xml, const Any& v)
    {
        //  TODO.....
    }
    
    void    write_tnd(XmlNode& xml, const TND& v)
    {
        if(!v.name.empty())
            write_attribute(xml, szName, v.name);
        if(!v.type.empty())
            write_attribute(xml, szType, v.type);
        if(v.options)
            write_attribute(xml, szOption, v.options);
        if(!v.notes.empty())
            write_cdata(xml, szNotes, v.notes);
    }
    
    void    write_mmd(XmlNode& xml, const MinMaxDef<unsigned>& v)
    {
        if(v.min)
            write_attribute(xml, szCountMin, v.min);
        if(v.max)
            write_attribute(xml, szCountMax, v.max);
        if(v.def)
            write_attribute(xml, szCountDef, v.def);
    }
    
    void    write_prop(XmlNode& xml, const Property& v)
    {
        write_tnd(xml, v);
        write_mmd(xml, v.count);
        if(v.value.valid())
            write_child(xml, szValue, v.value, write_any);
    }
    
    void    write_base(XmlNode& xml, const Base& v)
    {
        write_tnd(xml, (const TND&) v);
        write_children(xml, szProperty, v.properties, write_prop);
    }

    void    write_pin(XmlNode& xml, const Pin& v)
    {
        write_base(xml, v);
        write_attribute(xml, szFlow, v.flow);
        write_mmd(xml, v.count);
    }
    
    void    write_pinned(XmlNode& xml, const Pinned& v)
    {
        write_base(xml, v);
        write_children(xml, szPin, v.pins, write_pin);
    }
    
    void    write_node(XmlNode& xml, const Node& v)
    {   
        write_pinned(xml, v);
    }

    void    write_socket(XmlNode& xml, const Socket& v)
    {
        if(!v.node.empty())
            write_attribute(xml, szNode, v.node);
        if(!v.pin.empty())
            write_attribute(xml, szPin, v.pin);
        if(!v.sub.empty())
            write_attribute(xml, szSub, v.sub);
        write_children(xml, szNode, v.nodes, write_xn<std::string>);
    }
    
    void    write_edge(XmlNode& xml, const Edge& v)
    {
        write_base(xml, v);
        write_child(xml, szSource, v.source, write_socket);
        write_child(xml, szTarget, v.target, write_socket);
        write_children(xml, szData, v.datas, write_xn<std::string>);
    }
    
    void    write_graph(XmlNode& xml, const Graph& v)
    {
        write_pinned(xml, v);
        write_children(xml, szNode, v.nodes, write_node);
        write_children(xml, szEdge, v.edges, write_edge);
    }
    
    
    void    write_xn(XmlNode& xml, const Document& v)
    {
        write_base(xml, v);
        write_children(xml, szGraph, v.graphs, write_graph);
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
        write_attribute(*root, szFormat, szVersion);
        write_xn(*root, doc);
        return errors::none();
    }
}
