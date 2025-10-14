////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDTensor.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDTensor)

namespace {
    void    reg_TNEDTensor()
    {
        auto w = writer<TNEDTensor>();
        w.description("TNED Tensor");
        w.property(szXX, &TNEDTensor::xx);
        w.property(szXY, &TNEDTensor::xy);
        w.property(szXZ, &TNEDTensor::xz);
        w.property(szYX, &TNEDTensor::yx);
        w.property(szYY, &TNEDTensor::yy);
        w.property(szYZ, &TNEDTensor::yz);
        w.property(szZX, &TNEDTensor::zx);
        w.property(szZY, &TNEDTensor::zy);
        w.property(szZZ, &TNEDTensor::zz);
    }
    
    YQ_INVOKE(reg_TNEDTensor();)
}
