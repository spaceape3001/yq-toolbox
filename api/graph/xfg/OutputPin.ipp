////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/OutputPin.hpp>

namespace yq::xfg {
    OutputPin::OutputPin() = default;
    OutputPin::~OutputPin() = default;

    void        publish(pin_id_t off, const void* src, const TypeInfo&type)
    {
        //   TODO
    }
}

