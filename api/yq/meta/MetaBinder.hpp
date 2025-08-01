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
    class UntypeMeta;
    class TypeMeta;
    class Any;

    template <typename T> struct MetaBinder {
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
    static constexpr const bool     is_defined_v    = MetaBinder<T>::Defined;
    
    template <typename T>
    static constexpr const bool     is_type_v       = MetaBinder<T>::IsType;

    template <typename T>
    static constexpr const bool     is_object_v     = MetaBinder<T>::IsObject;

    template <typename T>
    static constexpr const bool     is_interface_v   = MetaBinder<T>::IsInterface;

    template <typename T>
    static constexpr const bool     is_compound_v   = MetaBinder<T>::IsCompound;

    template <typename T>
    using info_t    = typename MetaBinder<T>::Info;
    
    const TypeMeta&        invalid();
    const TypeMeta&        any();

    template <>
    struct MetaBinder<void> {
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
    struct MetaBinder<Any> {
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
        static_assert(MetaBinder<T>::Defined, "Must be meta-declared!");
        return MetaBinder<T>::bind();
    }
    
    template <typename T>
    uint64_t      meta_id()
    {
        static_assert(MetaBinder<T>::Defined, "Must be meta-declared!");
        return MetaBinder<T>::bind().id();
    }

    template <typename T>
    const auto&    meta_unsafe()
    {
        return MetaBinder<T>::bind();
    }

    template <typename T>
    auto           writer()
    {
        static_assert(MetaBinder<T>::Defined, "Must be meta-declared!");
        return typename info_t<T>::Writer<T>( MetaBinder<T>::edit() );
    }
}


/*! \brief Declares a meta type

    \note   MUST BE USED AT GLOBAL SCOPE (NO NAMESPACES)
*/
#define YQ_TYPE_DECLARE(...)                                            \
    namespace yq {                                                      \
        template <>                                                     \
        struct MetaBinder<__VA_ARGS__>  : public std::true_type {       \
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


/*! \brief Declares meta w/o type meta
    
    More for generic types that aren't going to be stored in an any, 
    but still needs type identifiers (for whatever reason)
*/
#define YQ_UNTYPE_DECLARE(...)  \
    namespace yq {                                                      \
        template <>                                                     \
        struct MetaBinder<__VA_ARGS__>  : public std::true_type {       \
            using Info = UntypeMeta;                                    \
            static constexpr const bool Defined         = true;         \
            static constexpr const bool IsObject        = false;        \
            static constexpr const bool IsType          = false;        \
            static constexpr const bool IsCompound      = false;        \
            static constexpr const bool IsInterface     = false;        \
            static constexpr const bool IsProxy         = false;        \
            static constexpr const bool IsTachyon       = false;        \
            static const UntypeMeta&   bind() { return edit(); }        \
            static UntypeMeta&         edit();                          \
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
