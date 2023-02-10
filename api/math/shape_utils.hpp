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

#include <math/AxBox1.hpp>
#include <math/AxBox2.hpp>
#include <math/AxBox3.hpp>
#include <math/AxBox4.hpp>
#include <math/AxCorners1.hpp>
#include <math/AxCorners2.hpp>
#include <math/AxCorners3.hpp>
#include <math/AxCorners4.hpp>
#include <math/Circle2.hpp>
#include <math/Normal2.hpp>
#include <math/Normal3.hpp>
#include <math/Plane3.hpp>
#include <math/Polygon2.hpp>
#include <math/Polygon3.hpp>
#include <math/Polygon4.hpp>
#include <math/Quadrilateral2.hpp>
#include <math/Ray2.hpp>
#include <math/Ray3.hpp>
#include <math/Ray4.hpp>
#include <math/RGB.hpp>
#include <math/RGBA.hpp>
#include <math/Segment1.hpp>
#include <math/Segment2.hpp>
#include <math/Segment3.hpp>
#include <math/Segment4.hpp>
#include <math/Sphere3.hpp>
#include <math/Sphere4.hpp>
#include <math/Triangle2.hpp>
#include <math/Triangle3.hpp>
#include <math/Triangle4.hpp>
#include <math/Vector1.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

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

