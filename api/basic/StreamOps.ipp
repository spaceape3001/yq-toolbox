////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/Stream.hpp>
#include <basic/StreamOps.hpp>
#include <basic/TextUtils.hpp>

//#include "Bytes.hpp"
//#include "File.hpp"
//#include "First.hpp"
//#include "LineCol.hpp"
//#include "OSFile.hpp"
//#include "Ops.hpp"
//#include "Text.hpp"

//#include <basic/FileUtils.hpp>
//#include <basic/ByteArray.hpp>

//#include <cstring>

//#include <fcntl.h>
//#include <unistd.h>


namespace yq {
    static constexpr const size_t   kStdBuf = 63;

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


    Stream&     operator<<(Stream&str, const std::filesystem::path&v)
    {
        return str << v.c_str();
    }

}

