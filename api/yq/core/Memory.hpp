////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/128-bit.hpp>
#include <yq/meta/TypeMeta.hpp>

#include <span>
#include <functional>
#include <type_traits>

namespace yq {

    struct ref1_t {};
    static constexpr const ref1_t REF1;
    struct copy1_t {};
    static constexpr const copy1_t COPY1;

    /*! \brief Simple memory container
    
        Data can be allocated within here, or simply be a pointer 
        somewhere else.   Default "copy" uses new/delete.  "ref" 
        doesn't allocate/deallocate, but instead trusts the client
        to keep data valid for the duration of need.
        
        This memory has the ability to define a "free" lambda
        which is used to destroy the data pointed to by the 
        given data pointer.
    */
    class Memory {
    public:
        /*! \brief Free function
        
            Yes, using std::function here
        */
        using Free = std::function<void(const void*, size_t)>;
    
        //  -------------------
        //  GETTERS/INFORMATION
        //  -------------------
            
            //! Number of bytes for the data
            size_t          bytes() const { return m_bytes; }

            //! Count of elements
            size_t          count() const;

            //! Pointer to the data
            const void*     data() const { return m_data; }

            //! TRUE if this memory has no data
            constexpr bool  empty() const noexcept { return !has_data(); }

            //! Tests for data
            constexpr bool  has_data() const noexcept { return m_data && m_bytes; }

            //! Computes MD5 checksum (or zero if empty)
            uint128_t       md5() const;

            //! Byte size of each element
            size_t          stride() const { return m_stride; }
        
            //! Element Type
            const TypeMeta* type() const { return m_type; }
        
            //! Implicit test operator
            operator        bool() const { return has_data(); }

        //  -------------------
        //  SETTERS
        //  -------------------

            /*! \brief Clears the memory
            
                This clears the memory object.  If there's a free handler,
                it will be called (if there's data).
                
                No error, no foul if the data's already cleared.  (Though a
                few CPU cycles will be wasted.)
            */
            void    clear();
            
            
            //  ----
            //  COPY
            //
            //  The copy methods do as advertised, copies the data into
            //  a new buffer.  This buffer will be kept until clear or 
            //  destruction.
        
            /*! \brief Sets a COPY of the data

                This routine copies the data pointed to in the argument 
                into a separate buffer.
                
                \tparam T           data type (normally deduced)
                \param[in] pData    pointer to the data array
                \param[in] count    Count of data items (in T)
            */
            template <typename T>
            void    copy(const T* pData, size_t count);

            /*! \brief Sets a COPY of the data
            
                This routine copies the data from the span into a 
                separate buffer.

                \tparam T           data type (normally deduced)
                \param[in] data     Span of data items (in T)
            */
            template <typename T>
            void    copy(std::span<const T> data);

            /*! \brief Sets a COPY of the data
            
                This routine copies the data from the span into a 
                separate buffer.

                \tparam T           data type (normally deduced)
                \param[in] data     Span of data items (in T)
            */
            template <typename T>
            void    copy(std::span<T> data);

            /*! \brief Sets a COPY of the data

                This routine copies the data from the given C-style
                array of data into a separate buffer.

                \tparam T           data type (normally deduced)
                \tparam N           number of items (normally deduced)
                \param[in] ptr      Static const array of data to copy in
            */
            template <typename T, size_t N>
            void    copy(const T (&ptr)[N]);

            /*! \brief Sets a COPY of the data
            
                This routine copies a *SINGLE* instance of the data 
                into a separate buffer.

                \tparam T           data type (normally deduced)
                \param[in] data     Data to import
            */
            template <typename T>
            void    copy1(const T& data);
        

            //  ----
            //  REF
            //
            //  Reference methods *don't* copy, but instead, lets the 
            //  application manage the memory.  Perhaps it's a statically
            //  globally declared array, that won't ever change.  In
            //  that case, there's no gain by copying it everywhere.  
            //  Therefore, these reference methods exist for that scenario.

            /*! \brief Sets a REFERENCE to the data
            
                This routine creates a REFERENCE to the data in the argument,
                and this data MUST remain valid for the duration of the usage.

                \tparam T           data type (normally deduced)
                \param[in] pData    pointer to the data array
                \param[in] count    Count of data items (in T)
            */
            template <typename T>
            void    ref(const T* pData, size_t count); 

            /*! \brief Sets a REFERENCE to the data

                This routine creates a REFERENCE to the data in the argument,
                and this data MUST remain valid for the duration of the usage.

                \tparam T           data type (normally deduced)
                \param[in] data     Span of data items (in T)
            */
            template <typename T>
            void    ref(std::span<const T> data); 

