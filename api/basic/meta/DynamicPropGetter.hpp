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

        virtual const Meta&     data() const override
        {
            return meta<T>();
        }

        virtual const Meta&     object() const override
        {
            return meta<C>();
        }

    protected:
        DynamicPropGetter(PropertyInfo* propInfo, const std::source_location& sl) : PropGetter(propInfo, sl) 
        {
        }
    };
    

    /* !\brief PropGetter for a member variable
    
        PropGetter for the scenario of a member variable on an object.
    */
    template <typename C, typename T>
    class IPM_PropGetter : public DynamicPropGetter<C,T> {
    public:
        typedef const T (C::*P);
        IPM_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, P pointer) : DynamicPropGetter<C,T>(propInfo, sl), m_data(pointer) 
        {
            assert(pointer);
        }

        virtual bool            get(void*dst, const void*obj) const override
        {
            assert(dst);
            assert(obj);
            *(T*) dst   = (((const C*) obj)->*m_data);
            return true;
        }

        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::print(((const C*) obj)->*m_data, str);
            return true;
        }
        
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::write(((const C*) obj)->*m_data, str);
            return true;
        }
        
    private:
        P       m_data;
    };
    
    template <typename C, typename T>
    class IFV_PropGetter : public DynamicPropGetter<C,T> {
    public:
        typedef T (C::*FN)() const;
        IFV_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<C,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
        virtual bool        get(void* dst, const void* obj) const override
        {
            assert(dst);
            assert(obj);
            *(T*) dst   = (((const C*) obj)->*m_function)();
            return true;
        }

        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::print((((const C*) obj)->*m_function)(), str);
            return true;
        }
        
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::write((((const C*) obj)->*m_function)(), str);
            return true;
        }
        
    private:
        FN      m_function;
    };
    
    
    template <typename C, typename T>
    class IFR_PropGetter : public DynamicPropGetter<C,T> {
    public:
        typedef const T& (C::*FN)() const;
        IFR_PropGetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropGetter<C,T>(propInfo, sl), m_function(function)
        {
            assert(function);
        }
        
        virtual bool        get(void* dst, const void* obj) const override
        {
            assert(dst);
            assert(obj);
            *(T*) dst   = (((const C*) obj)->*m_function)();
            return true;
        }
        
        virtual bool            print(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::print((((const C*) obj)->*m_function)(), str);
            return true;
        }
        
        virtual bool            write(Stream&str, const void*obj) const override
        {
            assert(obj);
            TypeInfo::write((((const C*) obj)->*m_function)(), str);
            return true;
        }

    private:
        FN      m_function;
    };

}
