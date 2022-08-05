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
#include "tensor_math.hpp"

namespace yq {
    
//  --------------------------------------------------------
//  HELPERs
//
//  These are functions that are needed for the others, so must be listed first



        //  AREA HELPERS

    /*! \brief "Point area" of the points
    
        This is a helper to area and other functions, 
        simply does an "area" of the point deltas, 
        no sign correction, no scaling.
    */
    template <typename T>
    square_t<T>    point_area(const std::vector<Vector2<T>>& vertex)
    {
        if(vertex.empty())
            return square_t<T>{};
        
        auto cross = [&](size_t a, size_t b){
            auto& va = vertex[a];
            auto& vb = vertex[b];
            return (vb.x-va.x)*(vb.y-va.y);
        };
        
        size_t  n   = vertex.size();
        square_t<T> ret = delta_area(vertex[n-1],vertex[0]);
        --n;
        for(size_t i=0;i<n;++n)
            ret += delta_area(vertex[i], vertex[i+1]);
        return ret;
    }



//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    AxBox2<T>   aabb(const Polygon2<T>&poly)
    {
        if(poly.vertex.empty())
            return nan_v<AxBox2<T>>;
        AxBox2<T>   ret;
        ret.lo = ret.hi = poly.vertex.front();
        size_t n = poly.vertex.size();
        for(size_t i=1;i<n;++i){
            ret.lo = min_elem(ret.lo, poly.vertex[i]);
            ret.hi = max_elem(ret.hi, poly.vertex[i]);
        }
        return ret;
    }

    template <typename T>
    AxBox3<T>   aabb(const Polygon3<T>&poly)
    {
        if(poly.vertex.empty())
            return nan_v<AxBox2<T>>;
        AxBox3<T>   ret;
        ret.lo = ret.hi = poly.vertex.front();
        size_t n = poly.vertex.size();
        for(size_t i=1;i<n;++i){
            ret.lo = min_elem(ret.lo, poly.vertex[i]);
            ret.hi = max_elem(ret.hi, poly.vertex[i]);
        }
        return ret;
    }

    template <typename T>
    AxBox4<T>   aabb(const Polygon4<T>&poly)
    {
        if(poly.vertex.empty())
            return nan_v<AxBox2<T>>;
        AxBox4<T>   ret;
        ret.lo = ret.hi = poly.vertex.front();
        size_t n = poly.vertex.size();
        for(size_t i=1;i<n;++i){
            ret.lo = min_elem(ret.lo, poly.vertex[i]);
            ret.hi = max_elem(ret.hi, poly.vertex[i]);
        }
        return ret;
    }

    

    template <typename T>
    Normal2<T>     normal(const Vector2<T>& dir) 
    {
        return { ~dir };
    }

    template <typename T>
    Normal3<T>     normal(const Vector3<T>& dir) 
    {
        return { ~dir };
    }
    
