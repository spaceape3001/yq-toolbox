////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

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
#include "vector_math.hpp"
#include "tensor_math.hpp"

namespace yq {
    
//  --------------------------------------------------------
//  HELPERs
//
//  These are functions that are needed for the others, so must be listed first


    template <typename T>
    constexpr AxBox1<T> aabb(const Vector1<T>& a, const Vector1<T>& b)
    {
        return { min_elem(a,b), max_elem(a,b) };
    }

    template <typename T>
    constexpr AxBox2<T> aabb(const Vector2<T>& a, const Vector2<T>& b)
    {
        return { min_elem(a,b), max_elem(a,b) };
    }

    template <typename T>
    constexpr AxBox3<T> aabb(const Vector3<T>& a, const Vector3<T>& b)
    {
        return { min_elem(a,b), max_elem(a,b) };
    }

    template <typename T>
    constexpr AxBox4<T> aabb(const Vector4<T>& a, const Vector4<T>& b)
    {
        return { min_elem(a,b), max_elem(a,b) };
    }

    template <typename T>
    square_t<T>    delta_area(const Vector2<T>&a, const Vector2<T>& b)
    {
        return (b.x-a.x)*(b.y-a.y);
    }


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

    /*! \brief "Point area" of the points
    
        This is a helper to area and other functions, 
        simply does an "area" of the point deltas, 
        no sign correction, no scaling.
    */
    template <typename T>
    square_t<T>    point_area(const Triangle2<T>& tri)
    {
        return delta_area(tri.b, tri.a) + delta_area(tri.c, tri.b) + delta_area(tri.a, tri.c);
    }

    /*! \brief "Point area" of the points
    
        This is a helper to area and other functions, 
        simply does an "area" of the point deltas, 
        no sign correction, no scaling.
    */
    template <typename T>
    square_t<T>    point_area(const Quadrilateral2<T>& quad)
    {
        return delta_area(quad.b, quad.a) + delta_area(quad.c, quad.b) + delta_area(quad.d, quad.c) + delta_area(quad.a, quad.d);
    }

    //  ---------------------------------------
    //  CORNERS, using an ENU coordinate system
    //  ---------------------------------------
    
    //  -----------
    //  RECTANGLE 2
    //  -----------

    template <typename T>
    Vector2<T>  northeast(const Rectangle2<T>& rect)
    {
        return { rect.position.x+rect.size.x, rect.position.y+rect.size.y };
    }

    template <typename T>
    Vector2<T>  northwest(const Rectangle2<T>& rect)
    {
        return { rect.position.x, rect.position.y+rect.size.y };
    }

    template <typename T>
    Vector2<T>  southeast(const Rectangle2<T>& rect)
    {
        return { rect.position.x+rect.size.x, rect.position.y };
    }

    template <typename T>
    Vector2<T>  southwest(const Rectangle2<T>& rect)
    {
        return { rect.position.x, rect.position.y };
    }

    //  -------
    //  AXBOX 2
    //  -------
    
    template <typename T>
    Vector2<T>  northeast(const AxBox2<T>& ax)
    {
        return ax.hi;
    }

    template <typename T>
    Vector2<T>  northwest(const AxBox2<T>& ax)
    {
        return { ax.lo.x, ax.hi.y };
    }

    template <typename T>
    Vector2<T>  southeast(const AxBox2<T>& ax)
    {
        return { ax.hi.x, ax.lo.y };
    }

    template <typename T>
    Vector2<T>  southwest(const AxBox2<T>& ax)
    {
        return ax.lo;
    }

    //  -------
    //  AXBOX 3
    //  -------


    template <typename T>
    Vector3<T>  northeast_bottom(const AxBox3<T>& ax)
    {
        return { ax.hi.x, ax.hi.y, ax.lo.z };
   }

    template <typename T>
    Vector3<T>  northeast_top(const AxBox3<T>& ax)
    {
        return ax.hi;
    }


    template <typename T>
    Vector3<T>  northwest_bottom(const AxBox3<T>& ax)
    {
        return { ax.lo.x, ax.hi.y, ax.lo.z };
    }

