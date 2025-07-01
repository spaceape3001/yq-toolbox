////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/*
    Mapping is the concept of coordinate conversions, can be lossy or not.
    
    Classes will have a routine "map" that *is* the map routine.  
    One parameter in, one out, that defines the map space.
    
*/

namespace yq::mapper {

    template <typename M>
    concept SomeMapper {
        
    };


    template <typename M> 
    struct Traits;

}
