////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>
#include <yq/meta/MetaBinder.hpp>

namespace yq {

    //! Generalized node type (that the runtime needs to know about)
    YQ_ENUM(XGNodeType, ,
        //! Generic node, unremarkable, ordinary, common
        Unspecified = 0, 
        
        //! Always node
        Always,
        
        //! Continue (execution)
        Continue,
        
        //! Done 
        Done,
        
        //! Logic node
        Logic,
        
        Resume,
        
        Start
    );
}

YQ_TYPE_DECLARE(yq::XGNodeType)