            /*! \brief Sets a REFERENCE to the data

                This routine creates a REFERENCE to the data in the argument,
                and this data MUST remain valid for the duration of the usage.

                \tparam T           data type (normally deduced)
                \param[in] data     Span of data items (in T)
            */
            template <typename T>
            void    ref(std::span<T> data); 

            /*! \brief Sets a REFERENCE to the data

                This routine creates a REFERENCE to the data in the argument,
                and this data MUST remain valid for the duration of the usage.

                \tparam T           data type (normally deduced)
                \tparam N           number of items (normally deduced)
                \param[in] ptr      Static const array of data to copy in
            */
            template <typename T, size_t N>
            void    ref(const T (&ptr)[N]);

            template <typename T, size_t N>
            void    ref(T (&ptr)[N]);
            
            /*! \brief Sets a REFERENCE to the data

                This routine creates a REFERENCE to the data in the argument,
                and this data MUST remain valid for the duration of the usage.

                \param[in] data     Data to REFERENCE
            */
            template <typename T>
            void    ref1(const T& data);

            // NO MOVE FOR REF (THIS IS IMPORTANT)
            template <typename T>
            void    ref1(T&&) = delete;

            //  ----
            //  SET
            //
            //  Set allows for more granular control, where T/size calculations 
            //  are done by the client instead.  These will *not* enforce that
            //  byteCount is a multiple of stride


            /*! \brief "set" for the memory
            
                This method will implicitly CLEAR the data.
                
                \note while this is generally intended for internal API use, it's 
                tolerated to be public.
                
                \param[in] pData        Pointer to data
                \param[in] byteCount    Bytes of data
            */
            void    set(const void* pData, size_t byteCount); 

            /*! \brief "set" for the memory
            
                This method will implicitly CLEAR the data.
                
                \note while this is generally intended for internal API use, it's 
                tolerated to be public.
                
                \param[in] pData        Pointer to data
                \param[in] byteCount    Bytes of data
                \param[in] stride       Size of the element
            */
            void    set(const void* pData, size_t byteCount, size_t stride); 

            /*! \brief "set" for the memory
            
                This method will implicitly CLEAR the data.
                
                \note while this is generally intended for internal API use, it's 
                tolerated to be public.
                
                \param[in] pData        Pointer to data
                \param[in] byteCount    Bytes of data
                \param[in] type         TypeMeta for the data
            */
            void    set(const void* pData, size_t byteCount, const TypeMeta& type); 

            /*! \brief "set" for the memory
            
                This method will implicitly CLEAR the data.
                
                \note while this is generally intended for internal API use, it's 
                tolerated to be public.
                
                \param[in] pData        Pointer to data
                \param[in] byteCount    Bytes of data
                \param[in] Free         Lambda for clearing/freeing the data, in case of memory allocation. 
            */
            void    set(const void* pData, size_t byteCount, Free&& free); 

            /*! \brief "set" for the memory
            
                This method will implicitly CLEAR the data.
                
                \note while this is generally intended for internal API use, it's 
                tolerated to be public.
                
                \param[in] pData        Pointer to data
                \param[in] byteCount    Bytes of data
                \param[in] stride       Size of the element
                \param[in] Free         Lambda for clearing/freeing the data, in case of memory allocation. 
            */
            void    set(const void* pData, size_t byteCount, size_t stride, Free&& free); 

            /*! \brief "set" for the memory
            
                This method will implicitly CLEAR the data.
                
                \note while this is generally intended for internal API use, it's 
                tolerated to be public.
                
                \param[in] pData        Pointer to data
                \param[in] byteCount    Bytes of data
                \param[in] type         TypeMeta for the data
                \param[in] Free         Lambda for clearing/freeing the data, in case of memory allocation. 
            */
            void    set(const void* pData, size_t byteCount, const TypeMeta& type, Free&&free); 

        //  -------------------
        //  CONSTRUCTION/DESTRUCTION
        //  -------------------

        //! Default constructor, zeros everything
        Memory();
        
        
        //  Gah... compiler's having issues with argument forwarding, 
        //  therefore we have to list these *ALL* :(

        //! Constructs by data copy

        template <typename T>
        Memory(copy_k, const T* pData, size_t count) : Memory()
        {
            copy(pData, count);
        }
        
        template <typename T, typename A>
        Memory(copy_k, const std::vector<T, A>& data)
        {
            copy(data.data(), data.size());
        }

        template <typename T>
        Memory(copy_k, std::span<const T> data) : Memory()
        {
            copy(data);
        }

        template <typename T>
        Memory(copy_k, std::span<T> data) : Memory()
        {
            copy(data);
        }

        template <typename T, size_t N>
        Memory(copy_k, const T (&ptr)[N]) : Memory()
        {
            copy<T,N>(ptr);
        }

        template <typename T>
        Memory(copy1_t, const T& data) : Memory()
        {
            copy1(data);
        }


