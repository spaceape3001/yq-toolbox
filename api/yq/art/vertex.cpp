////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "vertex.hpp"

#include <yq/art/logging.hpp>
#include <yq/xml/XmlUtils.hpp>

#include <yq/coord/Polar2.hxx>
#include <yq/coord/Cylindrical3.hxx>

#ifdef NAN
    #undef NAN
#endif

namespace yq::art {

    bool        vtx_empty(const vertex_t&vtx)
    {
        return static_cast<bool>(std::get_if<std::monostate>(&vtx));
    }
    
    bool        vtx_reference(const vertex_t&vtx)
    {
        return std::get_if<ID>(&vtx) || std::get_if<Key>(&vtx);
    }

    bool        vtx_value(const vertex_t&vtx)
    {
        return 
            std::get_if<Vector2D>(&vtx) ||
            std::get_if<Vector3D>(&vtx) ||
            std::get_if<Vector4D>(&vtx) ||
            std::get_if<Polar2H>(&vtx) ||
            std::get_if<Cylindrical3H>(&vtx);
    }

    Vector2D    vtx_vector2(const vertex_t& vtx)
    {
        if(auto p = std::get_if<Vector2D>(&vtx))
            return *p;
        if(auto p = std::get_if<Vector3D>(&vtx))
            return { p->x, p->y };
        if(auto p = std::get_if<Vector4D>(&vtx))
            return { p->x, p->y };
        if(auto p = std::get_if<Polar2H>(&vtx))
            return p->to_clock();
        if(auto p = std::get_if<Cylindrical3H>(&vtx))
            return Polar2H(p->angle, p->radius).to_clock();
        return NAN;
    }
    
    Vector3D    vtx_vector3(const vertex_t& vtx)
    {
        if(auto p = std::get_if<Vector2D>(&vtx))
            return { p->x, p->y, 0. };
        if(auto p = std::get_if<Vector3D>(&vtx))
            return *p;
        if(auto p = std::get_if<Vector4D>(&vtx))
            return { p->x, p->y, p->z };
        if(auto p = std::get_if<Polar2H>(&vtx)){
            Vector2D    v   = p->to_clock();
            return { v.x, v.y, 0. };
        }
        if(auto p = std::get_if<Cylindrical3H>(&vtx))
            return p->to_clock();
        return NAN;
    }
    
    Vector4D    vtx_vector4(const vertex_t& vtx)
    {
        if(auto p = std::get_if<Vector2D>(&vtx))
            return { p->x, p->y, 0., 0. };
        if(auto p = std::get_if<Vector3D>(&vtx))
            return { p->x, p->y, p->z, 0. };
        if(auto p = std::get_if<Vector4D>(&vtx))
            return *p;
        if(auto p = std::get_if<Polar2H>(&vtx)){
            Vector2D    v   = p->to_clock();
            return { v.x, v.y, 0., 0. };
        }
        if(auto p = std::get_if<Cylindrical3H>(&vtx)){
            Vector3D    v   = p->to_clock();
            return { v.x, v.y, v.z, 0. };
        }
        return NAN;
    }
    

    ////////////////////////////////////////////////////////////////////////////

    //! Creates a vertex on this node, 
    static void     write_vertex(XmlNode& xr, const vertex_t& vtx)
    {
        if(std::get_if<std::monostate>(&vtx)){
            xr.create_element("v0");  // 0D "monostate"
        }
        if(auto p = std::get_if<Vector2D>(&vtx)){
            auto& x = *xr.create_element("v2");
            write_attribute(x, "x", p->x);
            write_attribute(x, "y", p->y);
        }
        if(auto p = std::get_if<Vector3D>(&vtx)){
            auto& x = *xr.create_element("v3");
            write_attribute(x, "x", p->x);
            write_attribute(x, "y", p->y);
            write_attribute(x, "z", p->z);
        }
        if(auto p = std::get_if<Vector4D>(&vtx)){
            auto& x = *xr.create_element("v4");
            write_attribute(x, "x", p->x);
            write_attribute(x, "y", p->y);
            write_attribute(x, "z", p->z);
            write_attribute(x, "w", p->w);
        }
        if(auto p=std::get_if<Polar2H>(&vtx)){
            auto& x = *xr.create_element("vp");
            write_attribute(x, "h", p->angle.value);
            write_attribute(x, "r", p->radius);
        }
        if(auto p=std::get_if<Cylindrical3H>(&vtx)){
            auto& x = *xr.create_element("vc");
            write_attribute(x, "h", p->angle.value);
            write_attribute(x, "r", p->radius);
            write_attribute(x, "z", p->z);
        }
        if(auto p=std::get_if<ID>(&vtx)){
            auto& x = *xr.create_element("vi");
            write_attribute(x, "id", p->id);
        }
        if(auto p=std::get_if<Key>(&vtx)){
            auto& x = *xr.create_element("vk");
            write_attribute(x, "key", p->key);
        }
    }
    
