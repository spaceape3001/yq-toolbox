////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Enum.hpp>
#include <basic/preamble.hpp>
#include <meta/InfoBinder.hpp>

namespace yq {
    /*! \brief Generic graph namespace
    
        The generic graph namespace is for a general-purpose I/O focused graph
        format.  It won't be obligatory for all use-cases.
    */
    namespace g {
        YQ_ENUM(Flow, ,
            Dead,
            Input,
            Output
        )
        
        struct Document;
        struct Graph;
        struct Node;
        struct Edge;
        struct Pin;
        struct Property;
    }
}

YQ_TYPE_DECLARE(yq::g::Flow)
