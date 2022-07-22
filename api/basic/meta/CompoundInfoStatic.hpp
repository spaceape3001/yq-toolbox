////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/CompoundInfo.hpp>
#include <basic/meta/MetaWriter.hpp>
#include <basic/meta/MethodInfoWriter.hpp>
#include <basic/meta/StaticPropGetter.hpp>
#include <basic/meta/StaticPropSetter.hpp>
#include <basic/meta/PropertyInfoWriter.hpp>

namespace yq {


    class CompoundInfo::Static : public Meta::Writer {
    public:
        
        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read/write.
            
            \tparam T   type
        */
        template <typename T>
        PropertyInfo::Writer<T>       variable(std::string_view szName, T* pointer, const std::source_location& sl=std::source_location::current())
        {
            assert(pointer);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta, STATIC);
            new XPV_PropGetter<T>(ret, sl, pointer);
            new XPV_PropSetter<T>(ret, sl, pointer);
            return PropertyInfo::Writer<T>{ret};
        }

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read/write.
            
            \tparam T   type
        */
        template <typename T>
        PropertyInfo::Writer<T>       variable(std::string_view szName, const T* pointer, const std::source_location& sl=std::source_location::current())
        {
            assert(pointer);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta, STATIC);
            new XPV_PropGetter<T>(ret, sl, pointer);
            return PropertyInfo::Writer<T>{ret};
        }

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read only.
            
            \tparam T   type
        */
        template <typename T>
        PropertyInfo::VarW<T>           variable(std::string_view szName, T (*function)(), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*   ret = new PropertyInfo(szName, sl, meta<T>(), m_meta, STATIC);
            new XFV_PropGetter<T>(ret, sl, function);
            return PropertyInfo::VarW<T>(ret);
        }

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read only.
            
            \tparam T   type
        */
        template <typename T>
        PropertyInfo::VarW<T>           variable(std::string_view szName, const T& (*function)(), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*   ret = new PropertyInfo(szName, sl, meta<T>(), m_meta, STATIC);
            new XFCR_PropGetter<T>(ret, sl, function);
            return PropertyInfo::VarW<T>(ret);
        }

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read only.
            
            \tparam T   type
        */
        template <typename T>
        PropertyInfo::VarW<T>           variable(std::string_view szName, void (*function)(T&), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*   ret = new PropertyInfo(szName, sl, meta<T>(), m_meta, STATIC);
            new XFVR_PropGetter<T>(ret, sl, function);
            return PropertyInfo::VarW<T>(ret);
        }
        

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read only.
            
            \tparam T   type
        */
        template <typename T>
        PropertyInfo::VarW<T>           variable(std::string_view szName, bool (*function)(T&), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*   ret = new PropertyInfo(szName, meta<T>(), sl, m_meta, STATIC);
            new XFBR_PropGetter<T>(ret, sl, function);
            return PropertyInfo::VarW<T>(ret);
        }



        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read/write.
            
            \tparam T   type
        */
        template <typename ... Args>
        MethodInfo::Writer              function(std::string_view szName, void(*)(Args...), const std::source_location& sl=std::source_location::current());

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read/write.
            
            \tparam T   type
        */
        template <typename T, typename ... Args>
        MethodInfo::Writer              function(std::string_view szName, T(*)(Args...), const std::source_location& sl=std::source_location::current());

        Static( CompoundInfo* compound ) : Meta::Writer(compound) {}
    };
}
