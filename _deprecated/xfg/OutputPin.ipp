////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/OutputPin.hpp>

namespace yq::xfg {
    OutputPin::OutputPin() = default;
    OutputPin::~OutputPin() = default;

    void        publish(pin_id_t off, const void* src, const TypeMeta&type)
    {
        //   TODO
    }
}

