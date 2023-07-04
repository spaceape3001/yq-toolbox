////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/xfg/PinInfo.hpp>
#include <graph/xfg/NodeInfo.hpp>

namespace yq::xfg {
    PinInfo::PinInfo(std::string_view kName, NodeInfo&par, const std::source_location& sl) : Meta(kName, &par, sl)
    {
        set(Flag::PIN);
    }

    const PinInfo*  to_pin(const Meta*m)
    {
        if(m && m->is_pin())
            return static_cast<const PinInfo*>(m);
        return nullptr;
    }
}

