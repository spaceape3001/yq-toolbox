////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <stddef.h>
#include <atomic>

namespace yq {

    //  Want a way to detect for things that derive from Ref-Count & things that don't
    //  & have a helper so not everything has to be ref-count derived....
    
    template <typename T> class Ref;

    class Refable {
    public:
        template <typename T>  friend class Ref;
        
        //! increments any reference.
        //! \note Internal use, though syntax required public availability
        virtual void	incRef() const = 0;

        //! decrements any reference, potential to delete pointer
        //! \note Internal use, though syntax required public availability
        virtual void	decRef() const = 0;
    };

    /*! \brief Basic Reference Counted class
    */
    class RefCount : public Refable {
    public:
    
        //! Tests for uniqueness
        bool	unique() const 
        {
            return m_count <= 1;
        }

        //! Current ref count
        //! \note For debug info only, subject to change
        size_t	count() const 
        {
            return m_count;
        }
        
        /*! \brief Cause a memory leak
        
            This VIOLATES the pairity, ensuring that proper functions will never
            release the memory.  (Are you sure this is what you want to do?)
        */
        void    leak() { incRef(); }

    protected:

        RefCount();
        RefCount(const RefCount& copy);
        virtual ~RefCount(){}
        
        RefCount& operator=(const RefCount&) = delete;
        
        template <typename T>  friend class Ref;

            //! TREAD LIGHTLY!  Increments the reference count (can lead to orphaned memory)
        virtual void	incRef() const override;
            //! TREAD LIGHTLY!  Decrements the reference count (can lead to dangling pointers)
        virtual void	decRef() const override;

    private:
        mutable std::atomic<size_t>  m_count;
    };
    

    /*! \brief Reference Counted Pointer
     * 
     * 	\tparam	T	type of object (must derive from RefCount!)
     */
    template <typename T>
    class Ref {
    public:

        //! Default constructor (null)
        constexpr Ref() noexcept : m_ptr(nullptr) {}

        //! Takes in an object 
        Ref(T* ptr) : m_ptr(ptr) 
        {
            if(m_ptr){
                m_ptr->incRef();
            }
        }

        //! Copy constructor
        Ref(const Ref& copy) : m_ptr(copy.m_ptr)
        {
            if(m_ptr){
                m_ptr->incRef();
            }
        }
        
        //! Move constructor
        Ref(Ref&&move) noexcept
        {
            m_ptr		= move.m_ptr;
            move.m_ptr	= nullptr;
        }

        //! Destructor (decrements ref, possible deletion)
        ~Ref()
        {
            if(m_ptr){
                m_ptr->decRef();
            
                #ifdef _DEBUG
                m_ptr	= nullptr;
                #endif
            }
        }
        
        //! Copy constructor (possible deletion in LHS)
        Ref&   operator=(const Ref& rhs)
        {
            if(rhs.m_ptr != m_ptr){
                if(m_ptr)
                    m_ptr->decRef();
                m_ptr   = rhs.m_ptr;
                if(m_ptr)
                    m_ptr->incRef();
            }
            return *this;
        }
        
        //! Move constructor (possible deletion in LHS)
        Ref&   operator=(Ref&& rhs)
        {
            if(this != &rhs){
                if(m_ptr)
                    m_ptr -> decRef();
                m_ptr       = rhs.m_ptr;
                rhs.m_ptr   = nullptr;
            }
            return *this;
        }
        
        //! Assignment of pointer (possible deletion in LHS)
        Ref&	operator=(T* ptr)
        {
            if(m_ptr == ptr)
                return *this;
            if(m_ptr)
                m_ptr->decRef();
            m_ptr   = ptr;
            if(m_ptr)
                m_ptr->incRef();
            return *this;
        }
        
        //! Raw Pointer
        operator T*() noexcept
        {
            return m_ptr;
        }

        //! Raw Constant Pointer
        operator const T*() const noexcept
        {
            return m_ptr;
        }

        //! Raw Pointer
        T*			ptr() noexcept
        {
            return m_ptr;
        }

        //! Raw Constant Pointer
        const T*	ptr() const noexcept
        {
            return m_ptr;
        }

        //! Pointer accessor
        T*			operator->() noexcept
        {
            return m_ptr;
        }

        //! Constant pointer accessor
        const T*	operator->() const noexcept 
        {
            return m_ptr;
        }

        //! TRUE if valid (ie safe to access)
        bool		valid() const noexcept
        {
            return m_ptr != nullptr;
        }
        
        //! TRUE if invalid (ie, don't access!)
        bool        invalid() const
        {
            return m_ptr == nullptr;
        }
        
        //! Used for if() statements, in lieu of valid
        explicit operator bool() const noexcept
        {
            return m_ptr != nullptr;
        }

        //! Used for if() statements (ie, if(!ref){...} )
        bool		operator!() const noexcept
        {
            return m_ptr == nullptr;
        }

        bool		operator==(const Ref&rhs) const noexcept
        {
            return m_ptr == rhs.m_ptr;
        }

        bool		operator==(const T* ptr) const noexcept
        {
            return m_ptr == ptr;
        }
        
        friend bool operator==(const T* lhs, const Ref& rhs) noexcept
        {
            return lhs == rhs.m_ptr;
        }

        bool		operator!=(const Ref&rhs) const noexcept
        {
            return m_ptr != rhs.m_ptr;
        }

        bool		operator!=(const T* ptr) const noexcept
        {
            return m_ptr != ptr;
        }
        
        friend bool operator!=(const T* lhs, const Ref& rhs)
        {
            return lhs != rhs.m_ptr;
        }
        
        template <typename U>
        requires std::is_base_of_v<U,T>
        operator Ref<U>() const noexcept
        {
            static_assert(std::is_const_v<U> || !std::is_const_v<T>, "Const cast required!");
            return Ref<U>(static_cast<U*>(m_ptr));
        }
        
    private:
        T*			m_ptr;
    };
}
