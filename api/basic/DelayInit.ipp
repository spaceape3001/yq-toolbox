////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DelayInit.hpp"
#include "ThreadId.hpp"
#include <atomic>

namespace yq {

    DelayInit::DelayInit() : m_next(nullptr)
    {
        thread::id();    // simply to force the thread ID...
        m_next  = current(this);
    }

    void         DelayInit::init_all(bool fRepeat)
    {
        while(init_pass() && fRepeat)
            ;
    }

    bool        DelayInit::init_pass()
    {
        DelayInit*     top = current(nullptr);
        if(!top)
            return false;
        
        DelayInit*              x   = nullptr;
        DelayInit*              n   = nullptr;
        
        for(x=top;x;x=n){
            n   = x -> m_next;
            x -> m_next = nullptr;
            x -> initialize();
        }

        return true;
    }


    DelayInit*  DelayInit::current(DelayInit* n)
    {
        static std::atomic<DelayInit*>   ptr(nullptr);
        return ptr.exchange(n);
    }
    
}
