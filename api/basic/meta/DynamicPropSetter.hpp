////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/PropSetter.hpp>

namespace yq {
    template <typename C, typename T>
    class DynamicPropSetter : public PropSetter {
    public:
    
        virtual const Meta&     data() const override
        {
            return meta<T>();
        }

        virtual const Meta&     object() const override
        {
            return meta<C>();
        }

    protected:
        DynamicPropSetter(PropertyInfo* propInfo, const std::source_location& sl) : PropSetter(propInfo, sl) {}
    };

    
    template <typename C, typename T>
    class IPM_PropSetter : public DynamicPropSetter<C,T> {
    public:
        typedef T (C::*P);
        IPM_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, P pointer) : DynamicPropSetter<C,T>(propInfo, sl), m_data(pointer) 
        {
            assert(pointer);
        }
        
        virtual bool            set(void*obj, const void*value) const override
        {
            assert(obj);
            assert(value);
            (((C*) obj)->*m_data) =  *(const T*) value;
            return true;
        }
    
        virtual bool            set(void*obj, std::string_view value) const override
        {
            assert(obj);
            return TypeInfo::parse(((C*) obj)->*m_data, value);
        }
        
    private:
        P      m_data;
    };
    
    template <typename C, typename T>
    class IFV_PropSetter : public DynamicPropSetter<C,T>{
    public:
        typedef void (C::*FN)(T);
        
        IFV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<C,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        virtual bool            set(void* obj, const void* value) const override
        {
            assert(obj);
            assert(value);
            (((C*) obj)->*m_function)(*(const T*) value);
            return true;
        }
        
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

    template <typename C, typename T>
    class IFBV_PropSetter : public DynamicPropSetter<C,T>{
    public:
        typedef bool (C::*FN)(T);
        
        IFBV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<C,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        virtual bool            set(void* obj, const void* value) const override
        {
            assert(obj);
            assert(value);
            return (((C*) obj)->*m_function)(*(const T*) value);
        }
        
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

    template <typename C, typename T>
    class IFR_PropSetter : public DynamicPropSetter<C,T>{
    public:
        typedef void (C::*FN)(const T&);
        
        IFR_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<C,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        virtual bool            set(void* obj, const void* value) const override
        {
            assert(obj);
            assert(value);
            
            (((C*) obj)->*m_function)(*(const T*) value);
            return true;
        }
        
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

    template <typename C, typename T>
    class IFBR_PropSetter : public DynamicPropSetter<C,T>{
    public:
        typedef bool (C::*FN)(const T&);
        
        IFBR_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : DynamicPropSetter<C,T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        virtual bool            set(void* obj, const void* value) const override
        {
            assert(obj);
            assert(value);
            return (((C*) obj)->*m_function)(*(const T*) value);
        }
        
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
