////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/units.hpp>
#include <yq/container/Stack.hpp>
#include <yq/core/Any.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/xg/types.hpp>

namespace yq {
    struct XGContext {
    
        //! Current always mode, flip to NaN to exit
        float                                       always  = NaNf;
        
        //! Current sim time
        unit::Second                                time{0.};

        //  fleetingly
        //  stack....
        Stack<xg_value_t>                           stack;
        
        //  will be added/dropped
        //  positional...
        std::vector<xg_value_t>                     values;

        //! Prefer values over variables (faster)
        std::unordered_map<uint32_t, xg_value_t>    variables; 
        
        //! When key/values are needed (nicer for debugging)
        std::map<std::string, xg_value_t, IgCase>   attributes;
        
        XGContext();
        virtual ~XGContext();
    };
}
