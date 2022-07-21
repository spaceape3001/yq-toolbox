////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <math/MKS.hpp>

namespace yq {
    template <typename T, typename DIM, double K>
    struct SCALED {
        using dimension         = DIM;
        using component_type    = T;
        static constexpr const double   FACTOR = K;
        
        T       value = {};
        
        auto operator<=>(const SCALED& b) const noexcept = default;
        
        operator MKS<T,DIM>() const noexcept { return { T(value*K) }; }
        
        SCALED&    operator=(const MKS<T,DIM>& v) 
        {
            value   = v.value / K;
            return *this;
        }
        
        template <double K2>
        requires (K2 != K)
        SCALED&     operator=(const SCALED<T,DIM,K2>& v)
        {
            value   = v.value * (K2/K);
            return *this;
        }
    };

//  --------------------------------------------------------
//  COMPOSITION

    template <typename T, typename DIM, double K>
    MKS<T,DIM> mks(const SCALED<T,DIM,K>& v)
    {
        return (MKS<T,DIM>) v;
    }

    template <typename T, typename DIM, double K>
    struct nan_eval<SCALED<T,DIM,K>> : public std::true_type {
        static consteval SCALED<T,DIM,K> make()
        {                                                   
            return { nan_v<T> };
        }                                                   
    };

    template <typename T, typename DIM, double K>
    struct zero_eval<SCALED<T,DIM,K>> : public std::true_type {
        static consteval SCALED<T,DIM,K> make()
        {
            return { T{} };
        }
    };
    
//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  SETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    template <typename T, typename DIM, double K>
    bool is_finite(const SCALED<T,DIM,K>& v)
    {
        return is_finite(v.value);
    }

    template <typename T, typename DIM, double K>
    bool is_nan(const SCALED<T,DIM,K>& v)
    {
        return is_nan(v.value);
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T, typename DIM, double K>
    SCALED<T,DIM,K> operator+(const SCALED<T,DIM,K>& a)
    {
        return a;
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T, typename DIM, double K>
    SCALED<T,DIM,K> operator-(const SCALED<T,DIM,K>& a)
    {
        return { -a.value };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T, typename DIM, double K>
    MKS<T,DIM>    operator+(const MKS<T,DIM>& a, const SCALED<T,DIM,K>& b)
    {
        return { a.value + b.value*K };
    }

    template <typename T, typename DIM, double K>
    MKS<T,DIM>    operator+(const SCALED<T,DIM,K>& a, const MKS<T,DIM>& b)
    {
        return { a.value*K + b.value };
    }

    template <typename T, typename DIM, double K>
    SCALED<T,DIM,K>    operator+(const SCALED<T,DIM,K>& a, const SCALED<T,DIM,K>& b)
    {
        return { a.value + b.value };
    }

    template <typename T, typename DIM, double K, double K2>
    requires (K != K2)
    SCALED<T,DIM,K>    operator+(const SCALED<T,DIM,K>& a, const SCALED<T,DIM,K2>& b)
    {
        return { a.value + b.value*(K2/K) };
    }
    
    template <typename T, typename DIM, double K>
    SCALED<T,DIM,K>&    operator+=(SCALED<T,DIM,K>& a, const MKS<T,DIM>& b)
    {
        a.value += b.value/K;
        return a;
    }

    template <typename T, typename DIM, double K>
    SCALED<T,DIM,K>&    operator+=(SCALED<T,DIM,K>& a, const SCALED<T,DIM,K>& b)
    {
        a.value += b.value;
        return a;
    }

    template <typename T, typename DIM, double K, double K2>
    requires (K != K2)
    SCALED<T,DIM,K>&    operator+=(SCALED<T,DIM,K>& a, const SCALED<T,DIM,K2>& b)
    {
        a.value += b.value * (K2/K);
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T, typename DIM, double K>
    MKS<T,DIM>    operator-(const MKS<T,DIM>& a, const SCALED<T,DIM,K>& b)
    {
        return { a.value - b.value*K };
    }

    template <typename T, typename DIM, double K>
    MKS<T,DIM>    operator-(const SCALED<T,DIM,K>& a, const MKS<T,DIM>& b)
    {
        return { a.value*K - b.value };
    }

    template <typename T, typename DIM, double K>
    SCALED<T,DIM,K>    operator-(const SCALED<T,DIM,K>& a, const SCALED<T,DIM,K>& b)
    {
        return { a.value - b.value };
    }

    template <typename T, typename DIM, double K, double K2>
    requires (K != K2)
    SCALED<T,DIM,K>    operator-(const SCALED<T,DIM,K>& a, const SCALED<T,DIM,K2>& b)
    {
        return { a.value - b.value*(K2/K) };
    }
    
    template <typename T, typename DIM, double K>
    SCALED<T,DIM,K>&    operator-=(SCALED<T,DIM,K>& a, const MKS<T,DIM>& b)
    {
        a.value -= b.value/K;
        return a;
    }

    template <typename T, typename DIM, double K>
    SCALED<T,DIM,K>&    operator-=(SCALED<T,DIM,K>& a, const SCALED<T,DIM,K>& b)
    {
        a.value -= b.value;
        return a;
    }

    template <typename T, typename DIM, double K, double K2>
    requires (K != K2)
    SCALED<T,DIM,K>&    operator-=(SCALED<T,DIM,K>& a, const SCALED<T,DIM,K2>& b)
    {
        a.value -= b.value * (K2/K);
        return a;
    }
    
//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T, typename DIM, double K, typename R>
    bool is_close(const R& compare, SCALED<T,DIM,K> actual, SCALED<T,DIM,K> expected)
    {
        return compare(actual.value-expected.value, expected.value);
    }


    template <typename T, typename DIM, double K, typename R>
    bool is_close(const R& compare, SCALED<T,DIM,K> actual, std::type_identity_t<T> v)
    {
        return compare(actual, SCALED<T,DIM,K>{v});
    }

}
