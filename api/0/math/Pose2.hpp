////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POSE2_HPP 1


#include <yq-toolbox/vector/Vector2.hpp>
#include <yq-toolbox/tensor/Tensor22.hpp>
#include <yq-toolbox/unit/MKS.hpp>
#include <yq-toolbox/unit/SCALED.hpp>

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
//  PROJECTIONS


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS
}

YQ_TYPE_DECLARE(yq::Pose2F)
YQ_TYPE_DECLARE(yq::Pose2D)


