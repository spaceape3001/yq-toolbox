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
    struct LENUDomain;

    using LENUAcceleration          = DVector<LENUDomain, unit::MeterPerSecond²3D>;
    using LENUAngularVelocity       = DVector<LENUDomain, unit::RadianPerSecond3D>;
    using LENUAngularAcceleration   = DVector<LENUDomain, unit::RadianPerSecond²3D>;
    using LENUDisplacement          = DVector<LENUDomain, unit::Meter3D>;
    using LENUForce                 = DVector<LENUDomain, unit::Newton3D>;
    using LENUOrientation           = DOrientation<LENUDomain, Quaternion3D>;
    using LENUPosition              = DPosition<LENUDomain, unit::Meter3D>;
    using LENURotation              = DVector<LENUDomain, unit::Radian3D>;
    using LENUTensor                = DTensor<LENUDomain, Tensor33D>;
    using LENUVector                = DVector<LENUDomain, Vector3D>;
    using LENUVelocity              = DVector<LENUDomain, unit::MeterPerSecond3D>;
}
