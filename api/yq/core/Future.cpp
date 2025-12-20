////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Future.hpp"

namespace yq::future {
    
    Base::Base(Ref<State> p) : m_data(p)
    {
    }
    
    Base::Base(const Base&cp) : m_data(cp.m_data)
    {
    }
    
    Base::Base(Base&&mv) : m_data(std::move(mv.m_data))
    {
    }
    
    Base::~Base()
    {
    }
    
    Base& Base::operator=(const Base& cp)
    {
        if(this != &cp){
            m_data  = cp.m_data;
        }
        return *this;
    }
    
    Base& Base::operator=(Base&& mv)
    {
        if(this != &mv){
            m_data  = std::move(mv.m_data);
        }
        return *this;
    }

    bool  Base::aborted() const
    {
        switch(fate()){
        case Fate::Cancelled:
        case Fate::Error:
        case Fate::Exception:
            return true;
        default:
            return false;
        }
    }

    void  Base::cancel()
    {
        if(m_data){
            m_data -> cancel    = true;
        }
    }

        //! TRUE if the fate is error or exception
    bool  Base::errored() const
    {
        switch(fate()){
        case Fate::Error:
        case Fate::Exception:
            return true;
        default:
            return false;
        }
    }
    
    
    Fate  Base::fate() const
    {
        if(m_data)
            return m_data -> fate;
        return Fate::None;
    }
    

    bool  Base::finished() const
    {
        return fate() != Fate::None;
    }

    bool  Base::ready() const
    {
        return fate() == Fate::Ready;
    }
    
    bool  Base::valid() const noexcept
    {
        return m_data.valid();
    }

}

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

namespace yq {
    using namespace future;
    
    FFuture::FFuture(Ref<State> st) : Base(st)
    {
    }
    
    FFuture::FFuture(const FFuture&cp) : Base(cp)
    {
    }
    
    FFuture::FFuture(FFuture&& mv) : Base(std::move(mv))
    {
    }
    
    FFuture& FFuture::operator=(const FFuture&cp)
    {
        Base::operator=(cp);
        return *this;
    }
    
    FFuture& FFuture::operator=(FFuture&&mv)
    {
        Base::operator=(std::move(mv));
        return *this;
    }
    
    FFuture::~FFuture() = default;

    std::error_code     FFuture::get_error() const
    {
        if(m_data){
            return m_data -> error;
        }
        return {};
    }
        
    std::exception_ptr  FFuture::get_exception() const
    {
        if(m_data){
            return m_data -> exception;
        }
        return {};
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    PPromise::PPromise(Ref<State> st) : Base(st)
    {
    }
    
    PPromise::PPromise(PPromise&& mv) : Base(std::move(mv))
    {
    }
    
    PPromise::~PPromise() = default;
    
    PPromise& PPromise::operator=(PPromise&&mv)
    {
        Base::operator=(std::move(mv));
        return *this;
    }

    bool        PPromise::cancelled() const noexcept
    {
        return m_data.valid() && m_data->cancel;
    }

    bool        PPromise::set(cancel_k)
    {
        if(m_data){
            m_data -> fate  = Fate::Cancelled;
            m_data  = {};
            return true;
        } else {
            return false;
        }
    }

    bool        PPromise::set(done_k)
    {
        if(m_data){
            m_data -> fate  = Fate::Done;
            m_data  = {};
            return true;
        } else {
            return false;
        }
    }

    bool        PPromise::set(std::error_code ec)
    {
        if(m_data){
            m_data -> error     = ec;
            m_data -> fate      = Fate::Error;
            m_data              = {};
            return true;
        } else {
            return false;
        }
    }

    bool        PPromise::set(std::exception_ptr ex)
    {
        if(m_data){
            m_data -> exception     = ex;
            m_data -> fate          = Fate::Exception;
            m_data                  = {};
            return true;
        } else {
            return false;
        }
    }

}
