////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNUTensor.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNUTensor)

namespace {
    void    reg_BSNUTensor()
    {
        auto w = writer<BSNUTensor>();
        w.description("BSNU Tensor");
        w.property(szXX, &BSNUTensor::xx);
        w.property(szXY, &BSNUTensor::xy);
        w.property(szXZ, &BSNUTensor::xz);
        w.property(szYX, &BSNUTensor::yx);
        w.property(szYY, &BSNUTensor::yy);
        w.property(szYZ, &BSNUTensor::yz);
        w.property(szZX, &BSNUTensor::zx);
        w.property(szZY, &BSNUTensor::zy);
        w.property(szZZ, &BSNUTensor::zz);
    }
    
    YQ_INVOKE(reg_BSNUTensor();)
}
