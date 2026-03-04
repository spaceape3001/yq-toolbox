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

        //! When key/values are needed (nicer for debugging)
        Map<std::string, xg_value_t, IgCase>    attributes;

        //! True if we're running in interrupt mode
        bool                                    interrupt   = false;    //< set by the runtime
        
        //! Current interrupt priority
        int32_t                                 priority    = 0;        //< set by the runtime
        
        XGRuntime*                              runtime     = nullptr;  //< set by the runtime

        //  fleetingly
        //  stack....
        Stack<xg_value_t>                       stack;
        
    
        //! Current sim time
        unit::Second                            time{0.};

        //  will be added/dropped
        //  positional...
        Vector<xg_value_t>                      values;

        //! Prefer values over variables (faster)
        Hash<uint32_t, xg_value_t>              variables; 
        
        XGContext();
        virtual ~XGContext();
    };
}
