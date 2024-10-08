////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "StdStream.hpp"
#include <ostream>

namespace yq::stream {
    StdStream::StdStream(std::ostream& os) : m_output(os)
    {
    }
    
    StdStream::~StdStream()
    {
        m_output.flush();
    }

    bool StdStream::write(const char* buf, size_t cb) 
    {
        if(buf && cb){
            m_output.write(buf, cb);
            return m_output.fail();
        }
        return false;
    }
}
