////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/core/UniqueID.hpp>
#include <atomic>

namespace yq {
    static uint64_t     generateUniqueId()
    {
        static std::atomic<uint64_t>    last{0};
        return ++last;
    }

    UniqueID::UniqueID() : m_id(generateUniqueId())
    {
    }
}
