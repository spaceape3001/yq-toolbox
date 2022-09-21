////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/Concat.hpp>

namespace yq {

    /*! \brief Simple API to permit a delayed initialization

        There can be a potential race issue with initializing these and 
        then calling "initialize()" because there's several operations for
        which this object could be registered in the manifest while the derived
        initialized class is still under construction.
    */

    class  DelayInit {
    public:
        struct Ctor;
        struct Invoke;
        
        /*! \brief Initializes all uninitialized
        
            This calls initialize() on all registered hooks.
        
            \note This routine takes a snapshot, operates on that snapshot.  
            If an initialize() registers additional hooks, those will not be initialized 
            unless fRepeat is TRUE.
        
            \param fRepeat  Keep initializing in a loop until no more hooks are registered
        */
        static void         init_all(bool fRepeat=true);

    protected:

        //! Default constructor (sets m_next)
        DelayInit();
        
        //! Override this to be initialized
        virtual void        initialize(){}

    private:

        //! Returns the "current" (uses an atomic) and used for setting m_next
        static DelayInit*   current(DelayInit*);
        static bool         init_pass();
        
            // not copyable/movable
        DelayInit(const DelayInit&) = delete;
        DelayInit(DelayInit&&) = delete;
        void    operator=(const DelayInit&) = delete;
        void    operator=(DelayInit&&) = delete;
     
        //! "Next" hook in the chain, may be NULL
        DelayInit*      m_next;
    };

    /*! \brief Simple class that runs a function during initialization

        Useful for running things on startup.
    */
    struct DelayInit::Ctor : public DelayInit {
        void(*fn)();
        
        Ctor(void(*_fn)()) : fn(_fn) {}
        void    initialize() override { fn(); }
    };

    /*! \brief Macro to invoke code at program startup */
    #define YQ_INVOKE(...) \
        namespace { \
            static ::yq::DelayInit::Ctor   YQ_CONCAT(s_invoke_, __COUNTER__) ( []() { __VA_ARGS__ } ); \
        }
}
