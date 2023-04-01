////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Enum.hpp>
#include <basic/Flag.hpp>

#include <filesystem>
#include <string>
#include <string_view>
#include <type_traits>

namespace yq {
    class Stream;

    Stream&     operator<<(Stream&, const std::string&);
    Stream&     operator<<(Stream&, std::string_view);
    Stream&     operator<<(Stream&, const char*);
    Stream&     operator<<(Stream&, char);
    Stream&     operator<<(Stream&, char32_t);

    Stream&     operator<<(Stream&, float);
    Stream&     operator<<(Stream&, double);

    Stream&     operator<<(Stream&, bool);

    Stream&     operator<<(Stream&, int8_t);
    Stream&     operator<<(Stream&, int16_t);
    Stream&     operator<<(Stream&, int32_t);
    Stream&     operator<<(Stream&, int64_t);

    Stream&     operator<<(Stream&, uint8_t);
    Stream&     operator<<(Stream&, uint16_t);
    Stream&     operator<<(Stream&, uint32_t);
    Stream&     operator<<(Stream&, uint64_t);

    Stream&     operator<<(Stream&, const std::filesystem::path&);

    template <typename E>
    Stream&     operator<<(Stream& str, EnumImpl<E> val)
    {
        return str << val.key();
    }
    
    template <typename E>
    Stream&     operator<<(Stream& str, Flag<E> val)
    {
        str << '{';
        bool f = true;
        for(E e : E::all_values()){
            if(val.is_set(e)){
                if(f){
                    f   = false;
                } else 
                    str << "|";
                str << e.key();
            }
        }
        str << '}';
        return str;
    }

    
    //  STREAM detection
    template <typename T, class = void>
    struct has_stream : public std::false_type {};
    
    template <typename T>
    using stream_op = decltype(std::declval<Stream>() << std::declval<T>());
    
    template <typename T>
    struct has_stream<T,std::void_t<stream_op<T>>> : public std::true_type{};
    
    template <typename T>
    inline constexpr bool has_stream_v = has_stream<T>::value;
}