    template <typename T>
    Vector3<T>  northwest_top(const AxBox3<T>& ax)
    {
        return { ax.lo.x, ax.hi.y, ax.hi.z };
    }

    template <typename T>
    Vector3<T>  southeast_bottom(const AxBox2<T>& ax)
    {
        return { ax.hi.x, ax.lo.y, ax.lo.z };
    }

    template <typename T>
    Vector3<T>  southeast_top(const AxBox2<T>& ax)
    {
        return { ax.hi.x, ax.lo.y, ax.hi.z };
    }

    template <typename T>
    Vector3<T>  southwest_bottom(const AxBox2<T>& ax)
    {
        return ax.lo;
    }

    template <typename T>
    Vector3<T>  southwest_top(const AxBox2<T>& ax)
    {
        return { ax.lo.x, ax.lo.y, ax.hi.z };
    }


//  --------------------------------------------------------
//  COMPOSITION


    template <typename T>
    AxBox2<T>   aabb(const Circle2<T>&a)
    {
        T       r   = abs(a.r);
        return {{
            a.pt.x - r,
            a.pt.y - r
        },{
            a.pt.x + r,
            a.pt.y + r
        }};
    }
    
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
    AxBox2<T>   aabb(const Quadrilateral2<T>& quad)
    {
        return { 
            min_elem(min_elem(quad.a, quad.b), min_elem(quad.c, quad.d)), 
            max_elem(max_elem(quad.a, quad.b), min_elem(quad.c, quad.d))
        };
    }

    template <typename T>
    AxBox2<T>   aabb(const Rectangle2<T>& rect)
    {
        return aabb(southwest(rect), northeast(rect));
    }

    template <typename T>
    AxBox1<T>   aabb(const Segment1<T>& a)
    {
        return aabb(a.lo, a.hi);
    }
    
    template <typename T>
    AxBox2<T>   aabb(const Segment2<T>& a)
    {
        return aabb(a.lo, a.hi);
    }
    
    template <typename T>
    AxBox3<T>   aabb(const Segment3<T>& a)
    {
        return aabb(a.lo, a.hi);
    }
    
    template <typename T>
    AxBox4<T>   aabb(const Segment4<T>& a)
    {
        return aabb(a.lo, a.hi);
    }
    
    template <typename T>
    AxBox3<T>   aabb(const Sphere3<T>&a)
    {
        T       r   = abs(a.r);
        return {{
            a.pt.x - r,
            a.pt.y - r,
            a.pt.z - r
        },{
            a.pt.x + r,
            a.pt.y + r,
            a.pt.z + r
        }};
    }
    
    template <typename T>
    AxBox4<T>   aabb(const Sphere4<T>&a)
    {
        T       r   = abs(a.r);
        return {{
            a.pt.x - r,
            a.pt.y - r,
            a.pt.z - r,
            a.pt.w - r
        },{
            a.pt.x + r,
            a.pt.y + r,
            a.pt.z + r,
            a.pt.w + r
        }};
    }
    
    template <typename T>
    AxBox2<T>   aabb(const Triangle2<T>& tri)
    {
        return { 
            min_elem(min_elem(tri.a, tri.b), tri.c), 
            max_elem(max_elem(tri.a, tri.b), tri.c)
        };
    }
    
    template <typename T>
    AxBox3<T>   aabb(const Triangle3<T>& tri)
    {
        return { 
            min_elem(min_elem(tri.a, tri.b), tri.c), 
            max_elem(max_elem(tri.a, tri.b), tri.c)
        };
    }

    template <typename T>
    AxBox4<T>   aabb(const Triangle4<T>& tri)
    {
        return { 
            min_elem(min_elem(tri.a, tri.b), tri.c), 
            max_elem(max_elem(tri.a, tri.b), tri.c)
        };
    }

    template <typename T>
    Circle2<T>  circle(const Vector2<T>& point, T radius)
    {
        return {point, radius};
    }
    
    template <typename T>
    AxCorners1<Vector1<T>>  corners(const AxBox1<T>& v)
    {
        return { 
            v.lo,
            v.hi
        };
    }

    template <typename T>
    AxCorners2<Vector2<T>>  corners(const AxBox2<T>& v)
    {
        return { 
            v.lo,
            { v.lo.x, v.hi.y }, 
            { v.hi.x, v.lo.y }, 
            v.hi
        };
    }

