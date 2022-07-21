////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/Quaternion3.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor44.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief Simple space reference frame
    
        The simple space is one with simple orientation & scaling relative to its parent's space
    */
    struct SimpleSpace {
        //! Orientation of this space relative to its parent space, centered around the position
        Quaternion3D    orientation = { 1., 0., 0., 0. };
        //! "Origin" of this space, in parent's spatial coordinates
        Vector3D        position    = { 0., 0., 0. };
        //! Scale of this space relative to parent's spatial coordinates
        Vector3D        scale       = { 1., 1., 1. };
        
        //! Calculates the local to parent transform
        Tensor44D       local2parent() const;

        //! Calculates the parent to local transform
        Tensor44D       parent2local() const;
    };
    
}
