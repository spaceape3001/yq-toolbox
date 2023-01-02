////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PolygonData.hpp"
#include <math/preamble.hpp>
#include <math/AxBox3.hpp>
#include <math/Segment3.hpp>
#include <math/Vector3.hpp>

namespace yq {

    /*! \brief Structure for polygon data
    */
    template <typename T>
    struct Polygon3 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector3<T>>  vertex;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Polygon3&) const noexcept = default;
        
        operator PolygonData<Vector3<T>>() const 
        {
            return { vertex };
        }

        /*! \brief Computes the axially aligned bounding box of this polygon
        */
        AxBox3<T>   bounds() const
        {
            if(vertex.empty())
                return nan_v<AxBox2<T>>;
            AxBox3<T>   ret;
            ret.lo = ret.hi = vertex.front();
            size_t n = vertex.size();
            for(size_t i=1;i<n;++i)
                ret |= vertex[i];
            return ret;
        }
        
        /*
            //  visitor patterns... eventually
        template <typename Pred>
        auto    per_segment(Pred pred) const
        {
            static constexpr const bool     has_first_flag  = std::is_invocable<pred, Segment3<T>, bool>;
        }
        
        template <typename Pred>
        auto    per_side(Pred pred) const
        {
        }

        template <typename Pred>
        auto    per_vertex(Pred pred) const
        {
        }
        */

        //! Computes the perimeter of the polygon 
        //! \note accuracy may vary on integral types
        T       perimeter() const
        {
            if(vertex.empty())
                return T{};
            T   ret = (vertex.back()-vertex.front()).length();
            size_t n = vertex.size() - 1;
            for(size_t i=0;i<n;++i)
                ret += (vertex[i+1]-vertex[i]).length();
            return ret;
        }
        
        //! Converts the polygon to segments
        std::vector<Segment3<T>>    segments() const
        {
            std::vector<Segment3<T>>    ret;
            if(!vertex.empty()){
                ret.reserve(vertex.size());
                ret.push_back(segment(vertex.back(), vertex.front()));
                size_t n = vertex.size() - 1;
                for(size_t i=0;i<n;++i)
                    ret.push_back(segment(vertex[i], vertex[i+1]));
            }
            return ret;
        }

    };
    
//  --------------------------------------------------------
//  COMPOSITION

    YQ_IEEE754_1(Polygon3)
    YQ_ZERO_1(Polygon3, { })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    /*! \brief Create an axially aligned bounding box from a polygon
    */
    template <typename T>
    AxBox3<T>   aabb(const Polygon3<T>&poly)
    {
        return poly.bounds();
    }

    //! Tests that all vertices are finite
    template <typename T>
    bool is_finite(const Polygon3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    //! Tests for any vertice that is not-a-number
    template <typename T>
    bool is_nan(const Polygon3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }

    //! Computes the perimeter of the polygon
    template <typename T>
    T       perimeter(const Polygon3<T>& poly)
    {
        return poly.perimeter();
    }

}

YQ_TYPE_DECLARE(yq::Polygon3D)
YQ_TYPE_DECLARE(yq::Polygon3F)

