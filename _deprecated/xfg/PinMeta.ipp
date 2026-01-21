////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/PinMeta.hpp>
#include <0/graph/xfg/NodeMeta.hpp>

namespace yq::xfg {
    PinMeta::PinMeta(std::string_view kName, NodeMeta&par, const std::source_location& sl) : Meta(kName, &par, sl)
    {
        set({Flag::PIN, Flag::XFG});
    }

    const PinMeta*  to_pin(const Meta*m)
    {
        if(m && m->is_pin() && m->is_xfg())
            return static_cast<const PinMeta*>(m);
        return nullptr;
    }
}

