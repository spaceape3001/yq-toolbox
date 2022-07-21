////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/Quaternion3.hpp>
#include <math/Vector3.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor44.hpp>
#include <math/MKS.hpp>
#include <math/SCALED.hpp>

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
    

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS
}

YQ_TYPE_DECLARE(yq::Pose3F)
YQ_TYPE_DECLARE(yq::Pose3D)


