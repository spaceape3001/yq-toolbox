////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/PropGetter.hpp>
#include <yq/meta/TypeMeta.hpp>
#include <yq/core/StreamOps.hpp>

namespace yq {

    /*! \brief Abstract static/global getter of type
    
        This is an abstract getter bound to a specific data type.  Derived getters from this class only
        need to implement the "GET", "PRINT" & "WRITE" routines and the constructor.
        
        \tparam T   data type being bound to
    */
    template <typename T>
    class StaticPropGetter : public PropGetter {
    public:
    
        /*! \brief Data type for this getter
        */
        virtual const Meta&     data() const override
        {
            return meta<T>();
        }

        /*! \brief Invalid object type
        
            As there's no object for the data, it's always invalid.
        */
        virtual const Meta&     object() const override
        {
            return invalid();
        }

    protected:
        
        /*! \brief Constructor
        
            \param[in] propInfo Property information
            \param[in] sl       Source location
        */
        StaticPropGetter(PropertyMeta* propInfo, const std::source_location& sl) : PropGetter(propInfo, sl) 
        {
        }
    };
    
    /*! \brief Getter for an explicit pointer
    
        This maintains an explicit pointer to the global variable, 
        and binds it to the property getter.
    */
    template <typename T>
    class XPV_PropGetter : public StaticPropGetter<T> {
    public:
    
        //! Variable pointer (always const in the geters)
        typedef const T* P;
        
        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] pointer  Pointer to variable
        */
        XPV_PropGetter(PropertyMeta*propInfo, const std::source_location& sl, P pointer) : StaticPropGetter<T>(propInfo, sl), m_data(pointer) 
        {
            assert(pointer);
        }
    
    private:
    
        /*! \brief Gets the data
            \param[out] dst Pointer to the destination data, must be valid
            \note The const void* object pointer is ignored.
            \return Always TRUE
        */
        virtual std::error_code  get(void*dst, const void*) const override
        {
            assert(dst);
            if(!dst)
                return errors::null_destination();
            *(T*) dst   = *m_data;
            return std::error_code();
        }

        /*! \brief Prints the data
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the TypeMeta print function returned true
        */
        virtual std::error_code     print(Stream&str, const void*) const override
        {
            return TypeMeta::print(*m_data, str);
        }
        
        /*! \brief Writes the data for data I/O purposes
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the TypeMeta write function returned true
        */
        virtual std::error_code      write(Stream&str, const void*) const override
        {
            return TypeMeta::write(*m_data, str);
        }

