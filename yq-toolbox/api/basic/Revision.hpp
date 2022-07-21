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
    class Revision : trait::not_copyable, trait::not_moveable {
    public:
    
        uint64_t    revision() const { return m_revision; }
        
    protected:
        Revision(Revision* m=nullptr);
        
        void        changed();
    private:
        uint64_t    m_revision;
        Revision*   m_master;
    };
}
