////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Object.hpp>
#include <yq/meta/DynamicPropSetter.hpp>

namespace yq {
    /*! \brief  Setter for member variable
    
        This is easy, an efficient way, when it's a public member variable
    */
    template <typename O, typename C, typename T>
    class UIPM_PropSetter : public DynamicPropSetter<O,T> {
    public:
    
        //! Pointer type to member variable
        typedef T (C::*P);
        
        /*! \brief Constructor
            \param[in] propInfo     Property we're a setter for
            \param[in] sl           Source location that it was declared
            \param[in] pointer      The member variable pointer
            \note Consumers shouldn't be directly creating these, it's public to avoid thorny friend statements.
        */
        UIPM_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, P pointer) : DynamicPropSetter<O,T>(propInfo, sl), m_data(pointer) 
        {
            assert(pointer);
        }
        
    private:
        /*! \brief Sets the property
        
            \param[in] obj      Pointer to object
            \param[in] value    Pointer to value
        */
        virtual std::error_code      set(void*p, const void*value) const override
        {
            //  In correct usage, pointer checks have already been done by the PropertyInfo base's setter call
            //  therefore these don't need to be checked here.  Asserts to verify in debug
            assert(p);
            if(!p)
                return errors::null_object();
            Object*  obj  = (Object*) p;
            C*        c   = dynamic_cast<C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            assert(value);
            if(!value)
                return errors::null_value();
            
            //  Types have already been checked, therefore C-style casts are fine
            (c->*m_data) =  *(const T*) value;
            return std::error_code();
        }
    
        /*! \brief Sets the property by string
        
            \param[in] obj      Pointer to object
            \param[in] value    String representation of the value
        */
        virtual std::error_code set(void*p, std::string_view value) const override
        {
            //  In correct usage, pointer checks have already been done by the PropertyInfo base's setter call
            //  therefore these don't need to be checked here.  Asserts to verify in debug
            assert(p);
            if(!p)
                return errors::null_object();
            Object*  obj  = (Object*) p;
            C*        c   = dynamic_cast<C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            return TypeMeta::parse(c->*m_data, value);
        }
        
