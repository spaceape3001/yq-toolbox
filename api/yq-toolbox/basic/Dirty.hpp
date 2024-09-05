////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Container to alert if the contents have been altered
    
    */
    template <typename T>
    struct Dirty {
        T       value;
        bool    dirty   = false;
        
        Dirty&  operator=(const T& v)
        {
            value   = v;
            dirty   = true;
            return *this;
        }

        Dirty&  operator=(T&& v)
        {
            value   = std::move(v);
            dirty   = true;
            return *this;
        }
    };
}
