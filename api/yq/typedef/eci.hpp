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
    struct ECIDomain;

    using ECIAcceleration          = DVector<ECIDomain, unit::MeterPerSecond²3D>;
    using ECIAngularVelocity       = DVector<ECIDomain, unit::RadianPerSecond3D>;
    using ECIAngularAcceleration   = DVector<ECIDomain, unit::RadianPerSecond²3D>;
    using ECIDisplacement          = DVector<ECIDomain, unit::Meter3D>;
    using ECIForce                 = DVector<ECIDomain, unit::Newton3D>;
    using ECIOrientation           = DOrientation<ECIDomain, Quaternion3D>;
    using ECIPosition              = DPosition<ECIDomain, unit::Meter3D>;
    using ECIRotation              = DVector<ECIDomain, unit::Radian3D>;
    using ECITensor                = DTensor<ECIDomain, Tensor33D>;
    using ECIVector                = DVector<ECIDomain, Vector3D>;
    using ECIVelocity              = DVector<ECIDomain, unit::MeterPerSecond3D>;
}
