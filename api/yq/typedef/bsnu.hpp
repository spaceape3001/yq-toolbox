////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/dvalue.hpp>
#include <yq/typedef/quaternion3.hpp>
#include <yq/typedef/tensor33.hpp>
#include <yq/typedef/vector3.hpp>
#include <yq/unit/declare.hpp>

namespace yq {
    struct BSNUDomain;

    using BSNUAcceleration          = DVector<BSNUDomain, unit::MeterPerSecond²3D>;
    using BSNUAngularVelocity       = DVector<BSNUDomain, unit::RadianPerSecond3D>;
    using BSNUAngularAcceleration   = DVector<BSNUDomain, unit::RadianPerSecond²3D>;
    using BSNUDisplacement          = DVector<BSNUDomain, unit::Meter3D>;
    using BSNUForce                 = DVector<BSNUDomain, unit::Newton3D>;
    using BSNUOrientation           = DOrientation<BSNUDomain, Quaternion3D>;
    using BSNUPosition              = DPosition<BSNUDomain, unit::Meter3D>;
    using BSNURotation              = DVector<BSNUDomain, unit::Radian3D>;
    using BSNUTensor                = DTensor<BSNUDomain, Tensor33D>;
    using BSNUVector                = DVector<BSNUDomain, Vector3D>;
    using BSNUVelocity              = DVector<BSNUDomain, unit::MeterPerSecond3D>;
}
