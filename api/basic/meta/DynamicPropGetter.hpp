////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/PropGetter.hpp>

namespace yq {
    /*! \brief Abstract getter of type on class/struct
    
        This is an abstract getter bound to a specific data type/class.  Derived getters from this class only
        need to implement the "GET" routine and the constructor.

        \tparam T   variable data type
        \tparam C   bound class/struct's meta info
    */
    template <typename C, typename T>
    class DynamicPropGetter : public PropGetter {
    public:
    
        static_assert(InfoBinder<T>::Defined, "Type must be meta defined!");
        static_assert(is_defined_v<T>, "Type must be meta defined!");

        //! Data meta type
        virtual const Meta&     data() const override
        {
            return meta<T>();
        }

        //! Object meta type
        virtual const Meta&     object() const override
        {
            return meta<C>();
        }

    protected:
    
        /*! \brief Constructor
            This constructs a dynamic prop getter.
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
        */
        DynamicPropGetter(PropertyInfo* propInfo, const std::source_location& sl) : PropGetter(propInfo, sl) 
        {
        }
    };
    

    /*! \brief PropGetter for a member variable
    
        PropGetter for the scenario of a member variable on an object.
    */
    template <typename C, typename T>
    class IPM_PropGetter : public DynamicPropGetter<C,T> {
    public:
    
