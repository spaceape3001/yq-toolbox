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
    struct ECEFDomain;

    using ECEFAcceleration          = DVector<ECEFDomain, unit::MeterPerSecond²3D>;
    using ECEFAngularVelocity       = DVector<ECEFDomain, unit::RadianPerSecond3D>;
    using ECEFAngularAcceleration   = DVector<ECEFDomain, unit::RadianPerSecond²3D>;
    using ECEFDisplacement          = DVector<ECEFDomain, unit::Meter3D>;
    using ECEFForce                 = DVector<ECEFDomain, unit::Newton3D>;
    using ECEFOrientation           = DOrientation<ECEFDomain, Quaternion3D>;
    using ECEFPosition              = DPosition<ECEFDomain, unit::Meter3D>;
    using ECEFRotation              = DVector<ECEFDomain, unit::Radian3D>;
    using ECEFTensor                = DTensor<ECEFDomain, Tensor33D>;
    using ECEFVector                = DVector<ECEFDomain, Vector3D>;
    using ECEFVelocity              = DVector<ECEFDomain, unit::MeterPerSecond3D>;
}
