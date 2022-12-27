////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Generic structure for data of a tetrahedron
    */
    template <typename V>
    struct TetrahedronData {
        //! Capture the template parameter
        using data_type = V;
        
        //! The data
        V     a, b, c, d;

        //! Defaulted comparison
        constexpr bool operator==(const TetrahedronData&) const noexcept = default;
    };
}

