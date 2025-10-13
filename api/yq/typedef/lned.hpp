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
    struct LNEDDomain;

    using LNEDAcceleration          = DVector<LNEDDomain, unit::MeterPerSecond²3D>;
    using LNEDAngularVelocity       = DVector<LNEDDomain, unit::RadianPerSecond3D>;
    using LNEDAngularAcceleration   = DVector<LNEDDomain, unit::RadianPerSecond²3D>;
    using LNEDDisplacement          = DVector<LNEDDomain, unit::Meter3D>;
    using LNEDForce                 = DVector<LNEDDomain, unit::Newton3D>;
    using LNEDOrientation           = DOrientation<LNEDDomain, Quaternion3D>;
    using LNEDPosition              = DPosition<LNEDDomain, unit::Meter3D>;
    using LNEDRotation              = DVector<LNEDDomain, unit::Radian3D>;
    using LNEDTensor                = DTensor<LNEDDomain, Tensor33D>;
    using LNEDVector                = DVector<LNEDDomain, Vector3D>;
    using LNEDVelocity              = DVector<LNEDDomain, unit::MeterPerSecond3D>;
}
