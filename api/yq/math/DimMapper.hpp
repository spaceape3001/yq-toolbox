////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/math/Ax.hpp>
#include <yq/tensor/Tensor44.hpp>

#include <yq/typedef/axbox1.hpp>
#include <yq/typedef/axbox2.hpp>
#include <yq/typedef/axbox3.hpp>
#include <yq/typedef/axbox4.hpp>

#include <yq/typedef/size1.hpp>
#include <yq/typedef/size2.hpp>
#include <yq/typedef/size3.hpp>
#include <yq/typedef/size4.hpp>

#include <yq/typedef/vector1.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/typedef/vector3.hpp>
#include <yq/typedef/vector4.hpp>

namespace yq {
    /*! \brief Utility for remapping dimensions
    
        \note This is intended to be fast, so primary axis only, no funny business
    */
    struct DimMapper {
    
        //! Maps domain to local (symmetric), so the transpose is the reverse 
        //! Thus, extract/extract should be considered 1:1
        //! \note None/bad will be interpretted as 0.0
        //! \note It'll be considered an ERROR to doubly list an axis in a column (none excluded)
        Tensor44<Ax>        axis = {
            // 1D      2D        3D         4D  (inbound sized-object)
            Ax::X,    Ax::X,    Ax::X,    Ax::X,    //< X/X dimension
            Ax::None, Ax::Y,    Ax::Y,    Ax::Y,    //< Y/Y dimension
            Ax::None, Ax::None, Ax::Z,    Ax::Z,    //< Z/Z dimension
            Ax::None, Ax::None, Ax::None, Ax::W,    //< W/W dimension
        };
        
        DimMapper();
        ~DimMapper();

        ///////////////////////////////////////////////////////////////////////

        template <typename T> Size1<T> map1(const Size1<T>&) const;
        template <typename T> Size1<T> map1(const Size2<T>&) const;
        template <typename T> Size1<T> map1(const Size3<T>&) const;
        template <typename T> Size1<T> map1(const Size4<T>&) const;
        
        template <typename T> Size2<T> map2(const Size1<T>&) const;
        template <typename T> Size2<T> map2(const Size2<T>&) const;
        template <typename T> Size2<T> map2(const Size3<T>&) const;
        template <typename T> Size2<T> map2(const Size4<T>&) const;

        template <typename T> Size3<T> map3(const Size1<T>&) const;
        template <typename T> Size3<T> map3(const Size2<T>&) const;
        template <typename T> Size3<T> map3(const Size3<T>&) const;
        template <typename T> Size3<T> map3(const Size4<T>&) const;

        template <typename T> Size4<T> map4(const Size1<T>&) const;
        template <typename T> Size4<T> map4(const Size2<T>&) const;
        template <typename T> Size4<T> map4(const Size3<T>&) const;
        template <typename T> Size4<T> map4(const Size4<T>&) const;

        ///////////////////////////////////////////////////////////////////////

        template <typename T> Size1<T> map1(const Size1<T>&, const Size1<T>&) const;
        template <typename T> Size1<T> map1(const Size2<T>&, const Size1<T>&) const;
        template <typename T> Size1<T> map1(const Size3<T>&, const Size1<T>&) const;
        template <typename T> Size1<T> map1(const Size4<T>&, const Size1<T>&) const;

        template <typename T> Size2<T> map2(const Size1<T>&, const Size2<T>&) const;
        template <typename T> Size2<T> map2(const Size2<T>&, const Size2<T>&) const;
        template <typename T> Size2<T> map2(const Size3<T>&, const Size2<T>&) const;
        template <typename T> Size2<T> map2(const Size4<T>&, const Size2<T>&) const;

        template <typename T> Size3<T> map3(const Size1<T>&, const Size3<T>&) const;
        template <typename T> Size3<T> map3(const Size2<T>&, const Size3<T>&) const;
        template <typename T> Size3<T> map3(const Size3<T>&, const Size3<T>&) const;
        template <typename T> Size3<T> map3(const Size4<T>&, const Size3<T>&) const;

        template <typename T> Size4<T> map4(const Size1<T>&, const Size4<T>&) const;
        template <typename T> Size4<T> map4(const Size2<T>&, const Size4<T>&) const;
        template <typename T> Size4<T> map4(const Size3<T>&, const Size4<T>&) const;
        template <typename T> Size4<T> map4(const Size4<T>&, const Size4<T>&) const;

