////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDTensor.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDTensor)

namespace {
    void    reg_bnsdTensor()
    {
        auto w = writer<BNSDTensor>();
        w.description("BNSD Tensor");
        w.property(szXX, &BNSDTensor::xx);
        w.property(szXY, &BNSDTensor::xy);
        w.property(szXZ, &BNSDTensor::xz);
        w.property(szYX, &BNSDTensor::yx);
        w.property(szYY, &BNSDTensor::yy);
        w.property(szYZ, &BNSDTensor::yz);
        w.property(szZX, &BNSDTensor::zx);
        w.property(szZY, &BNSDTensor::zy);
        w.property(szZZ, &BNSDTensor::zz);
    }
    
    YQ_INVOKE(reg_bnsdTensor();)
}
