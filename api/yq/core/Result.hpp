////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <utility>

namespace yq {

    /*! \brief General dual-return of value/success 
    */
    template <typename T>
    struct Result {
        T       value;
        bool    good = false;
        
        //constexpr Result() : value{}, good{} {}
        //constexpr Result(const T& v) : value(v), good(true) {}
        //constexpr Result(T&&v) : value(std::move(v)), good(true) {}
        //constexpr Result(bool f, const T& v) : value(v), good(f) {}
        //constexpr Result(bool f, T&&v) : value(std::move(v)), good(f) {}
        
        operator const T& () const { return value; }
        bool operator==(const Result&) const noexcept = default;
        
        template <typename U>
        Result<U>       cast_to() const
        {
            return Result<U>{(U) value, good};
        }
        
        constexpr operator std::pair<T,bool>() const { return std::pair<T,bool>(value, good); }
        
    };
}