        P      m_data;
    };
    
    /*! \brief Variable getter using function
    
        This implements the variable by ways of a function pointer.
    */
    template <typename T>
    class XFV_PropGetter : public StaticPropGetter<T> {
    public:
    
        //! Function pointer
        typedef T (*FN)();

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] function Function pointer
        */
        XFV_PropGetter(PropertyMeta* propInfo, const std::source_location& sl, FN function) : StaticPropGetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }

    private:
        /*! \brief Gets the data
            \param[out] dst Pointer to the destination data, must be valid
            \note The const void* object pointer is ignored.
            \return Always TRUE
        */
        virtual std::error_code    get(void* dst, const void*) const  override
        {
            assert(dst);
            if(!dst)
                return errors::null_destination();
            *(T*) dst   = std::move(m_function());
            return std::error_code();
        }

        /*! \brief Prints the data
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the TypeMeta print function returned true
        */
        virtual std::error_code     print(Stream&str, const void*) const override
        {
            return TypeMeta::print(m_function(), str);
        }
        
        /*! \brief Writes the data for data I/O purposes
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the TypeMeta write function returned true
        */
        virtual std::error_code     write(Stream&str, const void*) const override
        {
            return TypeMeta::write(m_function(), str);
        }

        FN      m_function;
    };
    
    /*! \brief Variable getter using function
    
        This implements the variable by ways of a function pointer.
    */
    template <typename T>
    class XFR_PropGetter : public StaticPropGetter<T> {
    public:
        //! Function pointer
        typedef T& (*FN)();

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] function Function pointer
        */
        XFR_PropGetter(PropertyMeta* propInfo, const std::source_location& sl, FN function) : StaticPropGetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
    
    private:

        /*! \brief Gets the data
            \param[out] dst Pointer to the destination data, must be valid
            \note The const void* object pointer is ignored.
            \return Always TRUE
        */
        virtual std::error_code    get(void* dst, const void*) const  override
        {
            assert(dst);
            if(!dst)
                return errors::null_destination();
            *(T*) dst   = m_function();
            return std::error_code();
        }

        /*! \brief Prints the data
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the TypeMeta print function returned true
        */
        virtual std::error_code print(Stream&str, const void*) const override
        {
            return TypeMeta::print(m_function(), str);
        }
        
        /*! \brief Writes the data for data I/O purposes
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the TypeMeta write function returned true
        */
        virtual std::error_code write(Stream&str, const void*) const override
        {
            return TypeMeta::write(m_function(), str);
        }

        FN      m_function;
    };

    /*! \brief Variable getter using function
    
        This implements the variable by ways of a function pointer.
    */
    template <typename T>
    class XFCR_PropGetter : public StaticPropGetter<T> {
    public:

        //! Function pointer
        typedef const T& (*FN)();

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] function Function pointer
        */
        XFCR_PropGetter(PropertyMeta* propInfo, const std::source_location& sl, FN function) : StaticPropGetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
    private:

        /*! \brief Gets the data
            \param[out] dst Pointer to the destination data, must be valid
            \note The const void* object pointer is ignored.
            \return Always TRUE
        */
        virtual std::error_code get(void* dst, const void*) const  override
        {
            assert(dst);
            if(!dst)
                return errors::null_destination();
            *(T*) dst   = m_function();
            return std::error_code();
        }

        /*! \brief Prints the data
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the TypeMeta print function returned true
        */
        virtual std::error_code print(Stream&str, const void*) const override
        {
            return TypeMeta::print(m_function(), str);
        }
        
        /*! \brief Writes the data for data I/O purposes
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the TypeMeta write function returned true
        */
        virtual std::error_code write(Stream&str, const void*) const override
        {
            return TypeMeta::write(m_function(), str);
        }

        FN      m_function;
    };

    /*! \brief Variable getter using function
    
        This implements the variable by ways of a function pointer.
    */
    template <typename T>
    class XFVR_PropGetter : public StaticPropGetter<T> {
    public:

        //! Function pointer
        typedef void (*FN)(T&);

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] function Function pointer
        */
        XFVR_PropGetter(PropertyMeta* propInfo, const std::source_location& sl, FN function) : StaticPropGetter<T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }

    private:

        /*! \brief Gets the data
            \param[out] dst Pointer to the destination data, must be valid
            \note The const void* object pointer is ignored.
            \return Always TRUE
        */
        virtual std::error_code get(void* dst, const void*) const override
        {
            assert(dst);
            if(!dst)
                return errors::null_destination();
            m_function(*(T*) dst);
            return std::error_code();
        }

        /*! \brief Prints the data
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the TypeMeta print function returned true
        */
        virtual std::error_code print(Stream&str, const void*) const override
        {
            T   tmp;
            m_function(tmp);
            return TypeMeta::print(tmp, str);
        }
        
        /*! \brief Writes the data for data I/O purposes
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the TypeMeta write function returned true
        */
        virtual std::error_code write(Stream&str, const void*) const override
        {
            T   tmp;
            m_function(tmp);
            return TypeMeta::print(tmp, str);
        }

        FN      m_function;
    };
    
    /*! \brief Variable getter using function
    
        This implements the variable by ways of a function pointer.
    */
    template <typename T>
    class XFBR_PropGetter : public StaticPropGetter<T> {
    public:

        //! Function pointer
        typedef bool (*FN)(T&);

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] function Function pointer
        */
        XFBR_PropGetter(PropertyMeta* propInfo, const std::source_location& sl, FN function) : StaticPropGetter<T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:

        /*! \brief Gets the data
            \param[out] dst Pointer to the destination data, must be valid
            \note The const void* object pointer is ignored.
            \return TRUE if the function returns true
        */
        virtual std::error_code get(void* dst, const void*) const override
        {
            if(!dst)
                return errors::null_destination();
            if(!m_function(*(T*) dst))
                return errors::getter_failed();
            return std::error_code();
        }

        /*! \brief Prints the data
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the getter function AND TypeMeta print function returned true
        */
        virtual std::error_code print(Stream&str, const void*) const override
        {
            T   tmp;
            if(!m_function(tmp))
                return errors::getter_failed();
            return TypeMeta::print(tmp, str);
        }
        
        /*! \brief Writes the data for data I/O purposes
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the getter function AND TypeMeta write function returned true
        */
        virtual std::error_code write(Stream&str, const void*) const override
        {
            T   tmp;
            if(!m_function(tmp))
                return errors::getter_failed();
            return TypeMeta::print(tmp, str);
        }

        FN      m_function;
    };
    
    /*! \brief Variable getter using function
    
        This implements the variable by ways of a function pointer.
    */
    template <typename T>
    class XFER_PropGetter : public StaticPropGetter<T> {
    public:

        //! Function pointer
        typedef std::error_code (*FN)(T&);

        /*! \brief Constructor
        
            \note Don't use, let the helpers maintain this.
            \param[in] propInfo Property information
            \param[in] sl       Source location
            \param[in] function Function pointer
        */
        XFER_PropGetter(PropertyMeta* propInfo, const std::source_location& sl, FN function) : StaticPropGetter<T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:

        /*! \brief Gets the data
            \param[out] dst Pointer to the destination data, must be valid
            \note The const void* object pointer is ignored.
            \return TRUE if the function returns true
        */
        virtual std::error_code get(void* dst, const void*) const override
        {
            if(!dst)
                return errors::null_destination();
            return m_function(*(T*) dst);
        }

        /*! \brief Prints the data
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the getter function AND TypeMeta print function returned true
        */
        virtual std::error_code print(Stream&str, const void*) const override
        {
            T   tmp;
            std::error_code ec = m_function(tmp);
            if(ec != std::error_code())
                return ec;
            return TypeMeta::print(tmp, str);
        }
        
        /*! \brief Writes the data for data I/O purposes
            \param[out] str Stream to print to.
            \note The const void* object pointer is ignored.
            \return TRUE if the getter function AND TypeMeta write function returned true
        */
        virtual std::error_code write(Stream&str, const void*) const override
        {
            T   tmp;
            std::error_code ec = m_function(tmp);
            if(ec != std::error_code())
                return ec;
            return TypeMeta::print(tmp, str);
        }

        FN      m_function;
    };
}
