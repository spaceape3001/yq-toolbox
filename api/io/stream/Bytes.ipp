////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Bytes.hpp"
#include <0/basic/ByteArray.hpp>

namespace yq {
    namespace stream {
        bool Bytes::write(const char* buf, size_t cb)
        {
            m_bytes.append(buf, cb);
            return true;
        }
    }
}

