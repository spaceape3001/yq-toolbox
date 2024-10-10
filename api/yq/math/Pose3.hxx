////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/math/Pose3.hpp>

/* 
    This is the template IMPLEMENTATION of the pose3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {

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
}
