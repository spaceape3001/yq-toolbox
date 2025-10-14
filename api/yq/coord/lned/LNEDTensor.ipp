////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDTensor.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDTensor)

namespace {
    void    reg_LNEDTensor()
    {
        auto w = writer<LNEDTensor>();
        w.description("LNED Tensor");
        w.property(szXX, &LNEDTensor::xx);
        w.property(szXY, &LNEDTensor::xy);
        w.property(szXZ, &LNEDTensor::xz);
        w.property(szYX, &LNEDTensor::yx);
        w.property(szYY, &LNEDTensor::yy);
        w.property(szYZ, &LNEDTensor::yz);
        w.property(szZX, &LNEDTensor::zx);
        w.property(szZY, &LNEDTensor::zy);
        w.property(szZZ, &LNEDTensor::zz);
    }
    
    YQ_INVOKE(reg_LNEDTensor();)
}
