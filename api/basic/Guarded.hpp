////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <tbb/spin_rw_mutex.h>

namespace yq {
    template <typename T>
    class Guarded {
    public:

        Guarded() {}
        Guarded(const T& v) : m_data(v) {}
        
        Guarded&    operator=(const T& v)
        {
            {
                tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, true);
                m_data      = v;
            }
            return *this;
        }
        
        T   get() const
        {
            tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, false);
            return m_data;
        }
        
        operator T() const
        {
            tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, false);
            return m_data;
        }
        
    private:
        mutable tbb::spin_rw_mutex  m_mutex;
        T                           m_data;
    };
}