    enum class Ret {
        Success,
        NoMatch,
        Parsing
    };
    
    static Ret     read_vertex(const XmlNode&xn, vertex_t&vtx)
    {
        if(xn.name()[0] != 'v')
            return Ret::NoMatch;
        switch(xn.name()[1]){
        case '0':
            if(xn.name() == "v0"){
                vtx = {};
                return Ret::Success;
            }
            break;
        case '2':
            if(xn.name() == "v2"){
                auto x  = read_attribute(xn, "x", x_double);
                auto y  = read_attribute(xn, "y", x_double);
                
                if(!x || !y)
                    return Ret::Parsing;
                    
                vtx = Vector2D(*x, *y);
                return Ret::Success;
            }
            break;
        case '3':
            if(xn.name() == "v3"){
                auto x  = read_attribute(xn, "x", x_double);
                auto y  = read_attribute(xn, "y", x_double);
                auto z  = read_attribute(xn, "z", x_double);
                
                if(!x || !y || !z)
                    return Ret::Parsing;
                    
                vtx = Vector3D(*x, *y, *z);
                return Ret::Success;
            }
            break;
        case '4':
            if(xn.name() == "v4"){
                auto x  = read_attribute(xn, "x", x_double);
                auto y  = read_attribute(xn, "y", x_double);
                auto z  = read_attribute(xn, "z", x_double);
                auto w  = read_attribute(xn, "w", x_double);
                
                if(!x || !y || !z || !w)
                    return Ret::Parsing;
                    
                vtx = Vector4D(*x, *y, *z, *w);
                return Ret::Success;
            }
            break;
        case 'c':
            if(xn.name() == "vc"){
                auto r  = read_attribute(xn, "r", x_double);
                auto h  = read_attribute(xn, "h", x_double);
                auto z  = read_attribute(xn, "z", x_double);
                
                if(!r || !h || !z)
                    return Ret::Parsing;
                vtx = Cylindrical3H( *h, *r, *z );
                return Ret::Success;
            }
            break;
        case 'i':
            if(xn.name() == "vi"){
                auto i  = read_attribute(xn, "id", x_uint64);
                if(!i)
                    return Ret::Parsing;
                vtx = ID{ *i };
                return Ret::Success;
            }
            break;
        case 'k':
            if(xn.name() == "vk"){
                vtx  = Key{ read_attribute(xn, "key", x_string) };
                return Ret::Success;
            }
            break;
        case 'p':
            if(xn.name() == "vp"){
                auto r  = read_attribute(xn, "r", x_double);
                auto h  = read_attribute(xn, "h", x_double);
                if(!r || !h)
                    return Ret::Parsing;
                vtx = Polar2H( *h, *r );
                return Ret::Success;
            }
            break;
        default:
            break;
        }
        return Ret::NoMatch;
    }


    void    write_vertices(XmlNode&xn, std::initializer_list<const vertex_t*> vertices)
    {
        for(auto v : vertices){
            if(!v)
                continue;
            write_vertex(xn, *v);
        }
    }
    
    void    write_vertices(XmlNode&xn, std::span<const vertex_t> vertices)
    {
        for(const auto& v : vertices)
            write_vertex(xn, v);
    }

    bool    read_vertices(const XmlNode& xn, std::initializer_list<vertex_t*> vertices)
    {
        bool    success = true;
        for(auto& v : vertices){    // pre-filter against null pointers
            if(!v){
                #ifndef NDEBUG
                artAlert << "Null vertex pointers detected in Shape::read_vertices(), aborting call";
                #endif
                return false;
            }
        }
        
        auto itr            = vertices.begin();
        for(const XmlNode* x = xn.first_node(); (itr != vertices.end()) && x; x=x->next_sibling()){
            if(x->name()[0] != 'v')
                continue;
            switch(read_vertex(*x, * (vertex_t*) itr)){
            case Ret::Success:
                ++itr;
                break;
            case Ret::NoMatch:  // not an error, could be another v-based element
                break;
            case Ret::Parsing:  // parsing failure
                success     = false;
                *(vertex_t*) (itr++)  = vertex_t{};
                break;
            }
        }
        return success && (itr == vertices.end());
    }
    
    bool    read_vertices(const XmlNode&xn, std::vector<vertex_t>& vertices)
    {
        bool    success = true;
        for(const XmlNode* x = xn.first_node(); x; x=x->next_sibling()){
            if(x->name()[0] != 'v')
                continue;
            vertex_t    v;
            switch(read_vertex(*x, v)){
            case Ret::Success:
                vertices.push_back(std::move(v));
                break;
            case Ret::NoMatch:  // not an error
                break;
            case Ret::Parsing:  // parsing failure
                vertices.push_back(vertex_t{});
                success = false;
                break;
            }
        }
        return success;
    }
}
