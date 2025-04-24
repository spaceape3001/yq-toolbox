////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <yq/errors.hpp>
#include <yq/core/Result.hpp>
#include <yq/meta/AnyDef.hpp>
#include <yq/meta/TypeInfo.hpp>

    //  SKIPPING INCLUDES... done in order by others

namespace yq {

    inline Any::Any() : m_type(&invalid()), m_data{}
    {
    }


    template <typename T>
    Any  Any::from(T&& val)
    {
        Any   ret;
        ret.set(std::move(val));
        return ret;
    }

    template <typename T>
    requires (!std::is_same_v<T, Any>)
    Any::Any(T&& val) : m_type(nullptr)
    {
        set(val);
    }

    template <typename T>
    requires (is_type_v<std::decay_t<T>> && !std::is_same_v<T,Any>)
    Any&    Any::operator=(T&& cp)
    {
        set(cp);
        return *this;
    }

    template <typename T>
    requires (is_type_v<std::decay_t<T>> && !std::is_same_v<T,Any>)
    bool        Any::operator==(const T&b) const
    {
        if(&meta<T>() != m_type)
            return false;
        return m_data.reference<T>() == b;
    }


    template <typename T>
    requires is_type_v<T>
    bool        operator==(const T& a, const Any& b)
    {
        return b.operator==(a);
    }

    template <typename T, typename Pred>
    bool    Any::as(Pred&& pred) const
    {
        static_assert( is_type_v<T>, "TypeInfo T must be metatype defined!");
        if(m_type == &meta<T>()){
            pred(m_data.reference<T>());
            return true;
        }
        
        auto cvt = m_type -> m_convert.get(&meta<T>(), nullptr);
        if(cvt){
            T tmp;
            (*cvt)(&tmp, raw_ptr());
            pred(tmp);
            return true;
        }
        return false;
    }

    template <typename T>
    bool        Any::can_convert() const
    {
        static_assert( is_type_v<T>, "TypeInfo T must be metatype defined!");
        return can_convert_to(&meta<T>());
    }

    template <typename T>
    any_x     Any::convert() const
    {
        static_assert( is_type_v<T>, "TypeInfo T must be metatype defined!");
        return convert_to(meta<T>());
    }

    template <typename T>
    T*          Any::ptr()
    {
        static_assert( is_type_v<T>, "TypeInfo T must be metatype defined!");
        return (m_type == &meta<T>()) ?  m_data.pointer<T>() : nullptr;
    }


    template <typename T>
    const T*    Any::ptr() const
    {
        static_assert( is_type_v<T>, "TypeInfo T must be metatype defined!");
        return (m_type == &meta<T>()) ?  m_data.pointer<T>() : nullptr;
    }

    template <typename T>
    const T&            Any::ref(const T& bad) const
    {
        static_assert( is_type_v<T>, "TypeInfo T must be metatype defined!");
        return (m_type == &meta<T>()) ?  m_data.reference<T>() : bad;
    }

    template <typename T>
    void Any::set(T&& val)
    {
        using U     = std::decay<T>::type;
        static_assert( is_type_v<U>, "TypeInfo must be metatype defined!");
        
        const TypeInfo& newType  = meta<U>();
        if(m_type){
            if(&newType == m_type){
                if constexpr (std::is_rvalue_reference_v<T>){
                    m_data.reference<U>() = std::move(val);
                } else {
                    m_data.reference<U>() = val;
                }
                return;
            }
            (m_type->m_dtor)(m_data);
        }
        
        assert(good(newType));
        m_type      = &newType;
        if constexpr (std::is_rvalue_reference_v<T>){
            m_data.ctorMove(std::move(val));
        } else {
            m_data.ctorCopy(val);
        }
    }

    inline void    Any::set(std::string_view cp)
    {
        static const TypeInfo*  mtString    = &meta<std::string>();
        m_data.reference<std::string>() = std::string(cp);
        m_type  = mtString;
    }

    inline void    Any::set(std::string&&mv)
    {
        static const TypeInfo*  mtString    = &meta<std::string>();
        m_data.reference<std::string>() = std::move(mv);
        m_type  = mtString;
    }

    template <typename T>
    const T*    Any::unsafe_ptr() const
    {
        return m_data.pointer<T>();
    }

    template <typename T>
    Result<const T&>   Any::value() const
    {
        static thread_local T   tmp;
        static_assert( is_type_v<T>, "TypeInfo T must be metatype defined!");
        if(m_type == &meta<T>())
            return {m_data.reference<T>(), true};
            
        auto cvt = m_type -> m_convert.get(&meta<T>(), nullptr);
        if(cvt){
            (*cvt)(&tmp, raw_ptr());
            return { tmp, true };
        }
        return { tmp, false };
    }
}
