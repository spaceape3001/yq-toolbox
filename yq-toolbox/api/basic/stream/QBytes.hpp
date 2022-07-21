////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QByteArray>
#include <basic/Stream.hpp>

namespace yq {
    namespace stream {
        /*! \brief Wrapper to give a stream API to a QByteArray
        */
        struct QBytes : public Stream {
            QByteArray&          data;
            
            QBytes(QByteArray& ref) : data(ref) {}
            
            void write(const char* buf, size_t cb) override
            {
                data.append(buf, cb);
            }
        };
    }
}
