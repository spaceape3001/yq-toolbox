////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/typedef/uvw.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_zero.hpp>

namespace yq {

    /*! \brief UVW data structure
    
        Used to bind together uvw triple binding of data to the relevant axes
    */
    template <typename T>
    struct UVW {
    
        //! Data for the U-axis
        T   u;
        
        //! Data for the V-axis
        T   v;
        
        //! Data for the W-axis
        T   w;
        
        //! Default constructor
        constexpr UVW() noexcept = default;
        
        //! Component-wise constructor
        constexpr UVW(const T& _u, const T& _v, const T& _w) noexcept : u(_u), v(_v), w(_w) {}
        
        //! Constructs all data to same value
        constexpr UVW(all_k, const T& _val) noexcept : u(_val), v(_val), w(_val) {}
        
        consteval UVW(nan_k) noexcept : UVW(ALL, nan_v<T>) {}

        constexpr UVW(u_k, T _val) noexcept : UVW(_val, zero_v<T>, zero_v<T>) {}
        
        consteval UVW(u_k) noexcept : UVW(U, one_v<T>) {}
        
        constexpr UVW(v_k, T _val) noexcept : UVW(zero_v<T>, v(_val), zero_v<T>) {}

        consteval UVW(v_k) noexcept : UVW(V, one_v<T>) {}

        constexpr UVW(w_k, T _val) noexcept : UVW(zero_v<T>, zero_v<T>, v(_val)) {}

        consteval UVW(w_k) noexcept : UVW(V, one_v<T>) {}

        consteval UVW(zero_k) noexcept : UVW(zero_v<T>, zero_v<T>, zero_v<T>) {}

        //! Defaulted equality operator
        constexpr bool operator==(const UVW&) const noexcept = default;
    };
}

YQ_TYPE_DECLARE(yq::UVW3D)
YQ_TYPE_DECLARE(yq::UVW3F)
YQ_TYPE_DECLARE(yq::UVW3U)
YQ_TYPE_DECLARE(yq::UVW3I)


