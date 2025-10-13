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
    struct TNEDDomain;

    using TNEDAcceleration          = DVector<TNEDDomain, unit::MeterPerSecond²3D>;
    using TNEDAngularVelocity       = DVector<TNEDDomain, unit::RadianPerSecond3D>;
    using TNEDAngularAcceleration   = DVector<TNEDDomain, unit::RadianPerSecond²3D>;
    using TNEDDisplacement          = DVector<TNEDDomain, unit::Meter3D>;
    using TNEDForce                 = DVector<TNEDDomain, unit::Newton3D>;
    using TNEDOrientation           = DOrientation<TNEDDomain, Quaternion3D>;
    using TNEDPosition              = DPosition<TNEDDomain, unit::Meter3D>;
    using TNEDRotation              = DVector<TNEDDomain, unit::Radian3D>;
    using TNEDTensor                = DTensor<TNEDDomain, Tensor33D>;
    using TNEDVector                = DVector<TNEDDomain, Vector3D>;
    using TNEDVelocity              = DVector<TNEDDomain, unit::MeterPerSecond3D>;
}