        //! Member variable pointer
        typedef const T (C::*P);
        
        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] pointer  Pointer to the member variable
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        IPM_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, P pointer) : DynamicPropGetter<C,T>(propInfo, sl), m_data(pointer) 
        {
            assert(pointer);
        }

    private:
    
        /*! \brief Gets the value of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            get(void*dst, const void*obj) const override
        {
            assert(dst);
            assert(obj);
            *(T*) dst   = (((const C*) obj)->*m_data);
            return true;
        }

        /*! \brief Prints the object's value to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::print(((const C*) obj)->*m_data, str);
            return true;
        }
        
        /*! \brief Writes the object's value to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::write(((const C*) obj)->*m_data, str);
            return true;
        }
        
        P       m_data;
    };
    
    /*! \brief PropGetter for a member getter (of return)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename C, typename T>
    class IFV_PropGetter : public DynamicPropGetter<C,T> {
    public:
    
        //! Member function pointer
        typedef T (C::*FN)() const;

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        IFV_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<C,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool        get(void* dst, const void* obj) const override
        {
            assert(dst);
            assert(obj);
            *(T*) dst   = (((const C*) obj)->*m_function)();
            return true;
        }

        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::print((((const C*) obj)->*m_function)(), str);
            return true;
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::write((((const C*) obj)->*m_function)(), str);
            return true;
        }
        
        FN      m_function;
    };
    
    
    /*! \brief PropGetter for a member getter (of const return reference)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename C, typename T>
    class IFR_PropGetter : public DynamicPropGetter<C,T> {
    public:
        typedef const T& (C::*FN)() const;

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        IFR_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<C,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool        get(void* dst, const void* obj) const override
        {
            assert(dst);
            assert(obj);
            *(T*) dst   = (((const C*) obj)->*m_function)();
            return true;
        }
        
        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::print((((const C*) obj)->*m_function)(), str);
            return true;
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::write((((const C*) obj)->*m_function)(), str);
            return true;
        }

        FN      m_function;
    };

    /*! \brief PropGetter for a member getter (of parameter return)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename C, typename T>
    class IFP_PropGetter : public DynamicPropGetter<C,T> {
    public:

        //! Member function pointer
        typedef void (C::*FN)(T&) const;

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        IFP_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<C,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool        get(void* dst, const void* obj) const override
        {
            assert(dst);
            assert(obj);
            (((const C*) obj)->*m_function)(*(T*) dst);
            return true;
        }
        
        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            T   data;
            (((const C*) obj)->*m_function)(data);
            TypeInfo::print(data, str);
            return true;
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            T   data;
            (((const C*) obj)->*m_function)(data);
            TypeInfo::write(data, str);
            return true;
        }

        FN      m_function;
    };

    /*! \brief PropGetter for a member getter (of parameter return)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename C, typename T>
    class IFPB_PropGetter : public DynamicPropGetter<C,T> {
    public:

        //! Member function pointer
        typedef bool (C::*FN)(T&) const;

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        IFPB_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<C,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool        get(void* dst, const void* obj) const override
        {
            assert(dst);
            assert(obj);
            return (((const C*) obj)->*m_function)(*(T*) dst);
        }
        
        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            T   data;
            if(!(((const C*) obj)->*m_function)(data))
                return false;
            TypeInfo::print(data, str);
            return true;
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            T   data;
            if(!(((const C*) obj)->*m_function)(data))
                return false;
            TypeInfo::write(data, str);
            return true;
        }

        FN      m_function;
    };

    /*! \brief PropGetter for a member getter (of const return reference)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename C, typename T>
    class ZFRV_PropGetter : public DynamicPropGetter<C,T> {
    public:
        typedef T (*FN)(const C&);

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        ZFRV_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<C,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool        get(void* dst, const void* obj) const override
        {
            assert(dst);
            assert(obj);
            *(T*) dst   = (*m_function)((const C*) obj);
            return true;
        }
        
        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::print((*m_function)((const C*) obj), str);
            return true;
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::write((*m_function)((const C*) obj), str);
            return true;
        }

        FN      m_function;
    };

    /*! \brief PropGetter for a member getter (of const return reference)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename C, typename T>
    class ZFVV_PropGetter : public DynamicPropGetter<C,T> {
    public:
        typedef T (*FN)(C);

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        ZFVV_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<C,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool        get(void* dst, const void* obj) const override
        {
            assert(dst);
            assert(obj);
            *(T*) dst   = (*m_function)((const C*) obj);
            return true;
        }
        
        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::print((*m_function)((const C*) obj), str);
            return true;
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::write((*m_function)((const C*) obj), str);
            return true;
        }

        FN      m_function;
    };

    /*! \brief PropGetter for a member getter (of const return reference)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename C, typename T>
    class ZFRR_PropGetter : public DynamicPropGetter<C,T> {
    public:
        typedef const T& (*FN)(const C&);

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        ZFRR_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<C,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool        get(void* dst, const void* obj) const override
        {
            assert(dst);
            assert(obj);
            *(T*) dst   = (*m_function)((const C*) obj);
            return true;
        }
        
        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::print((*m_function)((const C*) obj), str);
            return true;
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::write((*m_function)((const C*) obj), str);
            return true;
        }

        FN      m_function;
    };

    /*! \brief PropGetter for a member getter (of const return reference)
    
        PropGetter for the scenario of a member function on an object.
    */
    template <typename C, typename T>
    class ZFVR_PropGetter : public DynamicPropGetter<C,T> {
    public:
        typedef const T& (*FN)(C);

        /*! \brief Constructor
            
            \param[in] propInfo The property we're being associated with.
            \param[in] sl       Source location where this property getter is being associated at.
            \param[in] function Member function to get the property value
        
            \note This is only public to avoid thorny friend statements.  Don't create it directly outside of the meta-classes.
        */
        ZFVR_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<C,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
    private:
        /*! \brief Gets the property of the object
            \param[out] dst Destination pointer, assumed to be mapped correctly
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool        get(void* dst, const void* obj) const override
        {
            assert(dst);
            assert(obj);
            *(T*) dst   = (*m_function)((const C*) obj);
            return true;
        }
        
        /*! \brief Prints the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::print((*m_function)((const C*) obj), str);
            return true;
        }
        
        /*! \brief Writes the object's property to the given stream.
            \param[out] str Destination stream
            \param[in]  obj Object pointer, assumed to be mapped correctly
            \return TRUE (always)
        */
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::write((*m_function)((const C*) obj), str);
            return true;
        }

        FN      m_function;
    };
}
