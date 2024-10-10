////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Stream.hpp>

namespace yq::stream {
    class Null : public Stream {
    public:
        bool    is_open() const override;
        bool    write(const char*, size_t) override;
        
        Null();
        ~Null();
    };
}
