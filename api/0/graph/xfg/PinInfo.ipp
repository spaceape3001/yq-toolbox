////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/xfg/PinInfo.hpp>
#include <0/graph/xfg/NodeInfo.hpp>

namespace yq::xfg {
    PinInfo::PinInfo(std::string_view kName, NodeInfo&par, const std::source_location& sl) : Meta(kName, &par, sl)
    {
        set({Flag::PIN, Flag::XFG});
    }

    const PinInfo*  to_pin(const Meta*m)
    {
        if(m && m->is_pin() && m->is_xfg())
            return static_cast<const PinInfo*>(m);
        return nullptr;
    }
}

