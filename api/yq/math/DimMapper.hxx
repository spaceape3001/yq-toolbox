////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/math/DimMapper.hpp>

#include <yq/shape/Size1.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/shape/Size3.hpp>
#include <yq/shape/Size4.hpp>

#include <yq/vector/Vector1.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/vector/Vector4.hpp>

namespace yq {

////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    T   DimMapper::extract(const Size1<T>&v, Ax ax)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        default:
            return zero_v<T>;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Size2<T>&v, Ax ax)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        default:
            return zero_v<T>;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Size3<T>&v, Ax ax)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        case Ax::Zp:
            return v.z;
        case Ax::Zn:
            return -v.z;
        default:
            return zero_v<T>;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Size4<T>&v, Ax ax)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        case Ax::Zp:
            return v.z;
        case Ax::Zn:
            return -v.z;
        case Ax::Wp:
            return v.w;
        case Ax::Wn:
            return -v.w;
        default:
            return zero_v<T>;
        }
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    T   DimMapper::extract(const Vector1<T>&v, Ax ax)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        default:
            return zero_v<T>;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Vector2<T>&v, Ax ax)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        default:
            return zero_v<T>;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Vector3<T>&v, Ax ax)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        case Ax::Zp:
            return v.z;
        case Ax::Zn:
            return -v.z;
        default:
            return zero_v<T>;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Vector4<T>&v, Ax ax)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        case Ax::Zp:
            return v.z;
        case Ax::Zn:
            return -v.z;
        case Ax::Wp:
            return v.w;
        case Ax::Wn:
            return -v.w;
        default:
            return zero_v<T>;
        }
    }

 ////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    T   DimMapper::extract(const Size1<T>&v, Ax ax, T z)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        default:
            return z;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Size2<T>&v, Ax ax, T z)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        default:
            return z;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Size3<T>&v, Ax ax, T z)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        case Ax::Zp:
            return v.z;
        case Ax::Zn:
            return -v.z;
        default:
            return z;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Size4<T>&v, Ax ax, T z)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        case Ax::Zp:
            return v.z;
        case Ax::Zn:
            return -v.z;
        case Ax::Wp:
            return v.w;
        case Ax::Wn:
            return -v.w;
        default:
            return z;
        }
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    T   DimMapper::extract(const Vector1<T>&v, Ax ax, T z)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        default:
            return z;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Vector2<T>&v, Ax ax, T z)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        default:
            return z;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Vector3<T>&v, Ax ax, T z)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        case Ax::Zp:
            return v.z;
        case Ax::Zn:
            return -v.z;
        default:
            return z;
        }
    }
    
    template <typename T>
    T   DimMapper::extract(const Vector4<T>&v, Ax ax, T z)
    {
        switch(ax){
        case Ax::Xp:
            return v.x;
        case Ax::Xn:
            return -v.x;
        case Ax::Yp:
            return v.y;
        case Ax::Yn:
            return -v.y;
        case Ax::Zp:
            return v.z;
        case Ax::Zn:
            return -v.z;
        case Ax::Wp:
            return v.w;
        case Ax::Wn:
            return -v.w;
        default:
            return z;
        }
    }

