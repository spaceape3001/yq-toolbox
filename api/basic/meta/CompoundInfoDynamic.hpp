////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/meta/CompoundInfoStatic.hpp>
#include <basic/meta/DynamicPropGetter.hpp>
#include <basic/meta/DynamicPropSetter.hpp>
#include <basic/meta/PropertyInfoWriter.hpp>

namespace yq {
    template <typename C>
    class CompoundInfo::Dynamic : public CompoundInfo::Static {
    public:
    
        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param pointer          Pointer to class/type member
            \param[in] isReadOnly   Set to TRUE to make this read-only property
        */
        template <typename T>
        PropertyInfo::Writer<T>     property(std::string_view szName, T (C::*pointer), bool isReadOnly=false, const std::source_location& sl=std::source_location::current())
        {
            assert(pointer);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta, STATE);
            new IPM_PropGetter<C,T>(ret, sl, pointer);
            if(!isReadOnly)
                new IPM_PropSetter<C,T>(ret, sl, pointer);
            return PropertyInfo::Writer<T>{ret};
        }
        
        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  pointer Pointer to class/type member
        */
        template <typename T>
        PropertyInfo::Writer<T>     property(std::string_view szName, const T (C::*pointer), const std::source_location& sl=std::source_location::current())
        {
            assert(pointer);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta, STATE);
            new IPM_PropGetter<C,T>(ret, sl, pointer);
            return PropertyInfo::Writer<T>{ret};
        }

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T>
        PropertyInfo::PropW<C,T>    property(std::string_view szName, T (C::*function)() const, const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta);
            new IFV_PropGetter<C,T>(ret, sl, function);
            return PropertyInfo::PropW<C,T>{ret};
        }
        
        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T>
        PropertyInfo::PropW<C,T>    property(std::string_view szName, const T& (C::*function)() const, const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta);
            new IFR_PropGetter<C,T>(ret, sl, function);
            return PropertyInfo::PropW<C,T>{ret};
        }


        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T>
        PropertyInfo::PropW<C,T>    property(std::string_view szName, void (C::*function)(T&) const, const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta);
            new IFP_PropGetter<C,T>(ret, sl, function);
            return PropertyInfo::PropW<C,T>{ret};
        }
        
    
        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T>
        PropertyInfo::PropW<C,T>    property(std::string_view szName, bool (C::*function)(T&) const, const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta);
            new IFPB_PropGetter<C,T>(ret, sl, function);
            return PropertyInfo::PropW<C,T>{ret};
        }
        
        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T>
        PropertyInfo::PropW<C,T>    property(std::string_view szName, T (*function)(C), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta);
            new ZFVV_PropGetter<C,T>(ret, sl, function);
            return PropertyInfo::PropW<C,T>{ret};
        }

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T>
        PropertyInfo::PropW<C,T>    property(std::string_view szName, T (*function)(const C&), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta);
            new ZFRV_PropGetter<C,T>(ret, sl, function);
            return PropertyInfo::PropW<C,T>{ret};
        }

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T>
        PropertyInfo::PropW<C,T>    property(std::string_view szName, const T& (*function)(C), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta);
            new ZFVR_PropGetter<C,T>(ret, sl, function);
            return PropertyInfo::PropW<C,T>{ret};
        }

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T>
        PropertyInfo::PropW<C,T>    property(std::string_view szName, const T& (*function)(const C&), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyInfo*ret  = new PropertyInfo(szName, sl, meta<T>(), m_meta);
            new ZFRR_PropGetter<C,T>(ret, sl, function);
            return PropertyInfo::PropW<C,T>{ret};
        }

        template <typename R, typename ... Args>
        MethodInfo::Writer<R,Args...>   method(std::string_view szName, R (C::*function)(Args...), const std::source_location& sl=std::source_location::current());

        template <typename R, typename ... Args>
        MethodInfo::Writer<R,Args...>   method(std::string_view szName, R (C::*function)(Args...) const, const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            if(function && Meta::Writer::m_meta && thread_safe_write()){
                MethodInfo* ret = new MethodInfo::Const<R,C,Args...>(function, szName, sl, Meta::Writer::m_meta);
                return MethodInfo::Writer<R, Args...>(ret, 0ULL);
            }
            return MethodInfo::Writer<R, Args...>();
        }
        
        
        Dynamic(CompoundInfo* c) : Static(c) {}
    };
}
