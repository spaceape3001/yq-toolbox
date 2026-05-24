////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


//#include <0/basic/preamble.hpp>
#include <yq/meta/MetaBinder.hpp>

namespace yq {
    /*! \brief Generic graph namespace
    
        The generic graph namespace is for a general-purpose I/O focused graph
        format.  It won't be obligatory for all use-cases.
    */
    namespace g {
        enum class Flow : uint8_t {
            Dead,
            Input,
            Output
        };
        
        struct Document;
        struct Graph;
        struct Node;
        struct Edge;
        struct Pin;
        struct Property;
    }
}

YQ_TYPE_DECLARE(yq::g::Flow)