////////////////////////////////////////////////////////////////////////////////

    template <typename T> Size1<T>   DimMapper::map1(const Size1<T>&v) const
    {
        return Size1<T>(extract(v, axis.xx));
    }
    
    template <typename T> Size1<T>   DimMapper::map1(const Size2<T>&v) const
    {
        return Size1<T>(extract(v, axis.xy));
    }
    
    template <typename T> Size1<T>   DimMapper::map1(const Size3<T>&v) const
    {
        return Size1<T>(extract(v, axis.xz));
    }
    
    template <typename T> Size1<T>   DimMapper::map1(const Size4<T>&v) const
    {
        return Size1<T>(extract(v, axis.xw));
    }
    
    template <typename T> Size2<T>   DimMapper::map2(const Size1<T>&v) const
    {
        return Size2<T>(extract(v, axis.xx), extract(v, axis.yx));
    }
    
    template <typename T> Size2<T>   DimMapper::map2(const Size2<T>&v) const
    {
        return Size2<T>(extract(v, axis.xy), extract(v, axis.yy));
    }
    
    template <typename T> Size2<T>   DimMapper::map2(const Size3<T>&v) const
    {
        return Size2<T>(extract(v, axis.xz), extract(v, axis.yz));
    }
    
    template <typename T> Size2<T>   DimMapper::map2(const Size4<T>&v) const
    {
        return Size2<T>(extract(v, axis.xw), extract(v, axis.yw));
    }

    template <typename T> Size3<T>   DimMapper::map3(const Size1<T>&v) const
    {
        return Size3<T>(extract(v, axis.xx), extract(v, axis.yx), extract(v, axis.zx));
    }
    
    template <typename T> Size3<T>   DimMapper::map3(const Size2<T>&v) const
    {
        return Size3<T>(extract(v, axis.xy), extract(v, axis.yy), extract(v, axis.zy));
    }
    
    template <typename T> Size3<T>   DimMapper::map3(const Size3<T>&v) const
    {
        return Size3<T>(extract(v, axis.xz), extract(v, axis.yz), extract(v, axis.zz));
    }
    
    template <typename T> Size3<T>   DimMapper::map3(const Size4<T>&v) const
    {
        return Size3<T>(extract(v, axis.xw), extract(v, axis.yw), extract(v, axis.zw));
    }

    template <typename T> Size4<T>   DimMapper::map4(const Size1<T>&v) const
    {
        return Size4<T>(extract(v, axis.xx), extract(v, axis.yx), extract(v, axis.zx), extract(v, axis.wx));
    }
    
    template <typename T> Size4<T>   DimMapper::map4(const Size2<T>&v) const
    {
        return Size4<T>(extract(v, axis.xy), extract(v, axis.yy), extract(v, axis.zy), extract(v, axis.wy));
    }
    
    template <typename T> Size4<T>   DimMapper::map4(const Size3<T>&v) const
    {
        return Size4<T>(extract(v, axis.xz), extract(v, axis.yz), extract(v, axis.zz), extract(v, axis.wz));
    }
    
    template <typename T> Size4<T>   DimMapper::map4(const Size4<T>&v) const
    {
        return Size4<T>(extract(v, axis.xw), extract(v, axis.yw), extract(v, axis.zw), extract(v, axis.ww));
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <typename T> Size1<T> DimMapper::map1(const Size1<T>&v, const Size1<T>&b) const
    {
        return Size1<T>(extract(v, axis.xx, b.x));
    }
    
    template <typename T> Size1<T> DimMapper::map1(const Size2<T>&v, const Size1<T>&b) const
    {
        return Size1<T>(extract(v, axis.xy, b.x));
    }
    
    template <typename T> Size1<T> DimMapper::map1(const Size3<T>&v, const Size1<T>&b) const
    {
        return Size1<T>(extract(v, axis.xz, b.x));
    }
    
    template <typename T> Size1<T> DimMapper::map1(const Size4<T>&v, const Size1<T>&b) const
    {
        return Size1<T>(extract(v, axis.xw, b.x));
    }

    template <typename T> Size2<T> DimMapper::map2(const Size1<T>&v, const Size2<T>&b) const
    {
        return Size2<T>(extract(v, axis.xx, b.x), extract(v, axis.yx, b.y));
    }
    
    template <typename T> Size2<T> DimMapper::map2(const Size2<T>&v, const Size2<T>&b) const
    {
        return Size2<T>(extract(v, axis.xy, b.x), extract(v, axis.yy, b.y));
    }
    
    template <typename T> Size2<T> DimMapper::map2(const Size3<T>&v, const Size2<T>&b) const
    {
        return Size2<T>(extract(v, axis.xz, b.x), extract(v, axis.yz, b.y));
    }
    
    template <typename T> Size2<T> DimMapper::map2(const Size4<T>&v, const Size2<T>&b) const
    {
        return Size2<T>(extract(v, axis.xw, b.x), extract(v, axis.yw, b.y));
    }

    template <typename T> Size3<T> DimMapper::map3(const Size1<T>&v, const Size3<T>&b) const
    {
        return Size3<T>(extract(v, axis.xx, b.x), extract(v, axis.yx, b.y), extract(v, axis.zx, b.z));
    }
    
    template <typename T> Size3<T> DimMapper::map3(const Size2<T>&v, const Size3<T>&b) const
    {
        return Size3<T>(extract(v, axis.xy, b.x), extract(v, axis.yy, b.y), extract(v, axis.zy, b.z));
    }
    
    template <typename T> Size3<T> DimMapper::map3(const Size3<T>&v, const Size3<T>&b) const
    {
        return Size3<T>(extract(v, axis.xz, b.x), extract(v, axis.yz, b.y), extract(v, axis.zz, b.z));
    }
    
    template <typename T> Size3<T> DimMapper::map3(const Size4<T>&v, const Size3<T>&b) const
    {
        return Size3<T>(extract(v, axis.xw, b.x), extract(v, axis.yw, b.y), extract(v, axis.zw, b.z));
    }

    template <typename T> Size4<T> DimMapper::map4(const Size1<T>&v, const Size4<T>&b) const
    {
        return Size4<T>(extract(v, axis.xx, b.x), extract(v, axis.yx, b.y), extract(v, axis.zx, b.z), extract(v, axis.wx, b.w));
    }
    
    template <typename T> Size4<T> DimMapper::map4(const Size2<T>&v, const Size4<T>&b) const
    {
        return Size4<T>(extract(v, axis.xy, b.x), extract(v, axis.yy, b.y), extract(v, axis.zy, b.z), extract(v, axis.wy, b.w));
    }
    
    template <typename T> Size4<T> DimMapper::map4(const Size3<T>&v, const Size4<T>&b) const
    {
        return Size4<T>(extract(v, axis.xz, b.x), extract(v, axis.yz, b.y), extract(v, axis.zz, b.z), extract(v, axis.wz, b.w));
    }
    
    template <typename T> Size4<T> DimMapper::map4(const Size4<T>&v, const Size4<T>&b) const
    {
        return Size4<T>(extract(v, axis.xw, b.x), extract(v, axis.yw, b.y), extract(v, axis.zw, b.z), extract(v, axis.ww, b.w));
    }

////////////////////////////////////////////////////////////////////////////////

    template <typename T> Vector1<T>   DimMapper::map1(const Vector1<T>&v) const
    {
        return Vector1<T>(extract(v, axis.xx));
    }
    
    template <typename T> Vector1<T>   DimMapper::map1(const Vector2<T>&v) const
    {
        return Vector1<T>(extract(v, axis.xy));
    }
    
    template <typename T> Vector1<T>   DimMapper::map1(const Vector3<T>&v) const
    {
        return Vector1<T>(extract(v, axis.xz));
    }
    
    template <typename T> Vector1<T>   DimMapper::map1(const Vector4<T>&v) const
    {
        return Vector1<T>(extract(v, axis.xw));
    }
    
    template <typename T> Vector2<T>   DimMapper::map2(const Vector1<T>&v) const
    {
        return Vector2<T>(extract(v, axis.xx), extract(v, axis.yx));
    }
    
    template <typename T> Vector2<T>   DimMapper::map2(const Vector2<T>&v) const
    {
        return Vector2<T>(extract(v, axis.xy), extract(v, axis.yy));
    }
    
    template <typename T> Vector2<T>   DimMapper::map2(const Vector3<T>&v) const
    {
        return Vector2<T>(extract(v, axis.xz), extract(v, axis.yz));
    }
    
    template <typename T> Vector2<T>   DimMapper::map2(const Vector4<T>&v) const
    {
        return Vector2<T>(extract(v, axis.xw), extract(v, axis.yw));
    }

    template <typename T> Vector3<T>   DimMapper::map3(const Vector1<T>&v) const
    {
        return Vector3<T>(extract(v, axis.xx), extract(v, axis.yx), extract(v, axis.zx));
    }
    
    template <typename T> Vector3<T>   DimMapper::map3(const Vector2<T>&v) const
    {
        return Vector3<T>(extract(v, axis.xy), extract(v, axis.yy), extract(v, axis.zy));
    }
    
    template <typename T> Vector3<T>   DimMapper::map3(const Vector3<T>&v) const
    {
        return Vector3<T>(extract(v, axis.xz), extract(v, axis.yz), extract(v, axis.zz));
    }
    
    template <typename T> Vector3<T>   DimMapper::map3(const Vector4<T>&v) const
    {
        return Vector3<T>(extract(v, axis.xw), extract(v, axis.yw), extract(v, axis.zw));
    }

    template <typename T> Vector4<T>   DimMapper::map4(const Vector1<T>&v) const
    {
        return Vector4<T>(extract(v, axis.xx), extract(v, axis.yx), extract(v, axis.zx), extract(v, axis.wx));
    }
    
    template <typename T> Vector4<T>   DimMapper::map4(const Vector2<T>&v) const
    {
        return Vector4<T>(extract(v, axis.xy), extract(v, axis.yy), extract(v, axis.zy), extract(v, axis.wy));
    }
    
    template <typename T> Vector4<T>   DimMapper::map4(const Vector3<T>&v) const
    {
        return Vector4<T>(extract(v, axis.xz), extract(v, axis.yz), extract(v, axis.zz), extract(v, axis.wz));
    }
    
    template <typename T> Vector4<T>   DimMapper::map4(const Vector4<T>&v) const
    {
        return Vector4<T>(extract(v, axis.xw), extract(v, axis.yw), extract(v, axis.zw), extract(v, axis.ww));
    }

////////////////////////////////////////////////////////////////////////////////

    template <typename T> Vector1<T> DimMapper::map1(const Vector1<T>&v, const Vector1<T>&b) const
    {
        return Vector1<T>(extract(v, axis.xx, b.x));
    }
    
    template <typename T> Vector1<T> DimMapper::map1(const Vector2<T>&v, const Vector1<T>&b) const
    {
        return Vector1<T>(extract(v, axis.xy, b.x));
    }
    
    template <typename T> Vector1<T> DimMapper::map1(const Vector3<T>&v, const Vector1<T>&b) const
    {
        return Vector1<T>(extract(v, axis.xz, b.x));
    }
    
    template <typename T> Vector1<T> DimMapper::map1(const Vector4<T>&v, const Vector1<T>&b) const
    {
        return Vector1<T>(extract(v, axis.xw, b.x));
    }

    template <typename T> Vector2<T> DimMapper::map2(const Vector1<T>&v, const Vector2<T>&b) const
    {
        return Vector2<T>(extract(v, axis.xx, b.x), extract(v, axis.yx, b.y));
    }
    
    template <typename T> Vector2<T> DimMapper::map2(const Vector2<T>&v, const Vector2<T>&b) const
    {
        return Vector2<T>(extract(v, axis.xy, b.x), extract(v, axis.yy, b.y));
    }
    
    template <typename T> Vector2<T> DimMapper::map2(const Vector3<T>&v, const Vector2<T>&b) const
    {
        return Vector2<T>(extract(v, axis.xz, b.x), extract(v, axis.yz, b.y));
    }
    
    template <typename T> Vector2<T> DimMapper::map2(const Vector4<T>&v, const Vector2<T>&b) const
    {
        return Vector2<T>(extract(v, axis.xw, b.x), extract(v, axis.yw, b.y));
    }

    template <typename T> Vector3<T> DimMapper::map3(const Vector1<T>&v, const Vector3<T>&b) const
    {
        return Vector3<T>(extract(v, axis.xx, b.x), extract(v, axis.yx, b.y), extract(v, axis.zx, b.z));
    }
    
    template <typename T> Vector3<T> DimMapper::map3(const Vector2<T>&v, const Vector3<T>&b) const
    {
        return Vector3<T>(extract(v, axis.xy, b.x), extract(v, axis.yy, b.y), extract(v, axis.zy, b.z));
    }
    
    template <typename T> Vector3<T> DimMapper::map3(const Vector3<T>&v, const Vector3<T>&b) const
    {
        return Vector3<T>(extract(v, axis.xz, b.x), extract(v, axis.yz, b.y), extract(v, axis.zz, b.z));
    }
    
    template <typename T> Vector3<T> DimMapper::map3(const Vector4<T>&v, const Vector3<T>&b) const
    {
        return Vector3<T>(extract(v, axis.xw, b.x), extract(v, axis.yw, b.y), extract(v, axis.zw, b.z));
    }

    template <typename T> Vector4<T> DimMapper::map4(const Vector1<T>&v, const Vector4<T>&b) const
    {
        return Vector4<T>(extract(v, axis.xx, b.x), extract(v, axis.yx, b.y), extract(v, axis.zx, b.z), extract(v, axis.wx, b.w));
    }
    
    template <typename T> Vector4<T> DimMapper::map4(const Vector2<T>&v, const Vector4<T>&b) const
    {
        return Vector4<T>(extract(v, axis.xy, b.x), extract(v, axis.yy, b.y), extract(v, axis.zy, b.z), extract(v, axis.wy, b.w));
    }
    
    template <typename T> Vector4<T> DimMapper::map4(const Vector3<T>&v, const Vector4<T>&b) const
    {
        return Vector4<T>(extract(v, axis.xz, b.x), extract(v, axis.yz, b.y), extract(v, axis.zz, b.z), extract(v, axis.wz, b.w));
    }
    
    template <typename T> Vector4<T> DimMapper::map4(const Vector4<T>&v, const Vector4<T>&b) const
    {
        return Vector4<T>(extract(v, axis.xw, b.x), extract(v, axis.yw, b.y), extract(v, axis.zw, b.z), extract(v, axis.ww, b.w));
    }

////////////////////////////////////////////////////////////////////////////////

}
