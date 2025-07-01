////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>
#include <cstdint>
#include <string>

namespace yq {
    class TypeMeta;
    class Any;

    template <typename T> struct InfoBinder {
        using Info  = void;
        static constexpr const bool Defined     = false;
        static constexpr const bool IsCompound  = false;
        static constexpr const bool IsType      = false;
        static constexpr const bool IsObject    = false;
        
        static constexpr const bool IsInterface = false;
        static constexpr const bool IsProxy     = false;
        static constexpr const bool IsTachyon   = false;
    };
    
    template <typename T>
    static constexpr const bool     is_defined_v    = InfoBinder<T>::Defined;
    
    template <typename T>
    static constexpr const bool     is_type_v       = InfoBinder<T>::IsType;

    template <typename T>
    static constexpr const bool     is_object_v     = InfoBinder<T>::IsObject;

    template <typename T>
    static constexpr const bool     is_interface_v   = InfoBinder<T>::IsInterface;

    template <typename T>
    static constexpr const bool     is_compound_v   = InfoBinder<T>::IsCompound;

    template <typename T>
    using info_t    = typename InfoBinder<T>::Info;
    
    const TypeMeta&        invalid();
    const TypeMeta&        any();

    template <>
    struct InfoBinder<void> {
        using Info   = TypeMeta;
        static constexpr const bool Defined         = true;
        static constexpr const bool IsCompound      = false;
        static constexpr const bool IsType          = false;
        static constexpr const bool IsObject        = false;
        static constexpr const bool IsInterface     = false;
        static constexpr const bool IsProxy         = false;
        static constexpr const bool IsTachyon       = false;
        static const TypeMeta&  bind() { return invalid(); }
    };

    template <>
    struct InfoBinder<Any> {
        using Info   = TypeMeta;
        static constexpr const bool Defined         = true;
        static constexpr const bool IsCompound      = false;
        static constexpr const bool IsType          = false;
        static constexpr const bool IsObject        = false;
        static constexpr const bool IsInterface     = false;
        static constexpr const bool IsProxy         = false;
        static constexpr const bool IsTachyon       = false;
        static const TypeMeta&  bind() { return any(); }
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
        struct InfoBinder<__VA_ARGS__>  : public std::true_type {       \
            using Info = TypeMeta;                                      \
            static constexpr const bool Defined         = true;         \
            static constexpr const bool IsObject        = false;        \
            static constexpr const bool IsType          = true;         \
            static constexpr const bool IsCompound      = true;         \
            static constexpr const bool IsInterface     = false;        \
            static constexpr const bool IsProxy         = false;        \
            static constexpr const bool IsTachyon       = false;        \
            static const TypeMeta&   bind() { return edit(); }          \
            static TypeMeta&         edit();                            \
        };                                                              \
    } 


YQ_TYPE_DECLARE(std::string)
YQ_TYPE_DECLARE(bool)
YQ_TYPE_DECLARE(double)
YQ_TYPE_DECLARE(float)
YQ_TYPE_DECLARE(char32_t)
YQ_TYPE_DECLARE(int8_t)
YQ_TYPE_DECLARE(int16_t)
YQ_TYPE_DECLARE(int32_t)
YQ_TYPE_DECLARE(int64_t)
YQ_TYPE_DECLARE(uint8_t)
YQ_TYPE_DECLARE(uint16_t)
YQ_TYPE_DECLARE(uint32_t)
YQ_TYPE_DECLARE(uint64_t)
