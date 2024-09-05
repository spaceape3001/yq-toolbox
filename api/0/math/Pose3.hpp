////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POSE3_HPP 1


#include <yq-toolbox/vector/Quaternion3.hpp>
#include <yq-toolbox/vector/Vector3.hpp>
#include <yq-toolbox/vector/Tensor33.hpp>
#include <yq-toolbox/vector/Tensor44.hpp>
#include <yq-toolbox/unit/MKS.hpp>
#include <yq-toolbox/unit/SCALED.hpp>

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

    #ifdef YQ_USE_GLM
    template <typename T>
    requires std::is_floating_point_v<T>
    auto    view_matrix(const Pose3<T>& pose)
    {
        using fp_t = ieee754_t<T>;
        Tensor33<fp_t> eq  = tensor(pose.orientation);
        return glm::mat<4,4,T,glm::defaultp>{
            eq.xx, eq.xy, eq.xz, pose.position.x,
            eq.yx, eq.yy, eq.yz, pose.position.y,
            eq.zx, eq.zy, eq.zz, pose.position.z,
            0., 0., 0., 1.
        };
    }
    #endif

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS
}

YQ_TYPE_DECLARE(yq::Pose3F)
YQ_TYPE_DECLARE(yq::Pose3D)


