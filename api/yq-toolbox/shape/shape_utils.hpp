////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/*
    Even though shape functions are being moved closer to their structures,
    this file will loiter for those routines requiring a complicated 
    inclusion path.
*/

#include <yq/color/RGB.hpp>
#include <yq/color/RGBA.hpp>
#include <yq-toolbox/shape/AxBox1.hpp>
#include <yq-toolbox/shape/AxBox2.hpp>
#include <yq-toolbox/shape/AxBox3.hpp>
#include <yq-toolbox/shape/AxBox4.hpp>
#include <yq-toolbox/shape/AxCorners1.hpp>
#include <yq-toolbox/shape/AxCorners2.hpp>
#include <yq-toolbox/shape/AxCorners3.hpp>
#include <yq-toolbox/shape/AxCorners4.hpp>
#include <yq-toolbox/shape/Circle2.hpp>
#include <yq-toolbox/shape/Normal2.hpp>
#include <yq-toolbox/shape/Normal3.hpp>
#include <yq-toolbox/shape/Plane3.hpp>
#include <yq-toolbox/shape/Polygon2.hpp>
#include <yq-toolbox/shape/Polygon3.hpp>
#include <yq-toolbox/shape/Polygon4.hpp>
#include <yq-toolbox/shape/Quadrilateral2.hpp>
#include <yq-toolbox/shape/Ray2.hpp>
#include <yq-toolbox/shape/Ray3.hpp>
#include <yq-toolbox/shape/Ray4.hpp>
#include <yq-toolbox/shape/Segment1.hpp>
#include <yq-toolbox/shape/Segment2.hpp>
#include <yq-toolbox/shape/Segment3.hpp>
#include <yq-toolbox/shape/Segment4.hpp>
#include <yq-toolbox/shape/Sphere3.hpp>
#include <yq-toolbox/shape/Sphere4.hpp>
#include <yq-toolbox/shape/Triangle2.hpp>
#include <yq-toolbox/shape/Triangle3.hpp>
#include <yq-toolbox/shape/Triangle4.hpp>
#include <yq-toolbox/vector/Vector1.hpp>
#include <yq-toolbox/vector/Vector2.hpp>
#include <yq-toolbox/vector/Vector3.hpp>
#include <yq-toolbox/vector/Vector4.hpp>

namespace yq {
    
//  --------------------------------------------------------
//  HELPERs
//
//  These are functions that are needed for the others, so must be listed first



//  --------------------------------------------------------
//  COMPOSITION


    template <typename T>
    Polygon2<T> polygon(const Quadrilateral2<T>& quad)
    {
        return { { quad.a, quad.b, quad.c, quad.d  } };
    }


    template <typename T>
    Polygon2<T> polygon(const Rectangle2<T>& rect)
    {
        return { { southwest(rect), southeast(rect), northeast(rect), northwest(rect) } };
    }

    template <typename T>
    Polygon2<T> polygon(const Segment2<T>& seg)
    {
        return { { seg.a, seg.b } };
    }

    template <typename T>
    Polygon3<T> polygon(const Segment3<T>& seg)
    {
        return { { seg.a, seg.b } };
    }

    template <typename T>
    Polygon4<T> polygon(const Segment4<T>& seg)
    {
        return { { seg.a, seg.b } };
    }

    

    template <typename T>
    TriangleData<RGB<T>>     rgb(const TriangleData<RGBA<T>>& t)
    {
        return { rgb(t.a), rgb(t.b), rgb(t.c)};
    }

    template <typename T>
    TriangleData<RGBA<T>>     rgba(const TriangleData<RGB<T>>& t, std::type_identity_t<T> a)
    {
        return { rgba(t.a, a), rgba(t.b, a), rgba(t.c, a)};
    }
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

//  --------------------------------------------------------
//  MULTIPLICATION

    //  ----------------------------------------------



    //  ----------------------------------------------

    //  ----------------------------------------------

    //  ----------------------------------------------

    //  ----------------------------------------------

//  --------------------------------------------------------
//  UNIONS

//  --------------------------------------------------------
//  INTERSECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

