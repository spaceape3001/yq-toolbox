////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>
#include <basic/trait/not_moveable.hpp>
#include <basic/trait/not_copyable.hpp>

namespace yq {
    class UniqueID : trait::not_copyable, trait::not_moveable {
    public:
        uint64_t    id() const { return m_id; }
        
    protected:
        UniqueID();
    private:
        uint64_t    m_id;
    };
}
