////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <vector>
#include <tbb/spin_mutex.h>

namespace yq {
    using cleanup_fn               = std::function<void()>;
    
    /*! Manager of cleanup routines
    
		This will sweep (and clear) all added "cleanup routines" that need
		to be triggered at a specific point (or, with a mutex lock, etc).
    */
    class Cleanup {
    public:
    
		//! Constructor
        Cleanup();
        
        //! Destructor
        ~Cleanup();
        
        //! Add a callback to run with sweep (lambda capture good here)
        void                add(cleanup_fn&&);

        //! Add a callback to run with sweep (lambda capture good here)
        Cleanup&            operator<<(cleanup_fn&&);
        
        /*! Sweep/call all cleanup routines
        
            \note Clears all registered routines
        */
        void                sweep();
        
    private:
        using mutex_t   = tbb::spin_mutex;
        using vector_t  = std::vector<cleanup_fn>;
    
        vector_t            m_cleanup;
        mutable mutex_t     m_mutex;
    };
}