    template <typename T>
    AxCorners3<Vector3<T>>  corners(const AxBox3<T>& v)
    {
        return { 
            v.lo,
            { v.lo.x, v.lo.y, v.hi.z  }, 
            { v.lo.x, v.hi.y, v.lo.z  }, 
            { v.lo.x, v.hi.y, v.hi.z  }, 
            { v.hi.x, v.lo.y, v.lo.z  }, 
            { v.hi.x, v.lo.y, v.hi.z  }, 
            { v.hi.x, v.hi.y, v.lo.z  }, 
            v.hi
        };
    }

    template <typename T>
    AxCorners4<Vector4<T>>  corners(const AxBox4<T>& v)
    {
        return { 
            v.lo, 
            
            { v.lo.x, v.lo.y, v.lo.z, v.hi.w  }, 
            { v.lo.x, v.lo.y, v.hi.z, v.lo.w  }, 
            { v.lo.x, v.lo.y, v.hi.z, v.hi.w  }, 
            { v.lo.x, v.hi.y, v.lo.z, v.lo.w  }, 
            { v.lo.x, v.hi.y, v.lo.z, v.hi.w  }, 
            { v.lo.x, v.hi.y, v.hi.z, v.lo.w  }, 
            { v.lo.x, v.hi.y, v.hi.z, v.hi.w  }, 
             
            { v.hi.x, v.lo.y, v.lo.z, v.lo.w  }, 
            { v.hi.x, v.lo.y, v.lo.z, v.hi.w  }, 
            { v.hi.x, v.lo.y, v.hi.z, v.lo.w  }, 
            { v.hi.x, v.lo.y, v.hi.z, v.hi.w  }, 
            { v.hi.x, v.hi.y, v.lo.z, v.lo.w  }, 
            { v.hi.x, v.hi.y, v.lo.z, v.hi.w  }, 
            { v.hi.x, v.hi.y, v.hi.z, v.lo.w  }, 
            
            v.hi
        };
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
    Quadrilateral2<T> quadrilateral(const AxBox2<T>& ax)
    {
        return { southwest(ax), southeast(ax), northeast(ax), northwest(ax) };
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
    constexpr Segment1<T> segment(const Vector1<T>& a, const Vector1<T>& b)
    {
        return { a, b };
    }
    
    template <typename T>
    constexpr Segment2<T> segment(const Vector2<T>& a, const Vector2<T>& b)
    {
        return { a, b };
    }
    
    template <typename T>
    constexpr Segment3<T> segment(const Vector3<T>& a, const Vector3<T>& b)
    {
        return { a, b };
    }
    
    template <typename T>
    constexpr Segment4<T> segment(const Vector4<T>& a, const Vector4<T>& b)
    {
        return { a, b };
    }

    template <typename T>
    Sphere3<T>  sphere(const Vector3<T>& point, T radius)
    {
        return {point, radius};
    }

    template <typename T>
    Sphere4<T>  sphere(const Vector4<T>& point, T radius)
    {
        return {point, radius};
    }

    template <typename T>
    Tetrahedron3<T>    tetrahedron(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c, const Vector3<T>& d)
    {
        return { a, b, c };
    }

    template <typename T>
    Triangle2<T>    triangle(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c)
    {
        return { a, b, c };
    }
    
    template <typename T>
    Triangle3<T>    triangle(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c)
    {
        return { a, b, c };
    }

    template <typename T>
    Triangle4<T>    triangle(const Vector4<T>& a, const Vector4<T>& b, const Vector4<T>& c)
    {
        return { a, b, c };
    }

    template <typename T>
    Triangle2<T>   xy(const Triangle3<T>& a)
    {
        return { xy(a.a), xy(a.b), xy(a.c) };
    }
    
    template <typename T>
    Triangle3<T>   xy(const Triangle2<T>& a, std::type_identity_t<T> z)
    {
        return { xy(a.a, z), xy(a.b, z), xy(a.c, z) };
    }
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    template <typename T>
    bool    valid(const AxBox1<T>& a)
    {
        return all_lees_equal(a.lo, a.hi);
    }

    template <typename T>
    bool    valid(const AxBox2<T>& a)
    {
        return all_lees_equal(a.lo, a.hi);
    }

    template <typename T>
    bool    valid(const AxBox3<T>& a)
    {
        return all_lees_equal(a.lo, a.hi);
    }

    template <typename T>
    bool    valid(const AxBox4<T>& a)
    {
        return all_lees_equal(a.lo, a.hi);
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Segment1<T>&a, const Tensor11<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Segment1<T>&a, const Tensor12<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Segment1<T>&a, const Tensor13<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Segment1<T>&a, const Tensor14<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Segment2<T>&a, const Tensor21<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Segment2<T>&a, const Tensor22<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Segment2<T>&a, const Tensor23<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Segment2<T>&a, const Tensor24<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Segment3<T>&a, const Tensor31<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Segment3<T>&a, const Tensor32<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Segment3<T>&a, const Tensor33<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Segment3<T>&a, const Tensor34<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Segment4<T>&a, const Tensor41<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Segment4<T>&a, const Tensor42<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Segment4<T>&a, const Tensor43<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Segment4<T>&a, const Tensor44<T>&b)
    {
        return { a.a * b, a.b * b };
    }

    //  ----------------------------------------------

    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Triangle2<T>&a, const Tensor22<T>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Triangle2<T>&a, const Tensor23<T>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Triangle2<T>&a, const Tensor24<T>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Triangle3<T>&a, const Tensor32<T>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Triangle3<T>&a, const Tensor33<T>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Triangle3<T>&a, const Tensor34<T>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Triangle4<T>&a, const Tensor42<T>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Triangle4<T>&a, const Tensor43<T>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Triangle4<T>&a, const Tensor44<T>&b)
    {
        return { a.a * b, a.b * b, a.c*b };
    }


    //  ----------------------------------------------

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Tensor11<T>&a, const Segment1<T>&b)
    {
        return { a * b.a, a * b.b };
    }
    
    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Tensor12<T>&a, const Segment2<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Tensor13<T>&a, const Segment3<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment1<product_t<T,U>>    operator*(const Tensor14<T>&a, const Segment4<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Tensor21<T>&a, const Segment1<T>&b)
    {
        return { a * b.a, a * b.b };
    }
    
    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Tensor22<T>&a, const Segment2<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Tensor23<T>&a, const Segment3<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment2<product_t<T,U>>    operator*(const Tensor24<T>&a, const Segment4<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Tensor31<T>&a, const Segment1<T>&b)
    {
        return { a * b.a, a * b.b };
    }
    
    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Tensor32<T>&a, const Segment2<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Tensor33<T>&a, const Segment3<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment3<product_t<T,U>>    operator*(const Tensor34<T>&a, const Segment4<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Tensor41<T>&a, const Segment1<T>&b)
    {
        return { a * b.a, a * b.b };
    }
    
    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Tensor42<T>&a, const Segment2<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Tensor43<T>&a, const Segment3<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    template <typename T, typename U>
    Segment4<product_t<T,U>>    operator*(const Tensor44<T>&a, const Segment4<T>&b)
    {
        return { a * b.a, a * b.b };
    }

