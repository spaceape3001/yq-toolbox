////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/typedef/uv.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_zero.hpp>

namespace yq {
    /*! \brief UV coordinate type
        \tparam T   data type
    */
    template <typename T>
    struct UV {
    
        //! Data in u
        T   u;
        
        //! Data in v
        T   v;

        //! Default constructor
        constexpr UV() noexcept = default;
        
        //! Componentwise constructor
        constexpr UV(const T& _u, const T& _v) noexcept : u(_u), v(_v) {}
        
        //! Construct with all components to same value
        constexpr UV(all_k, const T& _val) noexcept : u(_val), v(_val) {}
        
        consteval UV(nan_k) noexcept : UV(ALL, nan_v<T>) {}

        constexpr UV(u_k, T _val) noexcept : u(_val), v(zero_v<T>) {}
        
        consteval UV(u_k) noexcept : UV(U, one_v<T>) {}
        
        constexpr UV(v_k, T _val) noexcept : u(zero_v<T>), v(_val) {}

        consteval UV(v_k) noexcept : UV(V, one_v<T>) {}

        consteval UV(zero_k) noexcept : UV(zero_v<T>, zero_v<T>) {}
        
        //! Defaulted equality operator
        constexpr bool operator==(const UV&) const noexcept = default;
    };
}

YQ_TYPE_DECLARE(yq::UV2D)
YQ_TYPE_DECLARE(yq::UV2F)
YQ_TYPE_DECLARE(yq::UV2U)
YQ_TYPE_DECLARE(yq::UV2I)


