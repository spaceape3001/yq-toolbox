////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/CompoundMetaStatic.hpp>
#include <yq/meta/DynamicPropGetter.hpp>
#include <yq/meta/DynamicPropSetter.hpp>
#include <yq/meta/PropertyMetaWriter.hpp>
#include <concepts>

namespace yq {
    template <typename C>
    class CompoundMeta::Dynamic : public CompoundMeta::Static {
    public:
    
        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param pointer          Pointer to class/type member
            \param[in] isReadOnly   Set to TRUE to make this read-only property
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::Writer<T>     property(std::string_view szName, T (B::*pointer), bool isReadOnly=false, const std::source_location& sl=std::source_location::current())
        {
            assert(pointer);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            ret -> set(Flag::STATE);
            new IPM_PropGetter<B,T>(ret, sl, pointer);
            if(!isReadOnly)
                new IPM_PropSetter<B,T>(ret, sl, pointer);
            return PropertyMeta::Writer<T>{ret};
        }
        
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::Writer<T>     property(std::string_view szName, read_only_k, T (B::*pointer), const std::source_location& sl=std::source_location::current())
        {
            return property(szName, pointer, true, sl);
        }


        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  pointer Pointer to class/type member
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::Writer<T>     property(std::string_view szName, const T (B::*pointer), const std::source_location& sl=std::source_location::current())
        {
            assert(pointer);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            ret -> set(Flag::STATE);
            new IPM_PropGetter<B,T>(ret, sl, pointer);
            return PropertyMeta::Writer<T>{ret};
        }

        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::Writer<T>     property(std::string_view szName, read_only_k, const T (B::*pointer), const std::source_location& sl=std::source_location::current())
        {
            return property(szName, pointer, sl);
        }
        

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::PropW<C,T>    property(std::string_view szName, T (B::*function)() const, const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            new IFV_PropGetter<B,T>(ret, sl, function);
            return PropertyMeta::PropW<C,T>{ret};
        }
        

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::PropW<C,T>    property(std::string_view szName, T (B::*function)() const noexcept, const std::source_location& sl=std::source_location::current())
        {
            return property(szName, (T (B::*)() const) function, sl);
        }

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::PropW<C,T>    property(std::string_view szName, const T& (B::*function)() const, const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            new IFR_PropGetter<B,T>(ret, sl, function);
            return PropertyMeta::PropW<C,T>{ret};
        }

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::PropW<C,T>    property(std::string_view szName, const T& (B::*function)() const noexcept, const std::source_location& sl=std::source_location::current())
        {
            return property(szName, (const T& (B::*)() const) function, sl);
        }

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::PropW<C,T>    property(std::string_view szName, void (B::*function)(T&) const, const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            new IFP_PropGetter<B,T>(ret, sl, function);
            return PropertyMeta::PropW<C,T>{ret};
        }
        
    
        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::PropW<C,T>    property(std::string_view szName, bool (B::*function)(T&) const, const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            new IFPB_PropGetter<B,T>(ret, sl, function);
            return PropertyMeta::PropW<C,T>{ret};
        }
        
        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::PropW<C,T>    property(std::string_view szName, T (*function)(B), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            new ZFVV_PropGetter<B,T>(ret, sl, function);
            return PropertyMeta::PropW<C,T>{ret};
        }

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::PropW<C,T>    property(std::string_view szName, T (*function)(const B&), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            new ZFRV_PropGetter<B,T>(ret, sl, function);
            return PropertyMeta::PropW<C,T>{ret};
        }

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::PropW<C,T>    property(std::string_view szName, const T& (*function)(B), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            new ZFVR_PropGetter<B,T>(ret, sl, function);
            return PropertyMeta::PropW<C,T>{ret};
        }

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param  p       Function pointer to getter (const & returns)
        */
        template <typename T, typename B=C>
        requires (std::is_base_of_v<B,C>)
        PropertyMeta::PropW<C,T>    property(std::string_view szName, const T& (*function)(const B&), const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            new ZFRR_PropGetter<B,T>(ret, sl, function);
            return PropertyMeta::PropW<C,T>{ret};
        }

        template <typename B, typename R, typename ... Args>
        requires (std::is_base_of_v<B,C>)
        MethodMeta::Writer<R,Args...>   method(std::string_view szName, R (B::*function)(Args...), const std::source_location& sl=std::source_location::current());

        template <typename B, typename R, typename ... Args>
        requires (std::is_base_of_v<B,C>)
        MethodMeta::Writer<R,Args...>   method(std::string_view szName, R (B::*function)(Args...) const, const std::source_location& sl=std::source_location::current())
        {
            assert(function);
            if(function && Meta::Writer::m_meta && thread_safe_write()){
                MethodMeta* ret = new MethodMeta::Const<R,C,Args...>(function, szName, sl, Meta::Writer::m_meta);
                return MethodMeta::Writer<R, Args...>(ret, 0ULL);
            }
            return MethodMeta::Writer<R, Args...>();
        }
        
        template <typename B, typename R, typename ... Args>
        requires (std::is_base_of_v<B,C>)
        MethodMeta::Writer<R,Args...>   method(std::string_view szName, R (B::*function)(Args...) const noexcept, const std::source_location& sl=std::source_location::current())
        {
            return method(szName, (R (B::*)(Args...) const) function, sl);
        }
        
        Dynamic(CompoundMeta* c) : Static(c) {}
    };
}
