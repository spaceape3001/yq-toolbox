////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <tbb/spin_mutex.h>
#include <set>

namespace yq {
    /*! Used for debugging, for detecting when something is first seen
    
        This uses mutexes, so it's thread safe.
    */
    template <typename T>
    class FirstSeen {
    public:
    
        using value_t   = T;
        using mutex_t   = tbb::spin_mutex;
        using lock_t    = tbb::spin_mutex::scoped_lock;
    
        FirstSeen() 
        {
        }
    
        ~FirstSeen() 
        {
        }
        
        bool    operator()(T v)
        {
            lock_t          _lock(m_mutex);
            auto [i,f]  = m_values.insert(v);
            return f;
        }
    
    private:
        mutex_t         m_mutex;
        std::set<T>     m_values;
    };
}
