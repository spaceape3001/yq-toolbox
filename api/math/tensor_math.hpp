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
#include <math/vector_math.hpp>

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
    constexpr Tensor21<T>  transpose(const Tensor12<T>&v)
    {
        return {
            v.xx,
            v.xy
        };
    }

    template <typename T>
    constexpr Tensor31<T>  transpose(const Tensor13<T>&v)
    {
        return {
            v.xx,
            v.xy,
            v.xz
        };
    }

    template <typename T>
    constexpr Tensor41<T>  transpose(const Tensor14<T>&v)
    {
        return {
            v.xx,
            v.xy,
            v.xz,
            v.xw
        };
    }

    template <typename T>
    constexpr Tensor12<T>  transpose(const Tensor21<T>&v)
    {
        return {
            v.xx, v.yx
        };
    }



    
    template <typename T>
    constexpr Tensor32<T>  transpose(const Tensor23<T>&v)
    {
        return {
            v.xx, v.yx,
            v.xy, v.yy,
            v.xz, v.yz
        };
    }
    
    template <typename T>
    constexpr Tensor42<T>  transpose(const Tensor24<T>&v)
    {
        return {
            v.xx, v.yx,
            v.xy, v.yy,
            v.xz, v.yz,
            v.xw, v.yw
        };
    }


    template <typename T>
    constexpr Tensor13<T>  transpose(const Tensor31<T>&v)
    {
        return {
            v.xx, v.yx, v.zx
        };
    }

    
    template <typename T>
    constexpr Tensor23<T>  transpose(const Tensor32<T>&v)
    {
        return {
            v.xx, v.yx, v.zx,
            v.xy, v.yy, v.zy
        };
    }



    
    template <typename T>
    constexpr Tensor43<T>  transpose(const Tensor34<T>&v)
    {
        return {
            v.xx, v.yx, v.zx,
            v.xy, v.yy, v.zy,
            v.xz, v.yz, v.zz,
            v.xw, v.yw, v.zw
        };
    }



    template <typename T>
    constexpr Tensor14<T>  transpose(const Tensor41<T>&v)
    {
        return {
            v.xx, v.yx, v.zx, v.wx
        };
    }


    
    template <typename T>
    constexpr Tensor24<T>  transpose(const Tensor42<T>&v)
    {
        return {
            v.xx, v.yx, v.zx, v.wx,
            v.xy, v.yy, v.zy, v.wy
        };
    }

    
    template <typename T>
    constexpr Tensor34<T>  transpose(const Tensor43<T>&v)
    {
        return {
            v.xx, v.yx, v.zx, v.wx,
            v.xy, v.yy, v.zy, v.wy,
            v.xz, v.yz, v.zz, v.wz
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


    template <typename T, typename U>
    constexpr Tensor12<product_t<T,U>> operator*(const Tensor11<T>& a, const Tensor12<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor13<product_t<T,U>> operator*(const Tensor11<T>& a, const Tensor13<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,
            a.xx*b.xz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor14<product_t<T,U>> operator*(const Tensor11<T>& a, const Tensor14<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,
            a.xx*b.xz,
            a.xx*b.xw
        };
    }

    
    //  -------------------------
    //  Tensor12 * (OTHER)

    template <typename T, typename U>
    constexpr Tensor11<product_t<T,U>> operator*(const Tensor12<T>& a, const Tensor21<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor12<product_t<T,U>> operator*(const Tensor12<T>& a, const Tensor22<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor12<T>& operator*=(Tensor12<T>&a, const Tensor22<U>& b)
    {
        a = a * b;
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor13<product_t<T,U>> operator*(const Tensor12<T>& a, const Tensor23<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,
            a.xx*b.xz + a.xy*b.yz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor14<product_t<T,U>> operator*(const Tensor12<T>& a, const Tensor24<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,
            a.xx*b.xz + a.xy*b.yz,
            a.xx*b.xw + a.xy*b.yw
        };
    }

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

   

    template <typename T, typename U>
    constexpr Tensor11<product_t<T,U>> operator*(const Tensor14<T>& a, const Tensor41<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor12<product_t<T,U>> operator*(const Tensor14<T>& a, const Tensor42<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor13<product_t<T,U>> operator*(const Tensor14<T>& a, const Tensor43<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz + a.xw*b.wz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor14<product_t<T,U>> operator*(const Tensor14<T>& a, const Tensor44<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz + a.xw*b.wz,
            a.xx*b.xw + a.xy*b.yw + a.xz*b.zw + a.xw*b.ww
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor14<T>& operator*=(Tensor14<T>&a, const Tensor44<U>& b)
    {
        a = a * b;
        return a;
    }
    
    //  -------------------------
    //  Tensor21 * (OTHER)


    template <typename T, typename U>
    constexpr Tensor21<product_t<T,U>> operator*(const Tensor21<T>& a, const Tensor11<U>& b)
    {
        return {
            a.xx*b.xx,

            a.yx*b.xx
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor21<T>& operator*=(Tensor21<T>&a, const Tensor11<U>& b)
    {
        a = a * b;
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor22<product_t<T,U>> operator*(const Tensor21<T>& a, const Tensor12<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,

            a.yx*b.xx,
            a.yx*b.xy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor23<product_t<T,U>> operator*(const Tensor21<T>& a, const Tensor13<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,
            a.xx*b.xz,

            a.yx*b.xx,
            a.yx*b.xy,
            a.yx*b.xz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor24<product_t<T,U>> operator*(const Tensor21<T>& a, const Tensor14<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,
            a.xx*b.xz,
            a.xx*b.xw,

            a.yx*b.xx,
            a.yx*b.xy,
            a.yx*b.xz,
            a.yx*b.xw
        };
    }
    
    //  -------------------------
    //  Tensor22 * (OTHER)

    
    template <typename T, typename U>
    constexpr Tensor21<product_t<T,U>> operator*(const Tensor22<T>& a, const Tensor21<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,

            a.yx*b.xx + a.yy*b.yx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor23<product_t<T,U>> operator*(const Tensor22<T>& a, const Tensor23<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,
            a.xx*b.xz + a.xy*b.yz,

            a.yx*b.xx + a.yy*b.yx,
            a.yx*b.xy + a.yy*b.yy,
            a.yx*b.xz + a.yy*b.yz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor24<product_t<T,U>> operator*(const Tensor22<T>& a, const Tensor24<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,
            a.xx*b.xz + a.xy*b.yz,
            a.xx*b.xw + a.xy*b.yw,

            a.yx*b.xx + a.yy*b.yx,
            a.yx*b.xy + a.yy*b.yy,
            a.yx*b.xz + a.yy*b.yz,
            a.yx*b.xw + a.yy*b.yw
        };
    }
    
    //  -------------------------
    //  Tensor23 * (OTHER)



    template <typename T, typename U>
    constexpr Tensor21<product_t<T,U>> operator*(const Tensor23<T>& a, const Tensor31<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor22<product_t<T,U>> operator*(const Tensor23<T>& a, const Tensor32<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor23<product_t<T,U>> operator*(const Tensor23<T>& a, const Tensor33<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor23<T>& operator*=(Tensor23<T>&a, const Tensor33<U>& b)
    {
        a = a * b;
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor24<product_t<T,U>> operator*(const Tensor23<T>& a, const Tensor34<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz,
            a.xx*b.xw + a.xy*b.yw + a.xz*b.zw,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz,
            a.yx*b.xw + a.yy*b.yw + a.yz*b.zw
        };
    }
    
    //  -------------------------
    //  Tensor24 * (OTHER)


    template <typename T, typename U>
    constexpr Tensor21<product_t<T,U>> operator*(const Tensor24<T>& a, const Tensor41<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor22<product_t<T,U>> operator*(const Tensor24<T>& a, const Tensor42<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor23<product_t<T,U>> operator*(const Tensor24<T>& a, const Tensor43<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz + a.xw*b.wz,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz + a.yw*b.wz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor24<product_t<T,U>> operator*(const Tensor24<T>& a, const Tensor44<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz + a.xw*b.wz,
            a.xx*b.xw + a.xy*b.yw + a.xz*b.zw + a.xw*b.ww,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz + a.yw*b.wz,
            a.yx*b.xw + a.yy*b.yw + a.yz*b.zw + a.yw*b.ww
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor24<T>& operator*=(Tensor24<T>&a, const Tensor44<U>& b)
    {
        a = a * b;
        return a;
    }
    
    //  -------------------------
    //  Tensor31 * (OTHER)


    template <typename T, typename U>
    constexpr Tensor31<product_t<T,U>> operator*(const Tensor31<T>& a, const Tensor11<U>& b)
    {
        return {
            a.xx*b.xx,

            a.yx*b.xx,

            a.zx*b.xx
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor31<T>& operator*=(Tensor31<T>&a, const Tensor11<U>& b)
    {
        a = a * b;
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor32<product_t<T,U>> operator*(const Tensor31<T>& a, const Tensor12<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,

            a.yx*b.xx,
            a.yx*b.xy,

            a.zx*b.xx,
            a.zx*b.xy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor33<product_t<T,U>> operator*(const Tensor31<T>& a, const Tensor13<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,
            a.xx*b.xz,

            a.yx*b.xx,
            a.yx*b.xy,
            a.yx*b.xz,

            a.zx*b.xx,
            a.zx*b.xy,
            a.zx*b.xz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor34<product_t<T,U>> operator*(const Tensor31<T>& a, const Tensor14<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,
            a.xx*b.xz,
            a.xx*b.xw,

            a.yx*b.xx,
            a.yx*b.xy,
            a.yx*b.xz,
            a.yx*b.xw,

            a.zx*b.xx,
            a.zx*b.xy,
            a.zx*b.xz,
            a.zx*b.xw
        };
    }
    
    //  -------------------------
    //  Tensor32 * (OTHER)

    template <typename T, typename U>
    constexpr Tensor31<product_t<T,U>> operator*(const Tensor32<T>& a, const Tensor21<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,

            a.yx*b.xx + a.yy*b.yx,

            a.zx*b.xx + a.zy*b.yx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor32<product_t<T,U>> operator*(const Tensor32<T>& a, const Tensor22<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,

            a.yx*b.xx + a.yy*b.yx,
            a.yx*b.xy + a.yy*b.yy,

            a.zx*b.xx + a.zy*b.yx,
            a.zx*b.xy + a.zy*b.yy
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor32<T>& operator*=(Tensor32<T>&a, const Tensor22<U>& b)
    {
        a = a * b;
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor33<product_t<T,U>> operator*(const Tensor32<T>& a, const Tensor23<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,
            a.xx*b.xz + a.xy*b.yz,

            a.yx*b.xx + a.yy*b.yx,
            a.yx*b.xy + a.yy*b.yy,
            a.yx*b.xz + a.yy*b.yz,

            a.zx*b.xx + a.zy*b.yx,
            a.zx*b.xy + a.zy*b.yy,
            a.zx*b.xz + a.zy*b.yz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor34<product_t<T,U>> operator*(const Tensor32<T>& a, const Tensor24<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,
            a.xx*b.xz + a.xy*b.yz,
            a.xx*b.xw + a.xy*b.yw,

            a.yx*b.xx + a.yy*b.yx,
            a.yx*b.xy + a.yy*b.yy,
            a.yx*b.xz + a.yy*b.yz,
            a.yx*b.xw + a.yy*b.yw,

            a.zx*b.xx + a.zy*b.yx,
            a.zx*b.xy + a.zy*b.yy,
            a.zx*b.xz + a.zy*b.yz,
            a.zx*b.xw + a.zy*b.yw
        };
    }
    
    //  -------------------------
    //  Tensor33 * (OTHER)

    
    template <typename T, typename U>
    constexpr Tensor31<product_t<T,U>> operator*(const Tensor33<T>& a, const Tensor31<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor32<product_t<T,U>> operator*(const Tensor33<T>& a, const Tensor32<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor34<product_t<T,U>> operator*(const Tensor33<T>& a, const Tensor34<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz,
            a.xx*b.xw + a.xy*b.yw + a.xz*b.zw,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz,
            a.yx*b.xw + a.yy*b.yw + a.yz*b.zw,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy,
            a.zx*b.xz + a.zy*b.yz + a.zz*b.zz,
            a.zx*b.xw + a.zy*b.yw + a.zz*b.zw
        };
    }
    
    //  -------------------------
    //  Tensor34 * (OTHER)

    template <typename T, typename U>
    constexpr Tensor31<product_t<T,U>> operator*(const Tensor34<T>& a, const Tensor41<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx + a.zw*b.wx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor32<product_t<T,U>> operator*(const Tensor34<T>& a, const Tensor42<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx + a.zw*b.wx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy + a.zw*b.wy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor33<product_t<T,U>> operator*(const Tensor34<T>& a, const Tensor43<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz + a.xw*b.wz,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz + a.yw*b.wz,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx + a.zw*b.wx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy + a.zw*b.wy,
            a.zx*b.xz + a.zy*b.yz + a.zz*b.zz + a.zw*b.wz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor34<product_t<T,U>> operator*(const Tensor34<T>& a, const Tensor44<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz + a.xw*b.wz,
            a.xx*b.xw + a.xy*b.yw + a.xz*b.zw + a.xw*b.ww,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz + a.yw*b.wz,
            a.yx*b.xw + a.yy*b.yw + a.yz*b.zw + a.yw*b.ww,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx + a.zw*b.wx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy + a.zw*b.wy,
            a.zx*b.xz + a.zy*b.yz + a.zz*b.zz + a.zw*b.wz,
            a.zx*b.xw + a.zy*b.yw + a.zz*b.zw + a.zw*b.ww
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor34<T>& operator*=(Tensor34<T>&a, const Tensor44<U>& b)
    {
        a = a * b;
        return a;
    }
    
    //  -------------------------
    //  Tensor41 * (OTHER)

    template <typename T, typename U>
    constexpr Tensor41<product_t<T,U>> operator*(const Tensor41<T>& a, const Tensor11<U>& b)
    {
        return {
            a.xx*b.xx,

            a.yx*b.xx,

            a.zx*b.xx,

            a.wx*b.xx
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor41<T>& operator*=(Tensor41<T>&a, const Tensor11<U>& b)
    {
        a = a * b;
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor42<product_t<T,U>> operator*(const Tensor41<T>& a, const Tensor12<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,

            a.yx*b.xx,
            a.yx*b.xy,

            a.zx*b.xx,
            a.zx*b.xy,

            a.wx*b.xx,
            a.wx*b.xy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor43<product_t<T,U>> operator*(const Tensor41<T>& a, const Tensor13<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,
            a.xx*b.xz,

            a.yx*b.xx,
            a.yx*b.xy,
            a.yx*b.xz,

            a.zx*b.xx,
            a.zx*b.xy,
            a.zx*b.xz,

            a.wx*b.xx,
            a.wx*b.xy,
            a.wx*b.xz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor44<product_t<T,U>> operator*(const Tensor41<T>& a, const Tensor14<U>& b)
    {
        return {
            a.xx*b.xx,
            a.xx*b.xy,
            a.xx*b.xz,
            a.xx*b.xw,

            a.yx*b.xx,
            a.yx*b.xy,
            a.yx*b.xz,
            a.yx*b.xw,

            a.zx*b.xx,
            a.zx*b.xy,
            a.zx*b.xz,
            a.zx*b.xw,

            a.wx*b.xx,
            a.wx*b.xy,
            a.wx*b.xz,
            a.wx*b.xw
        };
    }
    
    //  -------------------------
    //  Tensor42 * (OTHER)


    template <typename T, typename U>
    constexpr Tensor41<product_t<T,U>> operator*(const Tensor42<T>& a, const Tensor21<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,

            a.yx*b.xx + a.yy*b.yx,

            a.zx*b.xx + a.zy*b.yx,

            a.wx*b.xx + a.wy*b.yx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor42<product_t<T,U>> operator*(const Tensor42<T>& a, const Tensor22<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,

            a.yx*b.xx + a.yy*b.yx,
            a.yx*b.xy + a.yy*b.yy,

            a.zx*b.xx + a.zy*b.yx,
            a.zx*b.xy + a.zy*b.yy,

            a.wx*b.xx + a.wy*b.yx,
            a.wx*b.xy + a.wy*b.yy
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor42<T>& operator*=(Tensor42<T>&a, const Tensor22<U>& b)
    {
        a = a * b;
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor43<product_t<T,U>> operator*(const Tensor42<T>& a, const Tensor23<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,
            a.xx*b.xz + a.xy*b.yz,

            a.yx*b.xx + a.yy*b.yx,
            a.yx*b.xy + a.yy*b.yy,
            a.yx*b.xz + a.yy*b.yz,

            a.zx*b.xx + a.zy*b.yx,
            a.zx*b.xy + a.zy*b.yy,
            a.zx*b.xz + a.zy*b.yz,

            a.wx*b.xx + a.wy*b.yx,
            a.wx*b.xy + a.wy*b.yy,
            a.wx*b.xz + a.wy*b.yz
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor44<product_t<T,U>> operator*(const Tensor42<T>& a, const Tensor24<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,
            a.xx*b.xz + a.xy*b.yz,
            a.xx*b.xw + a.xy*b.yw,

            a.yx*b.xx + a.yy*b.yx,
            a.yx*b.xy + a.yy*b.yy,
            a.yx*b.xz + a.yy*b.yz,
            a.yx*b.xw + a.yy*b.yw,

            a.zx*b.xx + a.zy*b.yx,
            a.zx*b.xy + a.zy*b.yy,
            a.zx*b.xz + a.zy*b.yz,
            a.zx*b.xw + a.zy*b.yw,

            a.wx*b.xx + a.wy*b.yx,
            a.wx*b.xy + a.wy*b.yy,
            a.wx*b.xz + a.wy*b.yz,
            a.wx*b.xw + a.wy*b.yw
        };
    }
    
    //  -------------------------
    //  Tensor43 * (OTHER)

    template <typename T, typename U>
    constexpr Tensor41<product_t<T,U>> operator*(const Tensor43<T>& a, const Tensor31<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx,

            a.wx*b.xx + a.wy*b.yx + a.wz*b.zx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor42<product_t<T,U>> operator*(const Tensor43<T>& a, const Tensor32<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy,

            a.wx*b.xx + a.wy*b.yx + a.wz*b.zx,
            a.wx*b.xy + a.wy*b.yy + a.wz*b.zy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor43<product_t<T,U>> operator*(const Tensor43<T>& a, const Tensor33<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy,
            a.zx*b.xz + a.zy*b.yz + a.zz*b.zz,

            a.wx*b.xx + a.wy*b.yx + a.wz*b.zx,
            a.wx*b.xy + a.wy*b.yy + a.wz*b.zy,
            a.wx*b.xz + a.wy*b.yz + a.wz*b.zz
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor43<T>& operator*=(Tensor43<T>&a, const Tensor33<U>& b)
    {
        a = a * b;
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor44<product_t<T,U>> operator*(const Tensor43<T>& a, const Tensor34<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz,
            a.xx*b.xw + a.xy*b.yw + a.xz*b.zw,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz,
            a.yx*b.xw + a.yy*b.yw + a.yz*b.zw,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy,
            a.zx*b.xz + a.zy*b.yz + a.zz*b.zz,
            a.zx*b.xw + a.zy*b.yw + a.zz*b.zw,

            a.wx*b.xx + a.wy*b.yx + a.wz*b.zx,
            a.wx*b.xy + a.wy*b.yy + a.wz*b.zy,
            a.wx*b.xz + a.wy*b.yz + a.wz*b.zz,
            a.wx*b.xw + a.wy*b.yw + a.wz*b.zw
        };
    }
    
    //  -------------------------
    //  Tensor44 * (OTHER)
    
    template <typename T, typename U>
    constexpr Tensor41<product_t<T,U>> operator*(const Tensor44<T>& a, const Tensor41<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx + a.zw*b.wx,

            a.wx*b.xx + a.wy*b.yx + a.wz*b.zx + a.ww*b.wx
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor42<product_t<T,U>> operator*(const Tensor44<T>& a, const Tensor42<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx + a.zw*b.wx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy + a.zw*b.wy,

            a.wx*b.xx + a.wy*b.yx + a.wz*b.zx + a.ww*b.wx,
            a.wx*b.xy + a.wy*b.yy + a.wz*b.zy + a.ww*b.wy
        };
    }
    
    template <typename T, typename U>
    constexpr Tensor43<product_t<T,U>> operator*(const Tensor44<T>& a, const Tensor43<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz + a.xw*b.wz,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz + a.yw*b.wz,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx + a.zw*b.wx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy + a.zw*b.wy,
            a.zx*b.xz + a.zy*b.yz + a.zz*b.zz + a.zw*b.wz,

            a.wx*b.xx + a.wy*b.yx + a.wz*b.zx + a.ww*b.wx,
            a.wx*b.xy + a.wy*b.yy + a.wz*b.zy + a.ww*b.wy,
            a.wx*b.xz + a.wy*b.yz + a.wz*b.zz + a.ww*b.wz
        };
    }
    

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

    template <typename T>
    auto determinant(const Tensor11<T>& a)
    {
        return a.xx;
    }

    template <typename T>
    auto determinant(const Tensor22<T>& a)
    {
        return a.xx*a.yy-a.xy*a.yx;
    }

    template <typename T>
    auto determinant(const Tensor33<T>& a)
    {
        return a.xx*(a.yy*a.zz-a.yz*a.zy)+a.xy*(a.zx*a.xz-a.yx*a.zz)+a.xz*(a.yx*a.zy-a.zx*a.yy);
    }
 
    //  4x4 determinant is TODO....
    
    template <typename T>
    Tensor22<inverse_t<T>> inverse(const Tensor22<T>&a)
    {
        auto    di = one_v<T> / determinant(a);
        return {
             di * a.yy, -di * a.xy,
            -di * a.yx,  di * a.xx
        };
    }
    
    template <typename T>
    Tensor33<inverse_t<T>> inverse(const Tensor33<T>&a)
    {
        auto    di = one_v<T> / determinant(a);
        return {
            di*(a.yy*a.zz-a.zy*a.yz), di*(a.xz*a.zy-a.zz*a.xy), di*(a.xy*a.yz-a.yy*a.xz),
            di*(a.yz*a.zx-a.zz*a.yx), di*(a.xx*a.zz-a.xz*a.zx), di*(a.xz*a.yx-a.yz*a.xx),
            di*(a.yx*a.zy-a.zx*a.yy), di*(a.xy*a.zx-a.zy*a.xx), di*(a.xx*a.yy-a.yx*a.xy)
        };
    }
}

