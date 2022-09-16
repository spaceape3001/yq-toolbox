////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <tbb/spin_rw_mutex.h>

namespace yq {

    /*! \brief Thread safe data access
        
        This class bundles a type with a R/W mutex to assure thread-safe access
        to its contents.
    */
    template <typename T>
    class Guarded {
    public:

        //! Default constructor
        Guarded() {}
        
        //! Constructs with data 
        //! (Note constructor itself is *NOT* thread safe)
        Guarded(const T& v) : m_data(v) {}
        
        //! Assigns the data (under mutex) by copying it in
        Guarded&    operator=(const T& v)
        {
            //  By copying it into a temporary, we marshall any expensive destructors
            //  to fire *outside* the mutex lock.  Instead, only the move operators should be invoked.
            T       old = v;    
            {
                tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, true);
                std::swap(old, m_data);
            }
            return *this;
        }
        
        //! Assigns the data (under mutex) by moving it in
        Guarded&    operator=(T&& v)
        {
            //  By copying it into a temporary, we marshall any expensive destructors
            //  to fire *outside* the mutex lock.  Instead, only the move operators should be invoked.
            T       old = std::move(v);
            {
                tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, true);
                std::swap(old, m_data);
            }
            return *this;
        }

        //! Gets a COPY of the data (under read mutex)
        T   get() const
        {
            tbb::spin_rw_mutex::scoped_lock _lock(m_mutex, false);
            return m_data;
        }
        
        //! Gets a COPY of the data (under read mutex)
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
