////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>
#include <yq/meta/InfoBinder.hpp>

namespace yq {

    /*! \brief Tristate enumeration
    
        This tristate allows for overriding or taking the prevailing option
    */
    YQ_ENUM(Tristate, ,
        
        //! Default is a "maybe", which means inherit and/or optional
        Maybe       = 1,
        
        MAYBE       = Maybe,
        
        //! Assert a NO on this state, override the inheritance
        No          = 0,
        
        NO          = No,
        
        //! Assert a YES on this state, override the inheritance
        Yes         = 2,
        
        YES         = Yes,
        
        //! Synonym for "maybe"
        Inherit     = Maybe,
        
        INHERIT     = Inherit,

        //! Synonym for "maybe"
        Optional    = Maybe,
        
        OPTIONAL    = Optional
    );
}

YQ_TYPE_DECLARE(yq::Tristate)
