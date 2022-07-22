////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/preamble.hpp>
#include <type_traits>

namespace yq {
    class TypeInfo;
    class Any;

    template <typename T> struct InfoBinder {
        using Info  = void;
        static constexpr const bool Defined     = false;
        static constexpr const bool IsCompound  = false;
        static constexpr const bool IsType      = false;
        static constexpr const bool IsObject    = false;
    };
    
    template <typename T>
    static constexpr const bool     is_defined_v  = InfoBinder<T>::Defined;
    
    template <typename T>
    static constexpr const bool     is_type_v     = InfoBinder<T>::IsType;

    template <typename T>
    static constexpr const bool     is_object_v   = InfoBinder<T>::IsObject;

    template <typename T>
    static constexpr const bool     is_compound_v = InfoBinder<T>::IsCompound;

    template <typename T>
    using info_t    = typename InfoBinder<T>::Info;
    
    const TypeInfo&        invalid();
    const TypeInfo&        any();

    template <>
    struct InfoBinder<void> {
        using Info   = TypeInfo;
        static constexpr const bool Defined     = true;
        static constexpr const bool IsCompound  = false;
        static constexpr const bool IsType      = false;
        static constexpr const bool IsObject    = false;
        static const TypeInfo&  bind() { return invalid(); }
    };

    template <>
    struct InfoBinder<Any> {
        using Info   = TypeInfo;
        static constexpr const bool Defined     = true;
        static constexpr const bool IsCompound  = false;
        static constexpr const bool IsType      = true;
        static constexpr const bool IsObject    = false;
        static const TypeInfo&  bind() { return any(); }
    };

    template <typename T>
    const auto&    meta()
    {
        static_assert(InfoBinder<T>::Defined, "Must be meta-declared!");
        return InfoBinder<T>::bind();
    }

    template <typename T>
    const auto&    meta_unsafe()
    {
        return InfoBinder<T>::bind();
    }

    template <typename T>
    auto           writer()
    {
        static_assert(InfoBinder<T>::Defined, "Must be meta-declared!");
        return typename info_t<T>::Writer<T>( InfoBinder<T>::edit() );
    }
}


/*! \brief Declares a meta type

    \note   MUST BE USED AT GLOBAL SCOPE (NO NAMESPACES)
*/
#define YQ_TYPE_DECLARE(...)                                            \
    namespace yq {                                                      \
        template <>                                                     \
        struct InfoBinder<__VA_ARGS__>  : public std::true_type {           \
            using Info = TypeInfo;                                      \
            static constexpr const bool Defined     = true;             \
            static constexpr const bool IsObject    = false;            \
            static constexpr const bool IsType      = true;             \
            static constexpr const bool IsCompound  = true;             \
            static const TypeInfo&   bind() { return edit(); }          \
            static TypeInfo&         edit();                            \
        };                                                              \
    } 


YQ_TYPE_DECLARE(std::string)
YQ_TYPE_DECLARE(bool)
YQ_TYPE_DECLARE(double)
YQ_TYPE_DECLARE(float)
YQ_TYPE_DECLARE(int8_t)
YQ_TYPE_DECLARE(int16_t)
YQ_TYPE_DECLARE(int32_t)
YQ_TYPE_DECLARE(int64_t)
YQ_TYPE_DECLARE(uint8_t)
YQ_TYPE_DECLARE(uint16_t)
YQ_TYPE_DECLARE(uint32_t)
YQ_TYPE_DECLARE(uint64_t)
