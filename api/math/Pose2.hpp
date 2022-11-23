////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/Vector2.hpp>
#include <math/Tensor22.hpp>
#include <math/MKS.hpp>
#include <math/SCALED.hpp>

namespace yq {

    /*! \brief Position & orientation
    
        \sa https://en.wikipedia.org/wiki/Pose_(computer_vision)
    */
    template <typename T>
    struct Pose2 {
        using component_type    = T;
        using fp_t              = ieee754_t<T>;
        
        Vector2<T>              position;
        MKS<T,dim::Angle>       orientation;
        
        constexpr bool operator==(const Pose2&) const noexcept = default;
    };
    
    YQ_IEEE754_1(Pose2)

//  --------------------------------------------------------
//  COMPOSITION
    
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    template <typename T>
    constexpr bool is_finite(const Pose2<T>& v)
    {
        return is_finite(v.position) && is_finite(v.orientation);
    }

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS
}

YQ_TYPE_DECLARE(yq::Pose2F)
YQ_TYPE_DECLARE(yq::Pose2D)


