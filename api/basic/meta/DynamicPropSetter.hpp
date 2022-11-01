////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/PropSetter.hpp>

namespace yq {

    /*! \brief Abstract dynamic property setter
    
        A dynamic property setter is one that acts on an object.  Derived property setters 
        only need to worry about the "set" capability
        
        \tparam C   object type
        \tparam T   data type
    */
    template <typename C, typename T>
    class DynamicPropSetter : public PropSetter {
    public:
    
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
        /*! Constructor
        
            \param[in] propInfo     Property that we're a setter on
            \param[in] sl           Source location that it was declared
        */
        DynamicPropSetter(PropertyInfo* propInfo, const std::source_location& sl) : PropSetter(propInfo, sl) {}
    };

    /*! \brief  Setter for member variable
    
        This is easy, an efficient way, when it's a public member variable
    */
    template <typename C, typename T>
    class IPM_PropSetter : public DynamicPropSetter<C,T> {
    public:
    
        //! Pointer type to member variable
        typedef T (C::*P);
        
        /*! \brief Constructor
            \param[in] propInfo     Property we're a setter for
            \param[in] sl           Source location that it was declared
            \param[in] pointer      The member variable pointer
        */
        IPM_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, P pointer) : DynamicPropSetter<C,T>(propInfo, sl), m_data(pointer) 
        {
            assert(pointer);
        }
        
        /*! \brief Sets the property
        
            \param[in] obj      Pointer to object
            \param[in] value    Pointer to value
        */
        virtual bool            set(void*obj, const void*value) const override
        {
            //  In correct usage, pointer checks have already been done by the PropertyInfo base's setter call
            //  therefore these don't need to be checked here.  Asserts to verify in debug
            assert(obj);
            assert(value);
            
            //  Types have already been checked, therefore C-style casts are fine
            (((C*) obj)->*m_data) =  *(const T*) value;
            return true;
        }
    
        /*! \brief Sets the property by string
        
            \param[in] obj      Pointer to object
            \param[in] value    String representation of the value
        */
        virtual bool            set(void*obj, std::string_view value) const override
        {
            assert(obj);
            return TypeInfo::parse(((C*) obj)->*m_data, value);
        }
        
    private:
        P      m_data;
    };
    
    /*! \brief Setter using member function
    
        This binds to a member function as a setter for a property.
    */
    template <typename C, typename T>
    class IFV_PropSetter : public DynamicPropSetter<C,T>{
    public:

        //! Pointer type to member function
        typedef void (C::*FN)(T);
        
        /*! \brief Constructor
            \param[in] propInfo     Property we're a setter for
            \param[in] sl           Source location that it was declared
            \param[in] function     The member function pointer
        */
        IFV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<C,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        /*! \brief Sets the property
        
            \param[in] obj      Pointer to object
            \param[in] value    Pointer to value
        */
        virtual bool            set(void* obj, const void* value) const override
        {
            //  In correct usage, pointer checks have already been done by the PropertyInfo base's setter call
            //  therefore these don't need to be checked here.  Asserts to verify in debug
            assert(obj);
            assert(value);
            (((C*) obj)->*m_function)(*(const T*) value);
            return true;
        }
        
        /*! \brief Sets the property by string
        
            \param[in] obj      Pointer to object
            \param[in] value    String representation of the value
        */
        virtual bool            set(void*obj, std::string_view value) const override
        {
            assert(obj);
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            (((C*) obj)->*m_function)(tmp);
            return true;
        }

    private:
        FN      m_function;
    };


    /*! \brief Setter using member function
    
        This binds to a member function as a setter for a property.
    */
    template <typename C, typename T>
    class IFBV_PropSetter : public DynamicPropSetter<C,T>{
    public:

        //! Pointer type to member function
        typedef bool (C::*FN)(T);
        
        /*! \brief Constructor
            \param[in] propInfo     Property we're a setter for
            \param[in] sl           Source location that it was declared
            \param[in] function     The member function pointer
        */
        IFBV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<C,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        /*! \brief Sets the property
        
            \param[in] obj      Pointer to object
            \param[in] value    Pointer to value
        */
        virtual bool            set(void* obj, const void* value) const override
        {
            //  In correct usage, pointer checks have already been done by the PropertyInfo base's setter call
            //  therefore these don't need to be checked here.  Asserts to verify in debug
            assert(obj);
            assert(value);

            //  Types have already been checked, therefore C-style casts are fine
            return (((C*) obj)->*m_function)(*(const T*) value);
        }
        
        /*! \brief Sets the property by string
        
            \param[in] obj      Pointer to object
            \param[in] value    String representation of the value
        */
        virtual bool            set(void*obj, std::string_view value) const override
        {
            assert(obj);
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            return (((C*) obj)->*m_function)(tmp);
        }

    private:
        FN      m_function;
    };

    /*! \brief Setter using member function
    
        This binds to a member function as a setter for a property.
    */
    template <typename C, typename T>
    class IFR_PropSetter : public DynamicPropSetter<C,T>{
    public:

        //! Pointer type to member function
        typedef void (C::*FN)(const T&);
        
        /*! \brief Constructor
            \param[in] propInfo     Property we're a setter for
            \param[in] sl           Source location that it was declared
            \param[in] function     The member function pointer
        */
        IFR_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<C,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        /*! \brief Sets the property
        
            \param[in] obj      Pointer to object
            \param[in] value    Pointer to value
        */
        virtual bool            set(void* obj, const void* value) const override
        {
            //  In correct usage, pointer checks have already been done by the PropertyInfo base's setter call
            //  therefore these don't need to be checked here.  Asserts to verify in debug
            assert(obj);
            assert(value);
            
            //  Types have already been checked, therefore C-style casts are fine
            (((C*) obj)->*m_function)(*(const T*) value);
            return true;
        }
        
        /*! \brief Sets the property by string
        
            \param[in] obj      Pointer to object
            \param[in] value    String representation of the value
        */
        virtual bool            set(void*obj, std::string_view value) const override
        {
            assert(obj);
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            (((C*) obj)->*m_function)(tmp);
            return true;
        }

    private:
        FN      m_function;
    };

    /*! \brief Setter using member function
    
        This binds to a member function as a setter for a property.
    */
    template <typename C, typename T>
    class IFBR_PropSetter : public DynamicPropSetter<C,T>{
    public:

        //! Pointer type to member function
        typedef bool (C::*FN)(const T&);
        
        /*! \brief Constructor
            \param[in] propInfo     Property we're a setter for
            \param[in] sl           Source location that it was declared
            \param[in] function     The member function pointer
        */
        IFBR_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<C,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        /*! \brief Sets the property
        
            \param[in] obj      Pointer to object
            \param[in] value    Pointer to value
        */
        virtual bool            set(void* obj, const void* value) const override
        {
            //  In correct usage, pointer checks have already been done by the PropertyInfo base's setter call
            //  therefore these don't need to be checked here.  Asserts to verify in debug
            assert(obj);
            assert(value);

            //  Types have already been checked, therefore C-style casts are fine
            return (((C*) obj)->*m_function)(*(const T*) value);
        }
        
        /*! \brief Sets the property by string
        
            \param[in] obj      Pointer to object
            \param[in] value    String representation of the value
        */
        virtual bool            set(void*obj, std::string_view value) const override
        {
            assert(obj);
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            return (((C*) obj)->*m_function)(tmp);
        }

    private:
        FN      m_function;
    };
}
