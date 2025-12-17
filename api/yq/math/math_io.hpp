////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/text/format.hpp>

namespace yq { class Stream; }

namespace yq::math_io {
    //////////////////////////////////////////////////////////////////////////////

    std::string_view     format_n(const double*, uint8_t, int kMaxDigits=kMaxDoubleDigits);
    std::string_view     format_n(const float*, uint8_t, int kMaxDigits=kMaxFloatDigits);
    std::string_view     format_n(const int8_t*, uint8_t);
    std::string_view     format_n(const int16_t*, uint8_t);
    std::string_view     format_n(const int32_t*, uint8_t);
    std::string_view     format_n(const int64_t*, uint8_t);
    std::string_view     format_n(const uint8_t*, uint8_t);
    std::string_view     format_n(const uint16_t*, uint8_t);
    std::string_view     format_n(const uint32_t*, uint8_t);
    std::string_view     format_n(const uint64_t*, uint8_t);

    template <typename V, typename T=typename V::component_type>
    std::string_view     format(const V& v)
    {
        static constexpr const size_t kCount   = sizeof(V) / sizeof(T);
        static_assert(kCount < 256);
        return format_n((const T*)&v, (uint8_t) kCount);
    }

    //////////////////////////////////////////////////////////////////////////////    
    
    bool    parse_n(double*, uint8_t, std::string_view);
    bool    parse_n(float*, uint8_t, std::string_view);
    bool    parse_n(int8_t*, uint8_t, std::string_view);
    bool    parse_n(int16_t*, uint8_t, std::string_view);
    bool    parse_n(int32_t*, uint8_t, std::string_view);
    bool    parse_n(int64_t*, uint8_t, std::string_view);
    bool    parse_n(uint8_t*, uint8_t, std::string_view);
    bool    parse_n(uint16_t*, uint8_t, std::string_view);
    bool    parse_n(uint32_t*, uint8_t, std::string_view);
    bool    parse_n(uint64_t*, uint8_t, std::string_view);
    
    template <typename V, typename T=typename V::component_type>
    bool parse(V& v, std::string_view txt)
    {
        static constexpr const size_t kCount   = sizeof(V) / sizeof(T);
        static_assert(kCount < 256);
        return parse_n((T*) &v, (uint8_t) kCount, txt);
    }
    
    //////////////////////////////////////////////////////////////////////////////

    void    print_n(Stream&, const double*, uint8_t);
    void    print_n(Stream&, const float*, uint8_t);
    void    print_n(Stream&, const int8_t*, uint8_t);
    void    print_n(Stream&, const int16_t*, uint8_t);
    void    print_n(Stream&, const int32_t*, uint8_t);
    void    print_n(Stream&, const int64_t*, uint8_t);
    void    print_n(Stream&, const uint8_t*, uint8_t);
    void    print_n(Stream&, const uint16_t*, uint8_t);
    void    print_n(Stream&, const uint32_t*, uint8_t);
    void    print_n(Stream&, const uint64_t*, uint8_t);
    
    template <typename V, typename T=typename V::component_type>
    void    print(Stream& str, const V& v)
    {
        static constexpr const size_t kCount   = sizeof(V) / sizeof(T);
        static_assert(kCount < 256);
        print_n(str, (const T*) &v, (uint8_t) kCount);
    }
}
