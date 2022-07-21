////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/Fraction.hpp>
#include "dims.hpp"

namespace yq {
    struct Dimension {
        FractionI   time;
        FractionI   length;
        FractionI   angle;
        FractionI   mass;
        FractionI   temperature;
        FractionI   current;
        FractionI   matter;
        FractionI   intensity;
        
        auto    operator<=>(const Dimension&) const = default;
    };

    //  list predefined dimensions
    const std::vector<Dimension>&   dimensions();
    Dimension                       dimension(std::string_view);
    std::string_view                to_string(const Dimension&);
    
    template <typename T, typename L, typename A, typename M, typename K, typename C, typename Q, typename I>
    consteval Dimension dimension(const dim::DIM<T,L,A,M,K,C,Q,I>&)
    {
        return { fraction(T()), fraction(L()), fraction(A()), fraction(M()), fraction(K()), fraction(C()), fraction(Q()), fraction(I()) };
    }
}

YQ_TYPE_DECLARE(yq::Dimension)
