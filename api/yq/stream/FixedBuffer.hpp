////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/BasicBuffer.hpp>
#include <yq/core/Stream.hpp>

namespace yq::stream {

    template <size_t N>
    class FixedBuffer : public BasicBuffer<N>, public Stream {
    public:
        virtual bool    is_open() const { return true; }

        virtual bool    write(const char*z, size_t cb) override
        {
            BasicBuffer<N>::append(z, cb);
            return true;
        }
    };

}