    template <typename T>
    requires std::is_floating_point_v<T>
    Normal2<T>     normal(T x, std::type_identity_t<T> y)
    {
        return { ~Vector2<T>{x,y} };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Normal3<T>     normal(T x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return { ~Vector3<T>{x,y,z} };
    }

    template <typename T>
    Polygon2<T> polygon(const AxBox2<T>& ax)
    {
        return { { southwest(ax), southeast(ax), northeast(ax), northwest(ax) } };
    }

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
    Polygon2<T> polygon(const Triangle2<T>& tri)
    {
        return { { tri.a, tri.b, tri.c } };
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
    


    template <typename T>
    Tetrahedron3<T>    tetrahedron(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c, const Vector3<T>& d)
    {
        return { a, b, c, d };
    }

    


    
//  --------------------------------------------------------
//  BASIC FUNCTIONS



//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    Polygon2<product_t<T,U>>    operator*(const Polygon2<T>&a, const Tensor22<U>& b)
    {
        Polygon2<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon3<product_t<T,U>>    operator*(const Polygon2<T>&a, const Tensor23<U>& b)
    {
        Polygon3<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon4<product_t<T,U>>    operator*(const Polygon2<T>&a, const Tensor24<U>& b)
    {
        Polygon4<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon2<product_t<T,U>>    operator*(const Polygon3<T>&a, const Tensor32<U>& b)
    {
        Polygon2<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon3<product_t<T,U>>    operator*(const Polygon3<T>&a, const Tensor33<U>& b)
    {
        Polygon3<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon4<product_t<T,U>>    operator*(const Polygon3<T>&a, const Tensor34<U>& b)
    {
        Polygon4<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon2<product_t<T,U>>    operator*(const Polygon4<T>&a, const Tensor42<U>& b)
    {
        Polygon2<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon3<product_t<T,U>>    operator*(const Polygon4<T>&a, const Tensor43<U>& b)
    {
        Polygon3<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    
    template <typename T, typename U>
    Polygon4<product_t<T,U>>    operator*(const Polygon4<T>&a, const Tensor44<U>& b)
    {
        Polygon4<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<T>& v : a.vertex)
            ret.vertex.push_back(v*b);
        return ret;
    }
    

    //  ----------------------------------------------

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Segment1<T>&a, const Tensor11<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Segment1<T>&a, const Tensor12<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Segment1<T>&a, const Tensor13<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Segment1<T>&a, const Tensor14<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Segment2<T>&a, const Tensor21<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Segment2<T>&a, const Tensor22<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Segment2<T>&a, const Tensor23<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Segment2<T>&a, const Tensor24<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Segment3<T>&a, const Tensor31<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Segment3<T>&a, const Tensor32<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Segment3<T>&a, const Tensor33<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Segment3<T>&a, const Tensor34<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Segment4<T>&a, const Tensor41<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Segment4<T>&a, const Tensor42<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Segment4<T>&a, const Tensor43<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Segment4<T>&a, const Tensor44<U>&b)
    {
        return { a.a * b, a.b * b };
    }

    //  ----------------------------------------------

    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Triangle2<T>&a, const Tensor22<U>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Triangle2<T>&a, const Tensor23<U>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Triangle2<T>&a, const Tensor24<U>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Triangle3<T>&a, const Tensor32<U>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Triangle3<T>&a, const Tensor33<U>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Triangle3<T>&a, const Tensor34<U>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Triangle4<T>&a, const Tensor42<U>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Triangle4<T>&a, const Tensor43<U>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Triangle4<T>&a, const Tensor44<U>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    //  ----------------------------------------------

    template <typename T, typename U>
    Polygon2<product_t<T,U>>    operator*(const Tensor22<T>& a, const Polygon2<U>&b)
    {
        Polygon2<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon2<product_t<T,U>>    operator*(const Tensor23<T>& a, const Polygon3<U>&b)
    {
        Polygon2<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon2<product_t<T,U>>    operator*(const Tensor24<T>& a, const Polygon4<U>&b)
    {
        Polygon2<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon3<product_t<T,U>>    operator*(const Tensor32<T>& a, const Polygon2<U>&b)
    {
        Polygon3<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon3<product_t<T,U>>    operator*(const Tensor33<T>& a, const Polygon3<U>&b)
    {
        Polygon3<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon3<product_t<T,U>>    operator*(const Tensor34<T>& a, const Polygon4<U>&b)
    {
        Polygon3<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon4<product_t<T,U>>    operator*(const Tensor42<T>& a, const Polygon2<U>&b)
    {
        Polygon4<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector2<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon4<product_t<T,U>>    operator*(const Tensor43<T>& a, const Polygon3<U>&b)
    {
        Polygon4<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector3<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    template <typename T, typename U>
    Polygon4<product_t<T,U>>    operator*(const Tensor44<T>& a, const Polygon4<U>&b)
    {
        Polygon4<product_t<T,U>>    ret;
        ret.vertex.reserve(a.vertex.size());
        for(const Vector4<U>& v : b.vertex)
            ret.vertex.push_back(a*v);
        return ret;
    }

    //  ----------------------------------------------

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Tensor11<T>&a, const Segment1<U>&b)
    {
        return { a * b.a, a * b.b };
    }
    
    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Tensor12<T>&a, const Segment2<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Tensor13<T>&a, const Segment3<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Tensor14<T>&a, const Segment4<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Tensor21<T>&a, const Segment1<U>&b)
    {
        return { a * b.a, a * b.b };
    }
    
    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Tensor22<T>&a, const Segment2<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Tensor23<T>&a, const Segment3<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Tensor24<T>&a, const Segment4<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Tensor31<T>&a, const Segment1<U>&b)
    {
        return { a * b.a, a * b.b };
    }
    
    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Tensor32<T>&a, const Segment2<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Tensor33<T>&a, const Segment3<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Tensor34<T>&a, const Segment4<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Tensor41<T>&a, const Segment1<U>&b)
    {
        return { a * b.a, a * b.b };
    }
    
    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Tensor42<T>&a, const Segment2<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Tensor43<T>&a, const Segment3<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Tensor44<T>&a, const Segment4<U>&b)
    {
        return { a * b.a, a * b.b };
    }

    //  ----------------------------------------------

    
    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Tensor22<T>&a, const Triangle2<U>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Tensor23<T>&a, const Triangle3<U>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Tensor24<T>&a, const Triangle4<U>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Tensor32<T>&a, const Triangle2<U>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Tensor33<T>&a, const Triangle3<U>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Tensor34<T>&a, const Triangle4<U>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Tensor42<T>&a, const Triangle2<U>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Tensor43<T>&a, const Triangle3<U>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Tensor44<T>&a, const Triangle4<U>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

//  --------------------------------------------------------
//  UNIONS


//  --------------------------------------------------------
//  INTERSECTIONS


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    
    /*! \brief Computes the area of a 2D polygon
    */
    template <typename T>
    square_t<T>    area(const Polygon2<T>& poly)
    {
        return 0.5*abs(point_area(poly.vertex));
    }


    template <typename T>
    bool    is_ccw(const Polygon2<T>& poly)
    {
        return point_area(poly.vertex) < zero_v<T>;
    }


    template <typename T>
    bool    is_clockwise(const Polygon2<T>& poly)
    {
        return point_area(poly.vertex) > zero_v<T>;
    }
    

    template <typename T>
    requires trait::has_sqrt_v<square_t<T>>
    T       perimeter(const Polygon2<T>& poly)
    {
        if(poly.vertex.empty())
            return T{};
        T   ret = length(poly.vertex.back()-poly.vertex.front());
        size_t n = poly.vertex.size() - 1;
        for(size_t i=0;i<n;++i)
            ret += length(poly.vertex[i+1]-poly.vertex[i]);
        return ret;
    }
    
    template <typename T>
    requires trait::has_sqrt_v<square_t<T>>
    T       perimeter(const Polygon3<T>& poly)
    {
        if(poly.vertex.empty())
            return T{};
        T   ret = length(poly.vertex.back()-poly.vertex.front());
        size_t n = poly.vertex.size() - 1;
        for(size_t i=0;i<n;++i)
            ret += length(poly.vertex[i+1]-poly.vertex[i]);
        return ret;
    }
    
    template <typename T>
    requires trait::has_sqrt_v<square_t<T>>
    T       perimeter(const Polygon4<T>& poly)
    {
        if(poly.vertex.empty())
            return T{};
        T   ret = length(poly.vertex.back()-poly.vertex.front());
        size_t n = poly.vertex.size() - 1;
        for(size_t i=0;i<n;++i)
            ret += length(poly.vertex[i+1]-poly.vertex[i]);
        return ret;
    }

}