    //  ----------------------------------------------

    
    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Tensor22<T>&a, const Triangle2<T>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Tensor23<T>&a, const Triangle3<T>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle2<product_t<T,U>>    operator*(const Tensor24<T>&a, const Triangle4<T>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Tensor32<T>&a, const Triangle2<T>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Tensor33<T>&a, const Triangle3<T>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle3<product_t<T,U>>    operator*(const Tensor34<T>&a, const Triangle4<T>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Tensor42<T>&a, const Triangle2<T>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Tensor43<T>&a, const Triangle3<T>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

    template <typename T, typename U>
    Triangle4<product_t<T,U>>    operator*(const Tensor44<T>&a, const Triangle4<T>&b)
    {
        return { a * b.a, a * b.b, a * b.c };
    }

//  --------------------------------------------------------
//  UNIONS

    /*! \brief Union of two AABBs
    */
    template <typename T>
    constexpr AxBox1<T> operator|(const AxBox1<T>&a, const AxBox1<T>&b)
    {
        return { min_elem(a.lo, b.lo), max_elem(a.hi, b.hi) };
    }

    /*! \brief Union of two AABBs
    */
    template <typename T>
    constexpr AxBox2<T> operator|(const AxBox2<T>&a, const AxBox2<T>&b)
    {
        return { min_elem(a.lo, b.lo), max_elem(a.hi, b.hi) };
    }

    /*! \brief Union of two AABBs
    */
    template <typename T>
    constexpr AxBox3<T> operator|(const AxBox3<T>&a, const AxBox3<T>&b)
    {
        return { min_elem(a.lo, b.lo), max_elem(a.hi, b.hi) };
    }

    /*! \brief Union of two AABBs
    */
    template <typename T>
    constexpr AxBox4<T> operator|(const AxBox4<T>&a, const AxBox4<T>&b)
    {
        return { min_elem(a.lo, b.lo), max_elem(a.hi, b.hi) };
    }

//  --------------------------------------------------------
//  INTERSECTIONS

    /*! \brief Intersection of two AABBs
    */
    template <typename T>
    constexpr AxBox1<T> operator&(const AxBox1<T>&a, const AxBox1<T>&b)
    {
        return { max_elem(a.lo, b.lo), min_elem(a.hi, b.hi) };
    }

    /*! \brief Intersection of two AABBs
    */
    template <typename T>
    constexpr AxBox2<T> operator&(const AxBox2<T>&a, const AxBox2<T>&b)
    {
        return { max_elem(a.lo, b.lo), min_elem(a.hi, b.hi) };
    }

    /*! \brief Intersection of two AABBs
    */
    template <typename T>
    constexpr AxBox3<T> operator&(const AxBox3<T>&a, const AxBox3<T>&b)
    {
        return { max_elem(a.lo, b.lo), min_elem(a.hi, b.hi) };
    }

    /*! \brief Intersection of two AABBs
    */
    template <typename T>
    constexpr AxBox4<T> operator&(const AxBox4<T>&a, const AxBox4<T>&b)
    {
        return { max_elem(a.lo, b.lo), min_elem(a.hi, b.hi) };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    square_t<T>     area(const AxBox2<T>& ax)
    {
        return component_product(ax.hi-ax.lo);
    }

    template <typename T>
    square_t<T> area(const Circle2<T>& a)
    {
        return std::numbers::pi_v<ieee754_t<T>> * (a.radius*a.radius);
    }
    

    template <typename T>
    square_t<T>    area(const Polygon2<T>& poly)
    {
        return 0.5*abs(point_area(poly.vertex));
    }

    template <typename T>
    square_t<T>    area(const Quadrilateral2<T>& quad)
    {
        return 0.5*abs(point_area(quad));
    }

    template <typename T>
    square_t<T>     area(const Sphere3<T>& sp)
    {
        return 4.0*pi*(sp.radius*sp.radius);
    }

    template <typename T>
    square_t<T>    area(const Triangle2<T>& tri)
    {
        return 0.5*abs(point_area(tri));
    }

    template <typename T>
    T   circumference(const Circle2<T>& a)
    {
        return ieee754_t<T>(2.) * std::numbers::pi_v<ieee754_t<T>> * a.radius;
    }

    template <typename T>
    T           diameter(const Circle2<T>&a)
    {
        return a.radius + a.radius;
    }

    template <typename T>
    T           diameter(const Sphere3<T>&a)
    {
        return a.radius + a.radius;
    }

    template <typename T>
    T           diameter(const Sphere4<T>&a)
    {
        return a.radius + a.radius;
    }

    template <typename T>
    fourth_t<T> hypervolume(const AxBox4<T>& bx)
    {
        return component_product(bx.hi-bx.lo);
    }

    template <typename T>
    bool    is_ccw(const Polygon2<T>& poly)
    {
        return point_area(poly.vertex) < zero_v<T>;
    }

    template <typename T>
    bool    is_ccw(const Triangle2<T>& tri)
    {
        return point_area(tri) < zero_v<T>;
    }

    template <typename T>
    bool    is_clockwise(const Polygon2<T>& poly)
    {
        return point_area(poly.vertex) > zero_v<T>;
    }
    
    template <typename T>
    bool    is_clockwise(const Triangle2<T>& tri)
    {
        return point_area(tri) > zero_v<T>;
    }

    /*! \brief Checks for full occlusion
    
        A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
        \param[in] Big   The "bigger" box, if eclipsed
        \param[in] Small The "smaller" box, if eclipsed
    */
    template <typename T>
    constexpr bool is_eclipsed(const AxBox1<T>& big, const AxBox1<T>& small)
    {
        return all_less_equal(big.lo, small.lo) && all_greater_equal(big.hi, small.hi);
    }

    
    /*! \brief Checks for full occlusion
    
        A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
        \param[in] Big   The "bigger" box, if eclipsed
        \param[in] Small The "smaller" box, if eclipsed
    */
    template <typename T>
    constexpr bool is_eclipsed(const AxBox2<T>& big, const AxBox2<T>& small)
    {
        return all_less_equal(big.lo, small.lo) && all_greater_equal(big.hi, small.hi);
    }
    
    /*! \brief Checks for full occlusion
    
        A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
        \param[in] Big   The "bigger" box, if eclipsed
        \param[in] Small The "smaller" box, if eclipsed
    */
    template <typename T>
    constexpr bool is_eclipsed(const AxBox3<T>& big, const AxBox3<T>& small)
    {
        return all_less_equal(big.lo, small.lo) && all_greater_equal(big.hi, small.hi);
    }

    /*! \brief Checks for full occlusion
    
        A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
        \param[in] Big   The "bigger" box, if eclipsed
        \param[in] Small The "smaller" box, if eclipsed
    */
    template <typename T>
    constexpr bool is_eclipsed(const AxBox4<T>& big, const AxBox4<T>& small)
    {
        return all_less_equal(big.lo, small.lo) && all_greater_equal(big.hi, small.hi);
    }

    template <typename T>
    constexpr bool is_inside(const AxBox1<T>& bx, const Vector1<T>& pt)
    {
        return all_less_equal(bx.lo, pt) && all_less_equal(pt, bx.hi);
    }
    
    template <typename T>
    constexpr bool is_inside(const AxBox2<T>& bx, const Vector2<T>& pt)
    {
        return all_less_equal(bx.lo, pt) && all_less_equal(pt, bx.hi);
    }

    template <typename T>
    constexpr bool is_inside(const AxBox3<T>& bx, const Vector3<T>& pt)
    {
        return all_less_equal(bx.lo, pt) && all_less_equal(pt, bx.hi);
    }

    template <typename T>
    constexpr bool is_inside(const AxBox4<T>& bx, const Vector4<T>& pt)
    {
        return all_less_equal(bx.lo, pt) && all_less_equal(pt, bx.hi);
    }

    /*! \brief Checks for any overlap
    
        This returns TRUE if *ANY* part of the boxes overlap (or touch)
    */
    template <typename T>
    constexpr bool is_overlapped(const AxBox1<T>& a, const AxBox1<T>& b)
    {
        return all_less_equal(a.lo, b.hi) && all_greater_equal(a.hi, b.lo);
    }

    /*! \brief Checks for any overlap
    
        This returns TRUE if *ANY* part of the boxes overlap (or touch)
    */
    template <typename T>
    constexpr bool is_overlapped(const AxBox2<T>& a, const AxBox2<T>& b)
    {
        return all_less_equal(a.lo, b.hi) && all_greater_equal(a.hi, b.lo);
    }

    /*! \brief Checks for any overlap
    
        This returns TRUE if *ANY* part of the boxes overlap (or touch)
    */
    template <typename T>
    constexpr bool is_overlapped(const AxBox3<T>& a, const AxBox3<T>& b)
    {
        return all_less_equal(a.lo, b.hi) && all_greater_equal(a.hi, b.lo);
    }

    /*! \brief Checks for any overlap
    
        This returns TRUE if *ANY* part of the boxes overlap (or touch)
    */
    template <typename T>
    constexpr bool is_overlapped(const AxBox4<T>& a, const AxBox4<T>& b)
    {
        return all_less_equal(a.lo, b.hi) && all_greater_equal(a.hi, b.lo);
    }

    template <typename T>
    T       length(const Segment1<T>& seg)
    {
        return length(seg.b-seg.a);
    }
    
    template <typename T>
    T       length(const Segment2<T>& seg)
    {
        return length(seg.b-seg.a);
    }

    template <typename T>
    T       length(const Segment3<T>& seg)
    {
        return length(seg.b-seg.a);
    }
    

    template <typename T>
    T       length(const Segment4<T>& seg)
    {
        return length(seg.b-seg.a);
    }

    template <typename T>
    requires has_ieee754_v<T>
    Vector1<T>     midpoint(const Segment1<T>& seg)
    {
        return ieee754_t<T>(0.5)*(seg.hi+seg.lo);
    }

    template <typename T>
    requires has_ieee754_v<T>
    Vector2<T>     midpoint(const Segment2<T>& seg)
    {
        return ieee754_t<T>(0.5)*(seg.hi+seg.lo);
    }

    template <typename T>
    requires has_ieee754_v<T>
    Vector3<T>     midpoint(const Segment3<T>& seg)
    {
        return ieee754_t<T>(0.5)*(seg.hi+seg.lo);
    }

    template <typename T>
    requires has_ieee754_v<T>
    Vector4<T>     midpoint(const Segment4<T>& seg)
    {
        return ieee754_t<T>(0.5)*(seg.hi+seg.lo);
    }


    template <typename T>
    T       perimeter(const AxBox2<T>& ax)
    {
        return 2. * component_sum(ax.hi-ax.lo);
    }
    
    template <typename T>
    T   permimeter(const Circle2<T>& a)
    {
        return ieee754_t<T>(2.) * std::numbers::pi_v<ieee754_t<T>> * a.radius;
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
    
    template <typename T>
    requires trait::has_sqrt_v<square_t<T>>
    T       perimeter(const Quadrilateral2<T>& quad)
    {
        return length(quad.b-quad.a)+length(quad.c-quad.b)+length(quad.d-quad.c)+length(quad.a-quad.d);
    }
    
    template <typename T>
    requires trait::has_sqrt_v<square_t<T>>
    T       perimeter(const Triangle2<T>& tri)
    {
        return length(tri.b-tri.a)+length(tri.c-tri.b)+length(tri.a-tri.c);
    }

    template <typename T>
    requires trait::has_sqrt_v<square_t<T>>
    T       perimeter(const Triangle3<T>& tri)
    {
        return length(tri.b-tri.a)+length(tri.c-tri.b)+length(tri.a-tri.c);
    }

    template <typename T>
    requires trait::has_sqrt_v<square_t<T>>
    T       perimeter(const Triangle4<T>& tri)
    {
        return length(tri.b-tri.a)+length(tri.c-tri.b)+length(tri.a-tri.c);
    }

    template <typename T>
    requires has_ieee754_v<T>
    Vector1<T>     point(const Segment1<T>& seg, ieee754_t<T> f)
    {
        return (one_v<ieee754_t<T>> - f) * seg.a + f * seg.b;
    }

    template <typename T>
    requires has_ieee754_v<T>
    Vector2<T>     point(const Segment2<T>& seg, ieee754_t<T> f)
    {
        return (one_v<ieee754_t<T>> - f) * seg.a + f * seg.b;
    }

    template <typename T>
    requires has_ieee754_v<T>
    Vector3<T>     point(const Segment3<T>& seg, ieee754_t<T> f)
    {
        return (one_v<ieee754_t<T>> - f) * seg.a + f * seg.b;
    }
    
    template <typename T>
    requires has_ieee754_v<T>
    Vector4<T>     point(const Segment4<T>& seg, ieee754_t<T> f)
    {
        return (one_v<ieee754_t<T>> - f) * seg.a + f * seg.b;
    }

    template <typename T>
    cube_t<T>       volume(const AxBox3<T>& bx)
    {
        return component_product(bx.hi-bx.lo);
    }
    
    template <typename T>
    cube_t<T>       volume(const Sphere3<T>&sp)
    {
        return (4.0/3.0)*pi*(sp.radius*sp.radius8sp.radius);
    }

}

