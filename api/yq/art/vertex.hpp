////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/units.hpp>
#include <yq/art/forward.hpp>
#include <yq/coord/Polar2.hpp>
#include <yq/coord/Cylindrical3.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/vector/Vector4.hpp>
#include <yq/typedef/xml.hpp>

namespace yq::art {
    class Point;

        // and if we go algebraic, add to it...
    using vertex_t   = std::variant<
        std::monostate,     //< Uninitialized default (ie, consider it zero-dim)
        Vector2D,           //< 2D position
        Vector3D,           //< 3D position
        Vector4D,           //< 4D position
        Polar2H,            //< Range/Azimuth polar (in degrees).
        Cylindrical3H, 
        ID, 
        Key
    >; // offset...? TBD
    
    //! True if the vertex is "empty" (ie monostate)
    bool        vtx_empty(const vertex_t&);
    
    //! True if the vertex is a reference
    bool        vtx_reference(const vertex_t&);

    //! True if the vertex is a value
    bool        vtx_value(const vertex_t&);

    //! Extracts a 2D vector (if possible)
    //! \note 3D & 4D will be in the xy plane
    //! \return valid Vector2D if value, NAN otherwise
    Vector2D    vtx_vector2(const vertex_t&);
    
    //! Extracts a 3D vector (if possible)
    //! \note 2D will have z as zero, 4D will be in the xyz space
    //! \return valid Vector3D if value, NAN otherwise
    Vector3D    vtx_vector3(const vertex_t&);
    
    //! Extracts a 4D vector (if possible)
    //! \note 2D/3D will have missing components "zero"
    //! \return valid Vector4D if value, NAN otherwise
    Vector4D    vtx_vector4(const vertex_t&);

    void    write_vertices(XmlNode&, std::initializer_list<const vertex_t*>);
    void    write_vertices(XmlNode&, std::span<const vertex_t>);
        
    bool    read_vertices(const XmlNode&, std::initializer_list<vertex_t*>);
    bool    read_vertices(const XmlNode&, std::vector<vertex_t>&);

}

//  Not doing this generically....
//YQ_TYPE_DECLARE(yq::art::vertex_t)
