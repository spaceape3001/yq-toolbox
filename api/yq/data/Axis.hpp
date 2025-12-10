////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq::data {
    // TBD
    struct Axis {
        AxisType                type        = AxisType::Linear;
        const TypeMeta*         meta        = nullptr;
        std::vector<double>     ticks;
        std::string             name;
        
        Axis();
        Axis(const Axis&);
        ~Axis();
    };
}
