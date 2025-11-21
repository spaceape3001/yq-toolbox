////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/units.hpp>
#include <yq/core/Any.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/xg/types.hpp>

namespace yq::xg {
    using value_t       = std::variant<std::monostate, bool, Any>;
    struct XGContext {
    
        //! Current always mode, flip to NaN to exit
        float                                   always  = NaNf;
        
        //! Current sim time
        unit::Second                            time{0.};

        //! Might do some more for tachyon, etc

        //! Prefer values over variables (faster)
        std::map<uint32_t, value_t>             values; 
        
        //! When key/values are needed (nicer for debugging)
        std::map<std::string, value_t, IgCase>  variables;
        
        XGContext();
        ~XGContext();
    };
}
