////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/*
    This file is for all the manually defined stuff for tensors
*/


#include <math/Vector1.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>
#include <math/Tensor11.hpp>
#include <math/Tensor12.hpp>
#include <math/Tensor13.hpp>
#include <math/Tensor14.hpp>
#include <math/Tensor21.hpp>
#include <math/Tensor22.hpp>
#include <math/Tensor23.hpp>
#include <math/Tensor24.hpp>
#include <math/Tensor31.hpp>
#include <math/Tensor32.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor34.hpp>
#include <math/Tensor41.hpp>
#include <math/Tensor42.hpp>
#include <math/Tensor43.hpp>
#include <math/Tensor44.hpp>

namespace yq {

//  --------------------------------------------------------
//  COMPOSITION


//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  SETTERS


//  --------------------------------------------------------
//  BASIC FUNCTIONS


    template <typename T>
    constexpr Tensor31<T>  transpose(const Tensor13<T>&v)
    {
        return {
            v.xx,
            v.xy,
            v.xz
        };
    }

    


    
//  --------------------------------------------------------
//  POSITIVE


//  --------------------------------------------------------
//  NEGATIVE


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  SUBTRACTION


//  --------------------------------------------------------
//  MULTIPLICATION

    //  -------------------------
    //  Tensor11 * (OTHER)


    
    //  -------------------------
    //  Tensor12 * (OTHER)


    //  -------------------------
    //  Tensor13 * (OTHER)

    

    template <typename T, typename U>
    constexpr Tensor11<product_t<T,U>> operator*(const Tensor13<T>& a, const Tensor31<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor12<product_t<T,U>> operator*(const Tensor13<T>& a, const Tensor32<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor13<product_t<T,U>> operator*(const Tensor13<T>& a, const Tensor33<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor13<T>& operator*=(Tensor13<T>&a, const Tensor33<U>& b)
    {
        a = a * b;
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor14<product_t<T,U>> operator*(const Tensor13<T>& a, const Tensor34<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz,
            a.xx*b.xw + a.xy*b.yw + a.xz*b.zw
        };
    }
    
    //  -------------------------
    //  Tensor14 * (OTHER)

    
    //  -------------------------
    //  Tensor21 * (OTHER)


    
    //  -------------------------
    //  Tensor22 * (OTHER)

    
    
    //  -------------------------
    //  Tensor23 * (OTHER)

    //  -------------------------
    //  Tensor24 * (OTHER)

    
    //  -------------------------
    //  Tensor31 * (OTHER)


    //  -------------------------
    //  Tensor32 * (OTHER)
    
    //  -------------------------
    //  Tensor33 * (OTHER)

    
    
    
    //  -------------------------
    //  Tensor34 * (OTHER)


    
    //  -------------------------
    //  Tensor41 * (OTHER)

    //  -------------------------
    //  Tensor42 * (OTHER)


    
    //  -------------------------
    //  Tensor43 * (OTHER)

    
    //  -------------------------
    //  Tensor44 * (OTHER)
    
    

//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