        P      m_data;
    };
    
    /*! \brief Setter using member function
    
        This binds to a member function as a setter for a property.
    */
    template <typename O, typename C, typename T>
    class UIFV_PropSetter : public DynamicPropSetter<O,T>{
    public:

        //! Pointer type to member function
        typedef void (C::*FN)(T);
        
        /*! \brief Constructor
            \param[in] propInfo     Property we're a setter for
            \param[in] sl           Source location that it was declared
            \param[in] function     The member function pointer
            \note Consumers shouldn't be directly creating these, it's public to avoid thorny friend statements.
        */
        UIFV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<O,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
    private:
        /*! \brief Sets the property
        
            \param[in] obj      Pointer to object
            \param[in] value    Pointer to value
        */
        virtual std::error_code set(void* p, const void* value) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            Object*  obj  = (Object*) p;
            C*        c   = dynamic_cast<C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();
                
            assert(value);
            if(!value)
                return errors::null_value();

            (c->*m_function)(*(const T*) value);
            return std::error_code();
        }
        
        /*! \brief Sets the property by string
        
            \param[in] obj      Pointer to object
            \param[in] value    String representation of the value
        */
        virtual std::error_code set(void*p, std::string_view value) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            Object*  obj  = (Object*) p;
            C*        c   = dynamic_cast<C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            T   tmp;
            std::error_code ec = TypeMeta::parse(tmp, value);
            if(ec != std::error_code())
                return ec;
            (c->*m_function)(tmp);
            return std::error_code();
        }

        FN      m_function;
    };


    /*! \brief Setter using member function
    
        This binds to a member function as a setter for a property.
    */
    template <typename O, typename C, typename T>
    class UIFBV_PropSetter : public DynamicPropSetter<O,T>{
    public:

        //! Pointer type to member function
        typedef bool (C::*FN)(T);
        
        /*! \brief Constructor
            \param[in] propInfo     Property we're a setter for
            \param[in] sl           Source location that it was declared
            \param[in] function     The member function pointer
            \note Consumers shouldn't be directly creating these, it's public to avoid thorny friend statements.
        */
        UIFBV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<O,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
    private:
        /*! \brief Sets the property
        
            \param[in] obj      Pointer to object
            \param[in] value    Pointer to value
        */
        virtual std::error_code set(void* p, const void* value) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            Object*  obj  = (Object*) p;
            C*        c   = dynamic_cast<C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            assert(value);
            if(!value)
                return errors::null_value();

            //  Types have already been checked, therefore C-style casts are fine
            if(!(c->*m_function)(*(const T*) value))
                return errors::setter_failed();
            return std::error_code();
        }
        
        /*! \brief Sets the property by string
        
            \param[in] obj      Pointer to object
            \param[in] value    String representation of the value
        */
        virtual std::error_code set(void*p, std::string_view value) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            Object*  obj  = (Object*) p;
            C*        c   = dynamic_cast<C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            T   tmp;
            std::error_code ec = TypeMeta::parse(tmp, value);
            if(ec != std::error_code())
                return ec;
            if(! (c->*m_function)(tmp))
                return errors::setter_failed();
            return std::error_code();
        }

        FN      m_function;
    };

    /*! \brief Setter using member function
    
        This binds to a member function as a setter for a property.
    */
    template <typename O, typename C, typename T>
    class UIFR_PropSetter : public DynamicPropSetter<O,T>{
    public:

        //! Pointer type to member function
        typedef void (C::*FN)(const T&);
        
        /*! \brief Constructor
            \param[in] propInfo     Property we're a setter for
            \param[in] sl           Source location that it was declared
            \param[in] function     The member function pointer
            \note Consumers shouldn't be directly creating these, it's public to avoid thorny friend statements.
        */
        UIFR_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<O,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
    private:
        /*! \brief Sets the property
        
            \param[in] obj      Pointer to object
            \param[in] value    Pointer to value
        */
        virtual std::error_code set(void* p, const void* value) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            Object*  obj  = (Object*) p;
            C*        c   = dynamic_cast<C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            assert(value);
            if(!value)
                return errors::null_value();
            
            //  Types have already been checked, therefore C-style casts are fine
            (c->*m_function)(*(const T*) value);
            return std::error_code();
        }
        
        /*! \brief Sets the property by string
        
            \param[in] obj      Pointer to object
            \param[in] value    String representation of the value
        */
        virtual std::error_code set(void*p, std::string_view value) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            Object*  obj  = (Object*) p;
            C*        c   = dynamic_cast<C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            T   tmp;
            std::error_code ec = TypeMeta::parse(tmp, value);
            if(ec != std::error_code())
                return ec;
            (c->*m_function)(tmp);
            return std::error_code();
        }

        FN      m_function;
    };

    /*! \brief Setter using member function
    
        This binds to a member function as a setter for a property.
    */
    template <typename O, typename C, typename T>
    class UIFBR_PropSetter : public DynamicPropSetter<O,T>{
    public:

        //! Pointer type to member function
        typedef bool (C::*FN)(const T&);
        
        /*! \brief Constructor
            \param[in] propInfo     Property we're a setter for
            \param[in] sl           Source location that it was declared
            \param[in] function     The member function pointer
            \note Consumers shouldn't be directly creating these, it's public to avoid thorny friend statements.
        */
        UIFBR_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<O,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
    private:
        /*! \brief Sets the property
        
            \param[in] obj      Pointer to object
            \param[in] value    Pointer to value
        */
        virtual std::error_code set(void* p, const void* value) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            Object*  obj  = (Object*) p;
            C*        c   = dynamic_cast<C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            assert(value);
            if(!value)
                return errors::null_value();

            //  Types have already been checked, therefore C-style casts are fine
            if(! (c->*m_function)(*(const T*) value))
                return errors::setter_failed();
            return std::error_code();
        }
        
        /*! \brief Sets the property by string
        
            \param[in] obj      Pointer to object
            \param[in] value    String representation of the value
        */
        virtual std::error_code set(void*p, std::string_view value) const override
        {
            assert(p);
            if(!p)
                return errors::null_object();
            Object*  obj  = (Object*) p;
            C*        c   = dynamic_cast<C*>(obj);
            assert(c);
            if(!c)
                return errors::null_object();

            T   tmp;
            std::error_code ec = TypeMeta::parse(tmp, value);
            if(ec != std::error_code())
                return ec;
            if(! (c->*m_function)(tmp))
                return errors::setter_failed();
            return std::error_code();
        }

        FN      m_function;
    };
}
