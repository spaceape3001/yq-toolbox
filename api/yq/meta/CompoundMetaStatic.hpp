////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/CompoundMeta.hpp>
#include <yq/meta/MetaWriter.hpp>
#include <yq/meta/MethodMetaImpl.hpp>
#include <yq/meta/MethodMetaWriter.hpp>
#include <yq/meta/StaticPropGetter.hpp>
#include <yq/meta/StaticPropSetter.hpp>
#include <yq/meta/PropertyMeta.hpp>
#include <yq/meta/PropertyMetaWriter.hpp>

namespace yq {


    class CompoundMeta::Static : public Meta::Writer {
    public:
        
        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read/write.
            
            \tparam T   type
            \param[in] szName       Property name... needs to be a string that persists
            \param[in] pointer      Pointer to the variable
            \param[in] isReadOnly   TRUE for read-only variable
        */
        template <typename T>
        PropertyMeta::Writer<T>       variable(std::string_view szName, T* pointer, bool isReadOnly=false, const std::source_location& sl=std::source_location::current())
        {
            assert(pointer);
            if(pointer && Meta::Writer::m_meta && thread_safe_write()){
                PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
                ret -> set(Flag::STATIC);
                new XPV_PropGetter<T>(ret, sl, pointer);
                if(!isReadOnly)
                    new XPV_PropSetter<T>(ret, sl, pointer);
                return PropertyMeta::Writer<T>{ret};
            }
            return nullptr;
        }

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read/write.
            
            \tparam T   type
        */
        template <typename T>
        PropertyMeta::Writer<T>       variable(std::string_view szName, const T* pointer, const std::source_location& sl=std::source_location::current())
        {
            assert(pointer);
            if(pointer && Meta::Writer::m_meta && thread_safe_write()){
                PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
                ret -> set(Flag::STATIC);
                new XPV_PropGetter<T>(ret, sl, pointer);
                return PropertyMeta::Writer<T>{ret};
            }
            return nullptr;
        }

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read only.
            
            \tparam T   type
        */
        template <typename T>
        PropertyMeta::VarW<T>           variable(std::string_view szName, T (*function)(), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            if(function && Meta::Writer::m_meta && thread_safe_write()){
                PropertyMeta*   ret = new PropertyMeta(szName, sl, meta<T>(), m_meta);
                ret -> set(Flag::STATIC);
                new XFV_PropGetter<T>(ret, sl, function);
                return PropertyMeta::VarW<T>(ret);
            }
            return nullptr;
        }

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read only.
            
            \tparam T   type
        */
        template <typename T>
        PropertyMeta::VarW<T>           variable(std::string_view szName, const T& (*function)(), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            if(function && Meta::Writer::m_meta && thread_safe_write()){
                PropertyMeta*   ret = new PropertyMeta(szName, sl, meta<T>(), m_meta);
                ret -> set(Flag::STATIC);
                new XFCR_PropGetter<T>(ret, sl, function);
                return PropertyMeta::VarW<T>(ret);
            }
            return nullptr;
        }

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read only.
            
            \tparam T   type
        */
        template <typename T>
        PropertyMeta::VarW<T>           variable(std::string_view szName, void (*function)(T&), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            if(function && Meta::Writer::m_meta && thread_safe_write()){
                PropertyMeta*   ret = new PropertyMeta(szName, sl, meta<T>(), m_meta);
                ret -> set(Flag::STATIC);
                new XFVR_PropGetter<T>(ret, sl, function);
                return PropertyMeta::VarW<T>(ret);
            }
            return nullptr;
        }
        

        /*! \brief Defines a global variable
        
            This defines a GLOBAL variable for the given scope, read only.
            
            \tparam T   type
        */
        template <typename T>
        PropertyMeta::VarW<T>           variable(std::string_view szName, bool (*function)(T&), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            if(function && Meta::Writer::m_meta && thread_safe_write()){
                PropertyMeta*   ret = new PropertyMeta(szName, meta<T>(), sl, m_meta);
                ret -> set(Flag::STATIC);
                new XFBR_PropGetter<T>(ret, sl, function);
                return PropertyMeta::VarW<T>(ret);
            }
            return nullptr;
        }


        /*! \brief Defines a global method
        
            This defines a GLOBAL method for the given scope
            
            \tparam R   result type (can be void)
        */
        template <typename R, typename ... Args>
        MethodMeta::Writer<R, Args...>  function(std::string_view szName, R(*function)(Args...), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            if(function && Meta::Writer::m_meta && thread_safe_write()){
                MethodMeta* ret = new MethodMeta::Static<R,Args...>(function, szName, sl, Meta::Writer::m_meta);
                return MethodMeta::Writer<R, Args...>(ret, 0ULL);
            }
            return MethodMeta::Writer<R, Args...>();
        }

        Static( CompoundMeta* compound ) : Meta::Writer(compound) {}
    };
}
