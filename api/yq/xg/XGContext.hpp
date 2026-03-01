////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/units.hpp>
#include <yq/container/Hash.hpp>
#include <yq/container/Map.hpp>
#include <yq/container/Stack.hpp>
#include <yq/container/Vector.hpp>
#include <yq/core/Any.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/xg/types.hpp>

namespace yq {
    struct XGContext {
        XGRuntime&                              runtime;
    
        //! Current always mode, flip to NaN to exit
        double                                  always  = NaN;

        //! When key/values are needed (nicer for debugging)
        Map<std::string, xg_value_t, IgCase>    attributes;
    
        //! Current sim time
        unit::Second                            time{0.};

        //! Last result from given node
        Map<gid_t, xg_result_t>                 results;
        
        //  fleetingly
        //  stack....
        Stack<xg_value_t>                       stack;
        
        //  will be added/dropped
        //  positional...
        Vector<xg_value_t>                      values;

        //! Prefer values over variables (faster)
        Hash<uint32_t, xg_value_t>              variables; 
        
        XGContext(XGRuntime&);
        virtual ~XGContext();
    };
}
