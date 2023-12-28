////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/BasicBuffer.hpp>
#include <0/io/Stream.hpp>

namespace yq {

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
