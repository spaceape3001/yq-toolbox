////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ThreadId.hpp"

#include <atomic>
#include <thread>

#if defined(WIN32)
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

namespace yq {
    namespace thread {
        unsigned int id()
        {
            static std::atomic<unsigned int>    sNext{0};
            static thread_local unsigned int    sRet    = sNext++;
            return sRet;
        }
        
        static unsigned int kMainThread     = id();

        unsigned int num_processors()
        {
            //  C++ can detect this (in theory)
            unsigned int    proc_count = (unsigned int) std::thread::hardware_concurrency();
            
            //  Check the OS info for what we're allowed to use
            #if defined(WIN32)
            SYSTEM_INFO sysinfo;
            GetSystemInfo(&sysinfo);
            unsigned int numCPU = sysinfo.dwNumberOfProcessors;            
            #else
            unsigned int numCPU = (unsigned int) sysconf(_SC_NPROCESSORS_ONLN);
            #endif
            
            //  And cap the amount (or if C++ failed, use the num processors)
            if((numCPU < proc_count) || !proc_count)
                proc_count  = numCPU;
            return proc_count;
        }
    }

    bool is_main_thread()
    {
        return thread::id() == 0;
    }
}
