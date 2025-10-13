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
    struct BNSDDomain;

    using BNSDAcceleration          = DVector<BNSDDomain, unit::MeterPerSecond²3D>;
    using BNSDAngularVelocity       = DVector<BNSDDomain, unit::RadianPerSecond3D>;
    using BNSDAngularAcceleration   = DVector<BNSDDomain, unit::RadianPerSecond²3D>;
    using BNSDDisplacement          = DVector<BNSDDomain, unit::Meter3D>;
    using BNSDForce                 = DVector<BNSDDomain, unit::Newton3D>;
    using BNSDOrientation           = DOrientation<BNSDDomain, Quaternion3D>;
    using BNSDPosition              = DPosition<BNSDDomain, unit::Meter3D>;
    using BNSDRotation              = DVector<BNSDDomain, unit::Radian3D>;
    using BNSDTensor                = DTensor<BNSDDomain, Tensor33D>;
    using BNSDVector                = DVector<BNSDDomain, Vector3D>;
    using BNSDVelocity              = DVector<BNSDDomain, unit::MeterPerSecond3D>;
}
