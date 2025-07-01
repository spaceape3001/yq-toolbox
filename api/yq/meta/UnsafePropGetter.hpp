////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Object.hpp>
#include <yq/meta/DynamicPropGetter.hpp>

namespace yq {

    /*! \brief PropGetter for a member variable
    
        PropGetter for the scenario of a member variable on an object.
    */
    template <typename O, typename C, typename T>
    class UIPM_PropGetter : public DynamicPropGetter<O,T> {
    public:
    
        //! Member variable pointer
        typedef const T (C::*P);
        
        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] pointer  Pointer to the member variable
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        UIPM_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, P pointer) : DynamicPropGetter<O,T>(propInfo, sl), m_data(pointer) 
        {
            assert(pointer);
        }

    private:
    
        /*! \brief Gets the value of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code get(void*dst, const void*p) const override
        {
            assert(dst);
            if(!dst)
                return errors::null_destination();
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();
            *(T*) dst   = c->*m_data;
            return std::error_code();
        }

        /*! \brief Prints the object's value to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code print(Stream&str, const void* p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();
            return TypeMeta::print(c->*m_data, str);
        }
        
        /*! \brief Writes the object's value to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code write(Stream&str, const void*p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();
            return TypeMeta::write(c->*m_data, str);
        }
        
        P       m_data;
    };
    
    /*! \brief PropGetter for a member getter (of return)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename O, typename C, typename T>
    class UIFV_PropGetter : public DynamicPropGetter<O,T> {
    public:
    
        //! Member function pointer
        typedef T (C::*FN)() const;

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        UIFV_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<O,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code get(void* dst, const void* p) const override
        {
            assert(dst);
            if(!dst)
                return errors::null_destination();
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            *(T*) dst   = (c->*m_function)();
            return std::error_code();
        }

        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code print(Stream&str, const void*p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            return TypeMeta::print((c->*m_function)(), str);
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code write(Stream&str, const void*p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();
            return TypeMeta::write((c->*m_function)(), str);
        }
        
        FN      m_function;
    };
    
    
    /*! \brief PropGetter for a member getter (of const return reference)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename O, typename C, typename T>
    class UIFR_PropGetter : public DynamicPropGetter<O,T> {
    public:
        typedef const T& (C::*FN)() const;

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        UIFR_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<O,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code get(void* dst, const void* p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            *(T*) dst   = (c->*m_function)();
            return std::error_code();
        }
        
        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code print(Stream&str, const void*p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();
            return TypeMeta::print((c->*m_function)(), str);
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code write(Stream&str, const void*p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();
            return TypeMeta::write((c->*m_function)(), str);
        }

        FN      m_function;
    };

    /*! \brief PropGetter for a member getter (of parameter return)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename O, typename C, typename T>
    class UIFP_PropGetter : public DynamicPropGetter<O,T> {
    public:

        //! Member function pointer
        typedef void (C::*FN)(T&) const;

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        UIFP_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<O,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code get(void* dst, const void* p) const override
        {
            assert(dst);
            if(!dst)
                return errors::null_destination();
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            (c->*m_function)(*(T*) dst);
            return std::error_code();
        }
        
        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code print(Stream&str, const void*p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            T   data;
            (c->*m_function)(data);
            return TypeMeta::print(data, str);
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code write(Stream&str, const void*p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            T   data;
            (c->*m_function)(data);
            return TypeMeta::write(data, str);
        }

        FN      m_function;
    };

    /*! \brief PropGetter for a member getter (of parameter return)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename O, typename C, typename T>
    class UIFPB_PropGetter : public DynamicPropGetter<O,T> {
    public:

        //! Member function pointer
        typedef bool (C::*FN)(T&) const;

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        UIFPB_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<O,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code get(void* dst, const void* p) const override
        {
            assert(dst);
            if(!dst)
                return errors::null_destination();
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();
            if(!(c->*m_function)(*(T*) dst))
                return errors::getter_failed();
            return std::error_code();
        }
        
        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code print(Stream&str, const void*p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            T   data;
            if(!(c->*m_function)(data))
                return errors::getter_failed();
            return TypeMeta::print(data, str);
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual std::error_code write(Stream&str, const void*p) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            const Object*  obj  = (const Object*) p;
            const C*        c   = dynamic_cast<const C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            T   data;
            if(!(c->*m_function)(data))
                return errors::getter_failed();
            return TypeMeta::write(data, str);
        }

        FN      m_function;
    };
}
