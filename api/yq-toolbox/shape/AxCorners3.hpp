////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_AXCORNERS3_HPP 1



namespace yq {

    /*! \brief Store data for corners of 3D box
    */
    template <typename T>
    struct AxCorners3 {

        //! Component type (captures the argument)
        using component_type    = T;
    
        //! Lower-lower-lower corner
        T   lll;    // south west bottom

        //! Lower-lower-upper corner
        T   llh;

        //! Lower-upper-lower corner
        T   lhl;

        //! Lower-upper-upper corner
        T   lhh;

        //! Upper-lower-lower corner
        T   hll;

        //! Upper-lower-upper corner
        T   hlh;

        //! Upper-upper-lower corner
        T   hhl;

        //! Upper-upper-upper corner
        T   hhh;
        
        //! Equality operator (defaulted)
        bool operator==(const AxCorners3&) const noexcept = default;
    };
}

