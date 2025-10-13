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
    struct TENUDomain;

    using TENUAcceleration          = DVector<TENUDomain, unit::MeterPerSecond²3D>;
    using TENUAngularVelocity       = DVector<TENUDomain, unit::RadianPerSecond3D>;
    using TENUAngularAcceleration   = DVector<TENUDomain, unit::RadianPerSecond²3D>;
    using TENUDisplacement          = DVector<TENUDomain, unit::Meter3D>;
    using TENUForce                 = DVector<TENUDomain, unit::Newton3D>;
    using TENUOrientation           = DOrientation<TENUDomain, Quaternion3D>;
    using TENUPosition              = DPosition<TENUDomain, unit::Meter3D>;
    using TENURotation              = DVector<TENUDomain, unit::Radian3D>;
    using TENUTensor                = DTensor<TENUDomain, Tensor33D>;
    using TENUVector                = DVector<TENUDomain, Vector3D>;
    using TENUVelocity              = DVector<TENUDomain, unit::MeterPerSecond3D>;
}
