////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3fmt/types.hpp>
#include <yq/units.hpp>
#include <yq/math/Range.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/coord2.hpp>
#include <yq/typedef/coord3.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/typedef/size2.hpp>
#include <yq/typedef/size3.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/typedef/vector3.hpp>
#include <yq/typedef/vector4.hpp>
#include <yq/container/StringMap.hpp>

namespace yq::b3::parse {

#if 0
    struct context_t {
        StringMap       m_colors;
        DoubleMap       m_units;

        std::string_view    color(const std::string& k) const;
        double              unit(const std::string& k) const;
    };
#endif

    /*
        Note, color & length make use of the global context, set before 
        parsing.  (otherwise, no units nor color lookups will occur)
    */


    unit::Degree            angle(std::string_view, unit::Degree def={0.});
    bool                    boolean(std::string_view, bool def=false);
    //Brush                   brush(std::string_view);
    //Color                   color(std::string_view);
    CoordN                  coord(std::string_view);
    Coord2I                 coord2(std::string_view);
    Coord3I                 coord3(std::string_view);
    CountN                  count(std::string_view);
    Font                    font(std::string_view);
    int                     integer(std::string_view, int def=0);
    IntegerSet              integer_set(std::string_view);
    
    //! Searches for ".." (if not present, it'll attempt a simple integer parse, returning identical values)
    RangeI                  irange(std::string_view, const RangeI& def={});
    //double                  length(std::string_view, double def=0.);
    //Pen                     pen(std::string_view);
    //PointN                  point(std::string_view);
    //Vector2D                point2(std::string_view);
    //Vector3D                point3(std::string_view);
    //! Double (but can't use "double" in the name)
    double                  real(std::string_view, double def=0.);
    //SizeN                   size(std::string_view);
    //Size2D                  size2(std::string_view);
    //Size3D                  size3(std::string_view);
    StringSet               string_set(std::string_view);
    VectorN                 vector(std::string_view);
    Vector2D                vector2(std::string_view);
    Vector3D                vector3(std::string_view);
    Vector4D                vector4(std::string_view);
}

