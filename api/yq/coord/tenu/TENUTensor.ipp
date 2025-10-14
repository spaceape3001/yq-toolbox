////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENUTensor.hpp"

YQ_TYPE_IMPLEMENT(yq::TENUTensor)

namespace {
    void    reg_TENUTensor()
    {
        auto w = writer<TENUTensor>();
        w.description("TENU Tensor");
        w.property(szXX, &TENUTensor::xx);
        w.property(szXY, &TENUTensor::xy);
        w.property(szXZ, &TENUTensor::xz);
        w.property(szYX, &TENUTensor::yx);
        w.property(szYY, &TENUTensor::yy);
        w.property(szYZ, &TENUTensor::yz);
        w.property(szZX, &TENUTensor::zx);
        w.property(szZY, &TENUTensor::zy);
        w.property(szZZ, &TENUTensor::zz);
    }
    
    YQ_INVOKE(reg_TENUTensor();)
}
