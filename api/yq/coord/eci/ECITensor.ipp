////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECITensor.hpp"

YQ_TYPE_IMPLEMENT(yq::ECITensor)

namespace {
    void    reg_ECITensor()
    {
        auto w = writer<ECITensor>();
        w.description("ECI Tensor");
        w.property(szXX, &ECITensor::xx);
        w.property(szXY, &ECITensor::xy);
        w.property(szXZ, &ECITensor::xz);
        w.property(szYX, &ECITensor::yx);
        w.property(szYY, &ECITensor::yy);
        w.property(szYZ, &ECITensor::yz);
        w.property(szZX, &ECITensor::zx);
        w.property(szZY, &ECITensor::zy);
        w.property(szZZ, &ECITensor::zz);
    }
    
    YQ_INVOKE(reg_ECITensor();)
}
