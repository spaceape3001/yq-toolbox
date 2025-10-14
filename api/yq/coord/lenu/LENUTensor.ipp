////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LENUTensor.hpp"

YQ_TYPE_IMPLEMENT(yq::LENUTensor)

namespace {
    void    reg_LENUTensor()
    {
        auto w = writer<LENUTensor>();
        w.description("LENU Tensor");
        w.property(szXX, &LENUTensor::xx);
        w.property(szXY, &LENUTensor::xy);
        w.property(szXZ, &LENUTensor::xz);
        w.property(szYX, &LENUTensor::yx);
        w.property(szYY, &LENUTensor::yy);
        w.property(szYZ, &LENUTensor::yz);
        w.property(szZX, &LENUTensor::zx);
        w.property(szZY, &LENUTensor::zy);
        w.property(szZZ, &LENUTensor::zz);
    }
    
    YQ_INVOKE(reg_LENUTensor();)
}
