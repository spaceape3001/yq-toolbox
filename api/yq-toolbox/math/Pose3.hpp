////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POSE3_HPP 1

#include <yq-toolbox/typedef/pose3.hpp>
#include <yq-toolbox/tensor/Tensor33.hpp>
#include <yq-toolbox/tensor/Tensor44.hpp>
#include <yq-toolbox/unit/MKS.hpp>
#include <yq-toolbox/unit/SCALED.hpp>
#include <yq-toolbox/vector/Quaternion3.hpp>
#include <yq-toolbox/vector/Vector3.hpp>

namespace yq {

    /*! \brief Position & orientation
    
        \sa https://en.wikipedia.org/wiki/Pose_(computer_vision)
    */
    template <typename T>
    struct Pose3 {
        using component_type    = T;
        using fp_t              = ieee754_t<T>;
        
        Quaternion3<T>          orientation;
        Vector3<T>              position;
        
        constexpr bool operator==(const Pose3&) const noexcept = default;
    };
    
    YQ_IEEE754_1(Pose3)

//  --------------------------------------------------------
//  COMPOSITION
    
    
//  --------------------------------------------------------
//  PROJECTIONS


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS
}

YQ_TYPE_DECLARE(yq::Pose3F)
YQ_TYPE_DECLARE(yq::Pose3D)


