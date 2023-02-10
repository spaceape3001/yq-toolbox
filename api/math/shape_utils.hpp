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
    Polygon3<T> polygon(const Triangle3<T>& tri)
    {
        return { { tri.a, tri.b, tri.c } };
    }

    template <typename T>
    Polygon4<T> polygon(const Triangle4<T>& tri)
    {
        return { { tri.a, tri.b, tri.c } };
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

    template <typename T, typename U>
    Polygon2<trait::product_t<T,U>>    operator*(const Polygon2<T>&a, const Tensor22<U>& b)
    {
        Polygon2<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon3<trait::product_t<T,U>>    operator*(const Polygon2<T>&a, const Tensor23<U>& b)
    {
        Polygon3<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon4<trait::product_t<T,U>>    operator*(const Polygon2<T>&a, const Tensor24<U>& b)
    {
        Polygon4<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon2<trait::product_t<T,U>>    operator*(const Polygon3<T>&a, const Tensor32<U>& b)
    {
        Polygon2<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon3<trait::product_t<T,U>>    operator*(const Polygon3<T>&a, const Tensor33<U>& b)
    {
        Polygon3<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon4<trait::product_t<T,U>>    operator*(const Polygon3<T>&a, const Tensor34<U>& b)
    {
        Polygon4<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon2<trait::product_t<T,U>>    operator*(const Polygon4<T>&a, const Tensor42<U>& b)
    {
        Polygon2<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon3<trait::product_t<T,U>>    operator*(const Polygon4<T>&a, const Tensor43<U>& b)
    {
        Polygon3<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon4<trait::product_t<T,U>>    operator*(const Polygon4<T>&a, const Tensor44<U>& b)
    {
        Polygon4<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    

    //  ----------------------------------------------



    //  ----------------------------------------------

    //  ----------------------------------------------

    template <typename T, typename U>
    Polygon2<trait::product_t<T,U>>    operator*(const Tensor22<T>& a, const Polygon2<U>&b)
    {
        Polygon2<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon2<trait::product_t<T,U>>    operator*(const Tensor23<T>& a, const Polygon3<U>&b)
    {
        Polygon2<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon2<trait::product_t<T,U>>    operator*(const Tensor24<T>& a, const Polygon4<U>&b)
    {
        Polygon2<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon3<trait::product_t<T,U>>    operator*(const Tensor32<T>& a, const Polygon2<U>&b)
    {
        Polygon3<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon3<trait::product_t<T,U>>    operator*(const Tensor33<T>& a, const Polygon3<U>&b)
    {
        Polygon3<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon3<trait::product_t<T,U>>    operator*(const Tensor34<T>& a, const Polygon4<U>&b)
    {
        Polygon3<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon4<trait::product_t<T,U>>    operator*(const Tensor42<T>& a, const Polygon2<U>&b)
    {
        Polygon4<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon4<trait::product_t<T,U>>    operator*(const Tensor43<T>& a, const Polygon3<U>&b)
    {
        Polygon4<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon4<trait::product_t<T,U>>    operator*(const Tensor44<T>& a, const Polygon4<U>&b)
    {
        Polygon4<trait::product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    //  ----------------------------------------------

    //  ----------------------------------------------

//  --------------------------------------------------------
//  UNIONS

//  --------------------------------------------------------
//  INTERSECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

