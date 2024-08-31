////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <atomic>
#include <system_error>
#include <exception>
#include <type_traits>
#include <yq/keywords.hpp>
#include <yq/basic/Ref.hpp>

namespace yq {
    template <typename> class Future;
    template <typename> class Promise;
}
    
namespace yq::future {
    class PromiseBase;
    class FutureBase;
    
    class Exception : public std::logic_error {
    public:
        Exception(const char* zMsg) : std::logic_error(zMsg) {}
    };
    
    enum class Fate {
        None        = 0,        //!< No fate yet, pending
        Ready,                  //!< "Done" with data present
        Done,                   //!< "Done" but no data present
        Cancelled,              //!< "Done" but cancelled
        Error,                  //!< "Done" but encountered the error code
        Exception,              //!< "Done" but encountered excpetion
        Fetched                 //!< "Done" with data, but data has already been retrieved
    };
    
    struct State  : public RefCount {
        std::atomic<bool>       cancel{false};
        std::atomic<Fate>       fate{Fate::None};
        std::error_code         error;
        std::exception_ptr      exception;
        int                     priority    = 0;
    };
    
    template <typename T>
    struct Data : public State {
        T                   payload;
    };
    
    template <>
    struct Data<void> : public State {
    };

    class Base {
    public:
    
        //! TRUE if valid (ie not detached)
        bool        valid() const noexcept;
    
    protected:
        Base(Ref<State>);
        Base(const Base&cp);
        Base(Base&&mv);
        ~Base();
        Base& operator=(const Base&);
        Base& operator=(Base&&);
        
        Ref<State>      m_data;

        Ref<State>&           _ref() { return m_data; }
        const Ref<State>&     _ref() const { return m_data; }
        
        template <typename T>
        Ref<Data<T>>&                 _as() 
        { 
            return reinterpret_cast<Ref<Data<T>>&>(_ref()); 
        }
        
        template <typename T>
        const Ref<Data<T>>&           _as() const 
        { 
            return reinterpret_cast<const Ref<Data<T>>&>(_ref()); 
        }
    };
}

namespace yq {
    class FFuture : public future::Base {
    public:
    
        // Aborting is cancellation, or error/exception condition
        bool                aborted() const;
    
        /*! Cancels the future/promise
        
            This signals to the promise that the result isn't needed, 
            to cancel it.
            
            \note This cancellation might be too late to be honored.
        */
        void                cancel();

        //! TRUE if the fate is DONE
        bool                done() const;
        
        //! TRUE if the fate is error or exception
        bool                errored() const;
        
        std::error_code     get_error() const;
        std::exception_ptr  get_exception() const;
        
        //! Current fate
        future::Fate        fate() const;
        
        //! TRUE if the fate isn't none
        bool                finished() const;
        
        //! TRUE if we're ready to get data
        bool                ready() const;
        
    protected:
        FFuture(Ref<future::State> st={});
        FFuture(const FFuture&);
        FFuture(FFuture&&);
        FFuture& operator=(const FFuture&);
        FFuture& operator=(FFuture&&);
        ~FFuture();
    };
    

    /*! \brief Base promise type
    */
    class PPromise : public future::Base {
    public:

        //! TRUE if cancelled
        bool        cancelled() const noexcept;

        //! Sets & detaches
        bool        set(cancel_t);

        //! Sets & detaches
        bool        set(done_t);

        //! Sets & detaches
        bool        set(std::error_code ec);

        //! Sets & detaches
        bool        set(std::exception_ptr ex);

    
    protected:
        PPromise(Ref<future::State> st={});
        PPromise(PPromise&&);
        ~PPromise();
        PPromise& operator=(PPromise&&);
        
        PPromise(const PPromise&) = delete;
        PPromise& operator=(const PPromise&) = delete;
    };



    /*! \brief Future with Cancel
    
        Unlike std::future, this one has a cancellation button!
    */
    template <typename T>
    class Future : public FFuture {
        friend class Promise<T>;
    public:
    
        using Data   = future::Data<T>;
    
        //! Constructs an invalid (empty) future
        Future(){}
        
        //! Moves a future
        Future(Future&& mv) : FFuture(std::move(mv)) { }
        
        //! Shallow copies a future (note, keep this in mind)
        Future(const Future& cp) : FFuture(cp) {}
        
        Future& operator=(const Future&cp)
        {
            FFuture::operator=(cp);
            return *this;
        }
        
        Future& operator=(Future&& mv)
        {
            FFuture::operator=(std::move(mv));
            return *this;
        }
       
        //! Gets the data, a future exception will be thrown if this can't be done
        template <typename U=T>
        requires (!std::is_same_v<U,void>)
        const U&            get() const
        {
            if(!ready())
                throw future::Exception("Resource is not ready to be gotten");
            return _as<U>()->payload;
        }
        
        //! Gets the data, nullptr returns if it can't be done
        template <typename U=T>
        requires (!std::is_same_v<U,void>)
        const U*            get_ptr() const
        {
            if(!ready())
                return nullptr;
            return &(_as<U>()->payload);
        }
        
        //! Will unload the payload into this move (good for large objects)
        template <typename U=T>
        requires (!std::is_same_v<U,void>)
        U                   steal()
        {
            if(!ready())
                throw future::Exception("Resource is not ready to be gotten");
            m_data -> fate  = future::Fate::Fetched;
            return std::move(_as<U>()->payload);
        }

        //! Destructor
        ~Future(){}

    private:
        Future(Ref<Data> p) : FFuture(p) {}
    };

    template <typename T>
    class Promise : public PPromise {
    public:
        using PPromise::set;
        
        //! Default, constructs a promise
        Promise() : PPromise(new future::Data<T>)
        {
        }
        
        //! Move constructor
        Promise( Promise&& mv) : PPromise(std::move(mv))
        {
        }
        
        //! Destructor
        ~Promise()
        {
        }
        
        //! Move operator (implict destruction of other promise)
        Promise&    operator=(Promise&& mv)
        {
            PPromise::operator=(std::move(mv));
            return *this;
        }
        
        //! Gets the future
        Future<T>   get_future() const
        {
            return Future<T>(_as<T>());
        }

        
        //! Sets & detaches
        template <typename U=T>
        requires (!std::is_same_v<U,void>)
        bool        set(U&&val)
        {
            if(m_data){
                _as<U>()->payload   = std::move(val);
                m_data -> fate      = future::Fate::Ready;
                m_data              = {};
                return true;
            } else {
                return false;
            }
        }
        
        //! Sets & detaches
        template <typename U=T>
        requires (!std::is_same_v<U,void>)
        bool        set(U&&val, std::error_code ec)
        {
            if(m_data){
                _as<U>()->payload   = std::move(val);
                m_data -> error     = ec;
                m_data -> fate      = future::Fate::Ready;
                m_data              = {};
                return true;
            } else {
                return false;
            }
        }

        //! Copy prohibited
        Promise(const Promise&) = delete;
        //! Copy prohibited
        Promise&    operator=(const Promise&) = delete;
    };
    
}
