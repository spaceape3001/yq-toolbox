////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFTensor.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFTensor)

namespace {
    void    reg_ECEFTensor()
    {
        auto w = writer<ECEFTensor>();
        w.description("ECEF Tensor");
        w.property(szXX, &ECEFTensor::xx);
        w.property(szXY, &ECEFTensor::xy);
        w.property(szXZ, &ECEFTensor::xz);
        w.property(szYX, &ECEFTensor::yx);
        w.property(szYY, &ECEFTensor::yy);
        w.property(szYZ, &ECEFTensor::yz);
        w.property(szZX, &ECEFTensor::zx);
        w.property(szZY, &ECEFTensor::zy);
        w.property(szZZ, &ECEFTensor::zz);
    }
    
    YQ_INVOKE(reg_ECEFTensor();)
}
