////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/PropSetter.hpp>
#include <basic/meta/TypeInfo.hpp>

namespace yq {
    template <typename T>
    class StaticPropSetter : public PropSetter {
    public:

        virtual const Meta&     data() const override
        {
            return meta<T>();
        }
        
        virtual const Meta&     object() const override
        {
            return invalid();
        }

    protected:
        StaticPropSetter(PropertyInfo*propInfo, const std::source_location& sl) : PropSetter(propInfo, sl) 
        {
        }
    };
    
    template <typename T>
    class XPV_PropSetter : public StaticPropSetter<T> {
    public:
        typedef T* P;
        XPV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, P pointer) : StaticPropSetter<T>(propInfo, sl), m_data(pointer) 
        {
            assert(pointer);
        }
        
        virtual bool            set(void*, const void*value) const override
        {
            assert(value);
            *m_data = *(const T*) value;
            return true;
        }
        
        virtual bool            set(void*, std::string_view value) const override
        {
            return TypeInfo::parse(*m_data, value);
        }

    private:
        P      m_data;
    };

    template <typename T>
    class XFV_PropSetter : public StaticPropSetter<T> {
    public:
        typedef void (*FN)(T);
        XFV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : StaticPropSetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        virtual bool            set(void*, const void*value) const override
        {
            assert(value);
            (*m_function)(*(const T*) value);
            return true;
        }
        
        virtual bool            set(void*, std::string_view value) const override
        {
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            (*m_function)(tmp);
            return true;
        }

    private:
        FN      m_function;
    };

    template <typename T>
    class XFBV_PropSetter : public StaticPropSetter<T> {
    public:
        typedef bool (*FN)(T);
        XFBV_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : StaticPropSetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        virtual bool            set(void*, const void*value) const override
        {
            assert(value);
            return (*m_function)(*(const T*) value);
        }
        
        virtual bool            set(void*, std::string_view value) const override
        {
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            return (*m_function)(tmp);
        }

    private:
        FN      m_function;
    };

    template <typename T>
    class XFR_PropSetter : public StaticPropSetter<T> {
    public:
        typedef void (*FN)(const T&);
        XFR_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : StaticPropSetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        virtual bool            set(void*, const void*value) const override
        {
            assert(value);
            (*m_function)(*(const T*) value);
            return true;
        }
        
        virtual bool            set(void*, std::string_view value) const override
        {
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            (*m_function)(tmp);
            return true;
        }

    private:
        FN      m_function;
    };


    template <typename T>
    class XFBR_PropSetter : public StaticPropSetter<T> {
    public:
        typedef bool (*FN)(const T&);
        XFBR_PropSetter(PropertyInfo* propInfo, const std::source_location& sl, FN function) : StaticPropSetter<T>(propInfo, sl), m_function(function) 
        {
            assert(function);
        }
        
        virtual bool            set(void*, const void*value) const override
        {
            assert(value);
            return (*m_function)(*(const T*) value);
        }
        
        virtual bool            set(void*, std::string_view value) const override
        {
            T   tmp;
            if(!TypeInfo::parse(tmp, value))
                return false;
            return (*m_function)(tmp);
        }

    private:
        FN      m_function;
    };
}
