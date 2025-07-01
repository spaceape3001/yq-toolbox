////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/math/Fraction.hpp>
#include <yq/unit/dims.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <string_view>
#include <vector>

namespace yq {
    struct Dimension {
        FractionI   time;
        FractionI   length;
        FractionI   angle;
        FractionI   mass;
        FractionI   temperature;
        FractionI   current;
        FractionI   matter;         //!< ie Moles
        FractionI   intensity;
        
        auto    operator<=>(const Dimension&) const = default;
    };

    //  list predefined dimensions
    #if 0
    const std::vector<Dimension>&   dimensions();
    Dimension                       dimension(std::string_view);
    std::string_view                to_string(const Dimension&);
    #endif
    
    template <typename T, typename L, typename A, typename M, typename K, typename C, typename Q, typename I>
    consteval Dimension dimension(const dim::DIM<T,L,A,M,K,C,Q,I>&)
    {
        return { fraction(T()), fraction(L()), fraction(A()), fraction(M()), fraction(K()), fraction(C()), fraction(Q()), fraction(I()) };
    }
}

YQ_TYPE_DECLARE(yq::Dimension)