        ///////////////////////////////////////////////////////////////////////

        template <typename T> Vector1<T> map1(const Vector1<T>&) const;
        template <typename T> Vector1<T> map1(const Vector2<T>&) const;
        template <typename T> Vector1<T> map1(const Vector3<T>&) const;
        template <typename T> Vector1<T> map1(const Vector4<T>&) const;
        
        template <typename T> Vector2<T> map2(const Vector1<T>&) const;
        template <typename T> Vector2<T> map2(const Vector2<T>&) const;
        template <typename T> Vector2<T> map2(const Vector3<T>&) const;
        template <typename T> Vector2<T> map2(const Vector4<T>&) const;

        template <typename T> Vector3<T> map3(const Vector1<T>&) const;
        template <typename T> Vector3<T> map3(const Vector2<T>&) const;
        template <typename T> Vector3<T> map3(const Vector3<T>&) const;
        template <typename T> Vector3<T> map3(const Vector4<T>&) const;

        template <typename T> Vector4<T> map4(const Vector1<T>&) const;
        template <typename T> Vector4<T> map4(const Vector2<T>&) const;
        template <typename T> Vector4<T> map4(const Vector3<T>&) const;
        template <typename T> Vector4<T> map4(const Vector4<T>&) const;

        ///////////////////////////////////////////////////////////////////////

        template <typename T> Vector1<T> map1(const Vector1<T>&, const Vector1<T>&) const;
        template <typename T> Vector1<T> map1(const Vector2<T>&, const Vector1<T>&) const;
        template <typename T> Vector1<T> map1(const Vector3<T>&, const Vector1<T>&) const;
        template <typename T> Vector1<T> map1(const Vector4<T>&, const Vector1<T>&) const;

        template <typename T> Vector2<T> map2(const Vector1<T>&, const Vector2<T>&) const;
        template <typename T> Vector2<T> map2(const Vector2<T>&, const Vector2<T>&) const;
        template <typename T> Vector2<T> map2(const Vector3<T>&, const Vector2<T>&) const;
        template <typename T> Vector2<T> map2(const Vector4<T>&, const Vector2<T>&) const;

        template <typename T> Vector3<T> map3(const Vector1<T>&, const Vector3<T>&) const;
        template <typename T> Vector3<T> map3(const Vector2<T>&, const Vector3<T>&) const;
        template <typename T> Vector3<T> map3(const Vector3<T>&, const Vector3<T>&) const;
        template <typename T> Vector3<T> map3(const Vector4<T>&, const Vector3<T>&) const;

        template <typename T> Vector4<T> map4(const Vector1<T>&, const Vector4<T>&) const;
        template <typename T> Vector4<T> map4(const Vector2<T>&, const Vector4<T>&) const;
        template <typename T> Vector4<T> map4(const Vector3<T>&, const Vector4<T>&) const;
        template <typename T> Vector4<T> map4(const Vector4<T>&, const Vector4<T>&) const;

        ///////////////////////////////////////////////////////////////////////

        template <typename T>
        static T   extract(const Size1<T>&, Ax);

        template <typename T>
        static T   extract(const Size2<T>&, Ax);

        template <typename T>
        static T   extract(const Size3<T>&, Ax);

        template <typename T>
        static T   extract(const Size4<T>&, Ax);
        
        ///////////////////////////////////////////////////////////////////////

        template <typename T>
        static T   extract(const Vector1<T>&, Ax);

        template <typename T>
        static T   extract(const Vector2<T>&, Ax);

        template <typename T>
        static T   extract(const Vector3<T>&, Ax);

        template <typename T>
        static T   extract(const Vector4<T>&, Ax);

        ///////////////////////////////////////////////////////////////////////

        template <typename T>
        static T   extract(const Size1<T>&, Ax, T);

        template <typename T>
        static T   extract(const Size2<T>&, Ax, T);

        template <typename T>
        static T   extract(const Size3<T>&, Ax, T);

        template <typename T>
        static T   extract(const Size4<T>&, Ax, T);
        
        ///////////////////////////////////////////////////////////////////////

        template <typename T>
        static T   extract(const Vector1<T>&, Ax, T);

        template <typename T>
        static T   extract(const Vector2<T>&, Ax, T);

        template <typename T>
        static T   extract(const Vector3<T>&, Ax, T);

        template <typename T>
        static T   extract(const Vector4<T>&, Ax, T);
    };
}

