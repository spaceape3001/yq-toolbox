////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "preamble.hpp"
#include <tbb/spin_rw_mutex.h>
#include "Grammar.hpp"

namespace yq::expr {
    struct Repo {
        mutable tbb::spin_rw_mutex  mutex;
        Grammar                     grammar;
        
        Repo()
        {
            grammar.add_punct_text('_');
        }
    };
    
    Repo&   repo()
    {
        static Repo s_repo;
        return s_repo;
    }
    
    #define LOCK                                                        \
        static const Repo&  _r  = repo();                               \
        tbb::spin_rw_mutex::scoped_lock     _lock(_r.mutex, false);
    
    #define WLOCK                                                        \
        static Repo&  _r  = repo();                                     \
        tbb::spin_rw_mutex::scoped_lock     _lock(_r.mutex, true);

}

#include "Grammar.ipp"
