////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*!  Basis for SFINAE trait detection
        
        As the basis, we need to have something to swallow valid/invalid subsitutions
    */
    template <class T> struct sink 
    { 
        typedef void type; 
    };

    template <class T>  using sink_t = typename sink<T>::type;
}
