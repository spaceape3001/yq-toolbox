////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Cleanup.hpp"
#include <utility>

namespace yq {
    Cleanup::Cleanup()
    {
    }
    
    Cleanup::~Cleanup()
    {
        sweep();
    }
    
    void                Cleanup::add(cleanup_fn&& fn)
    {
        mutex_t::scoped_lock _lock(m_mutex);
        m_cleanup.push_back(std::move(fn));
    }
    
    Cleanup&   Cleanup::operator<<(cleanup_fn&& fn)
    {
        add(std::move(fn));
        return *this;
    }
    
    void                Cleanup::sweep()
    {
        vector_t    what;
        {
            mutex_t::scoped_lock _lock(m_mutex);
            std::swap(what, m_cleanup);
        }
        for(cleanup_fn& fn : what){
            fn();
        }
    }
}
