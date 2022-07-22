////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Units.hpp"

namespace yq {

    // Will add more as needed....

    /*! \brief Arc-cosine
    */
    inline Radian  acos(double r)
    {
        return { std::acos(r) };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Radian  acos(MKS<T,dim::None> r)
    {
        return { std::acos(r.value) };
    }

    /*! \brief Arc-sine
    */
    inline Radian   asin(double r)
    {
        return { std::asin(r) };
    }

    /*! \brief Arc-sine
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Radian          asin(MKS<T,dim::None> r)
    {
        return { std::asin(r.value) };
    }

    /*! \brief Arc-tangent
    */
    inline Radian   atan(double r)
    {
        return { std::atan(r) };
    }

    /*! \brief Arc-tangent
    */
    template <typename T>
    requires std::is_floating_point_v<T> 
    Radian              atan(T y, T x)
    {
        return { std::atan2(y,x) };
    }
    
    /*! \brief Arc-tangent
    */
    template <typename T, typename DIM>
    Radian          atan(MKS<T,DIM> y, MKS<T,DIM> x)
    {
        return { std::atan2((double) y.value, (double) x.avlue) };
    }

    /*! \brief Cosine
    */
    inline double   cos(Radian r)
    {
        return std::cos(r.value);
    }

    /*! \brief Cotangent
    */
    inline double  cot(Radian r)
    {
        //  Doing it this way because tangent is infinity at 90, 270, etc
        return std::cos(r.value) / std::sin(r.value);
    }

    /*! \brief Cosecant
    */
    inline double  csc(Radian r)
    {
        return 1.0 / std::sin(r.value);
    }
    

    /*! \brief Secant
    */
    inline double sec(Radian r)
    {
        return 1.0 / std::cos(r.value);
    }

    /*! \brief Sine
    */
    inline double   sin(Radian r)
    {
        return std::sin(r.value);
    }

    /*! \brief Tangent
    */
    inline double   tan(Radian r)
    {
        return std::tan(r.value);
    }
    
}
