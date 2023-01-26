////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PolygonData.hpp"
#include <math/preamble.hpp>
#include <math/AxBox4.hpp>
#include <math/Vector4.hpp>

namespace yq {


    /*! \brief Structure for polygon data
    */
    template <typename T>
    struct Polygon4 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector4<T>>  vertex;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Polygon4&) const noexcept = default;
        
        operator PolygonData<Vector4<T>>() const 
        {
            return { vertex };
        }

        //! Addsa a point to the polygon
        Polygon4&   operator<<(const Vector4<T>& pt) 
        {
            vertex.push_back(pt);
            return *this;
        }


        /*! \brief Computes the axially aligned bounding box of this polygon
        */
        AxBox4<T>   bounds() const
        {
            if(vertex.empty())
                return nan_v<AxBox2<T>>;
            AxBox4<T>   ret;
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
            static constexpr const bool     has_first_flag  = std::is_invocable<pred, Segment4<T>, bool>;
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
        std::vector<Segment4<T>>    segments() const
        {
            std::vector<Segment4<T>>    ret;
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
    

    YQ_IEEE754_1(Polygon4)
    YQ_ZERO_1(Polygon4, { })

//  --------------------------------------------------------
    template <typename T>
    bool is_finite(const Polygon4<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    template <typename T>
    bool is_nan(const Polygon4<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }

    template <typename T>
    AxBox4<T>   aabb(const Polygon4<T>&poly)
    {
        return poly.bounds();
    }
    
    template <typename T>
    T       perimeter(const Polygon4<T>& poly)
    {
        return poly.perimeter();
    }

}

YQ_TYPE_DECLARE(yq::Polygon4D)
YQ_TYPE_DECLARE(yq::Polygon4F)

