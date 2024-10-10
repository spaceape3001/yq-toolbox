////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Stream.hpp"

namespace yq {
    namespace {
        class NullStream : public Stream {
        public:
            bool    is_open() const override { return false; }
            bool    write(const char*, size_t) { return true; }
        };
    }


    Stream&  Stream::null()
    {
        static NullStream   ret;
        return ret;
    }
}

