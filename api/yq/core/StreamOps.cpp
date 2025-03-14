////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/Stream.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/text/format.hpp>

namespace yq {
    Stream&     operator<<(Stream&str, std::string_view v)
    {
        str.write(v.data(), v.size());
        return str;
    }

    Stream&     operator<<(Stream&str, const std::string&v)
    {
        str.write(v.data(), v.size());
        return str;
    }

    Stream&     operator<<(Stream&str, const char*z)
    {
        return operator<<(str, std::string_view(z));
    }

    Stream&     operator<<(Stream& str, char v)
    {
        str.write(&v, 1);
        return str;
    }

    Stream&     operator<<(Stream&str, char32_t v)
    {
        return str << to_string_view(v);
    }

    Stream&     operator<<(Stream&str, float v)
    {
        return str << to_string_view(v);
    }

    Stream&     operator<<(Stream&str, double v)
    {
        str << to_string_view(v);
        return str;
    }

    Stream&     operator<<(Stream&str, bool v)
    {
        return str << to_string_view(v);
    }


    Stream&     operator<<(Stream&str, int8_t v)
    {
        return str << to_string_view(v);
    }

    Stream&     operator<<(Stream&str, int16_t v)
    {
        return str << to_string_view(v);
    }

    Stream&     operator<<(Stream&str, int32_t v)
    {
        return str << to_string_view(v);
    }

    Stream&     operator<<(Stream&str, int64_t v)
    {
        return str << to_string_view(v);
    }


    Stream&     operator<<(Stream&str, uint8_t v)
    {
        return str << to_string_view(v);
    }

    Stream&     operator<<(Stream&str, uint16_t v)
    {
        return str << to_string_view(v);
    }

    Stream&     operator<<(Stream&str, uint32_t v)
    {
        return str << to_string_view(v);
    }

    Stream&     operator<<(Stream&str, uint64_t v)
    {
        return str << to_string_view(v);
    }


    Stream&     operator<<(Stream&str, const filesystem_path_t&v)
    {
        return str << v.c_str();
    }

}