        template <typename T>
        Memory(ref_k, const T* pData, size_t count) : Memory()
        {
            ref(pData, count);
        }

        template <typename T, typename A>
        Memory(ref_k, const std::vector<T, A>& data)
        {
            ref(data.data(), data.size());
        }

        template <typename T>
        Memory(ref_k, std::span<T> data) : Memory()
        {
            ref(data);
        }

        template <typename T>
        Memory(ref_k, std::span<const T> data) : Memory()
        {
            ref(data);
        }

        template <typename T, size_t N>
        Memory(ref_k, const T (&ptr)[N]) : Memory()
        {
            ref<T,N>(ptr);
        }

        template <typename T, size_t N>
        Memory(ref_k, T (&ptr)[N]) : Memory()
        {
            ref<T,N>(ptr);
        }

        template <typename T>
        Memory(ref1_t, const T& data) : Memory()
        {
            ref1(data);
        }

        template <typename T>
        Memory(ref1_t, T&&) = delete;

        Memory(set_k, const void* pData, size_t byteCount); 

        Memory(set_k, const void* pData, size_t byteCount, size_t stride); 

        Memory(set_k, const void* pData, size_t byteCount, const TypeMeta& type); 

        Memory(set_k, const void* pData, size_t byteCount, Free&& free); 

        Memory(set_k, const void* pData, size_t byteCount, size_t stride, Free&& free); 

        Memory(set_k, const void* pData, size_t byteCount, const TypeMeta& type, Free&&free); 


        //! Move constructor
        Memory(Memory&& mv);

        //! Move operator
        Memory& operator=(Memory&&);
        
        //! Destructor
        ~Memory();
        
        //  -------------------
        //  -------------------

    private:
    
        Free            m_free;         // 32
        const void*     m_data;
        size_t          m_bytes;
        const TypeMeta* m_type;
        size_t          m_stride;       // 64

        //! Copying is *NOT* allowed
        Memory(const Memory&) = delete;
        
        //! Copying is *NOT* allowed
        Memory& operator=(const Memory&) = delete;
        
        //! Internal "Free" execution
        void            _free();
        
        //! Internal zero'ing of data memembers
        void            _zap();
        
        //! Internal move
        void            _move(Memory&&);
    
        void    _set(const void* pData, size_t byteCount, const TypeMeta* type, size_t stride, Free&& free); 

        template <typename T>
        static const TypeMeta* metaPtr()
        {
            if constexpr (is_type_v<T>)
                return &meta_unsafe<T>();
            return nullptr;
        }
    };

    template <typename T>
    void    Memory::copy(const T*p, size_t n)
    {
        //static_assert(std::is_trivial_v<T>, "Can only set with trivial types!");
        if(!p || !n)
            return ;
            
        T*    ndata   = new T[n];
        std::copy(p, p+n, ndata);
        _set(ndata, n * sizeof(T), metaPtr<T>(), sizeof(T), [](const void* p2, size_t sz) {
            delete[] ((const T*) p2);
        });
    }

    template <typename T>
    void    Memory::copy(std::span<T> d)
    {
        copy(d.data(), d.size());
    }

    template <typename T>
    void    Memory::copy(std::span<const T> d)
    {
        copy(d.data(), d.size());
    }

    template <typename T, size_t N>
    void    Memory::copy(const T (&ptr)[N])
    {
        copy(ptr, N);
    }
    

    template <typename T>
    void    Memory::copy1(const T&v)
    {
        //static_assert(std::is_trivially_copyable_v<T>, "Can only set with trivial types!");
        _set( new T(v), sizeof(T), metaPtr<T>(), sizeof(T), [](const void*p, size_t){
            delete ((const T*) p);
        });
    }
    
    template <typename T>
    void    Memory::ref(const T* p, size_t cnt)
    {
        //static_assert(std::is_trivially_copyable_v<T>, "Can only set with trivial types!");
        _set(p, cnt*sizeof(T), metaPtr<T>(), sizeof(T), {});
    }

    template <typename T>
    void    Memory::ref(std::span<const T>sp)
    {
        ref(sp.data(), sp.size());
    }

    template <typename T>
    void    Memory::ref(std::span<T>sp)
    {
        ref(sp.data(), sp.size());
    }

    template <typename T, size_t N>
    void    Memory::ref(const T (&ptr)[N])
    {
        ref(ptr, N);
    }

    template <typename T, size_t N>
    void    Memory::ref(T (&ptr)[N])
    {
        ref(ptr, N);
    }

    template <typename T>
    void    Memory::ref1(const T& p)
    {
        //static_assert(std::is_trivially_copyable_v<T>, "Can only set with trivial types!");
        _set(&p, sizeof(T), metaPtr<T>(), sizeof(T), {});
    }

};

