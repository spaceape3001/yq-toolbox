////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Stream.hpp>
#include <iosfwd>

namespace yq::stream {
    class StdStream : public Stream {
    public:
    
        StdStream(std::ostream&);
        ~StdStream();
    
        bool write(const char* buf, size_t cb) override;

    private:
        StdStream(const StdStream&) = delete;
        StdStream(StdStream&&) = delete;
        StdStream& operator=(const StdStream&) = delete;
        StdStream& operator=(StdStream&&) = delete;

        std::ostream&   m_output;
    };
}
