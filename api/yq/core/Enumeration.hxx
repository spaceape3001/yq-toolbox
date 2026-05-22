////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enumeration.hpp>
#include <yq/core/Result.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/text/match.hpp>
#include <algorithm>

namespace yq {

    template <typename E>
    class BoundEnumerationInfo : public EnumerationInfo {
        using Enum = Enumeration<E>;
    public:
        size_t  count() const override
        {
            return Enum::count();
        }
        
        std::string_view display(int v) const override
        {
            return enumeration<E>().display((E) v);
        }

        std::string_view        key(int v) const override
        {
            return enumeration<E>().key((E) v);
        }
        
        const string_view_vector_t& keys() const 
        {
            return enumeration<E>().keys();
        }

        const string_view_vector_t& keys(ordered_k) const 
        {
            return enumeration<E>().keys(ORDERED);
        }

        const string_view_vector_t& keys(sorted_k) const 
        {
            return enumeration<E>().keys(SORTED);
        }

        std::string_view pretty(int v) const override
        {
            return enumeration<E>().key((E) v);
        }
    
        int value(default_k) const override
        {
            return (int) enumeration<E>().value(DEFAULT);
        }

        int value(minimum_k) const override
        {
            return (int) enumeration<E>().value(MINIMUM);
        }
        
        int value(maximum_k) const override
        {
            return (int) enumeration<E>().value(MAXIMUM);
        }
    
    private:
        friend class Enumeration<E>;
        BoundEnumerationInfo()
        {
            const auto& em = enumeration<E>();
            for(E e : em.values())
                m_values.declared.push_back((int) e);
            for(E e : em.values(ORDERED))
                m_values.ordered.push_back((int) e);
            for(E e : em.values(SORTED))
                m_values.sorted.push_back((int) e);
            for(E e : em.values(UNIQUE))
                m_values.unique.push_back((int) e);
        }
        
        ~BoundEnumerationInfo()
        {
        }
    };
    
    
    template <typename E>
    const EnumerationInfo& Enumeration<E>::info()
    {
        static BoundEnumerationInfo<E> s_info;
        return s_info;
    }
    

    template <typename E>
    constexpr typename Enumeration<E>::definition_t Enumeration<E>::definition(create_k)
    {
        definition_t        result;
        size_t k=0;
        for(auto mem: std::meta::enumerators_of(^^E))
            result[k++] = { std::meta::identifier_of(mem), std::meta::extract<E>(mem) };
        return result;
    }

    template <typename E>
    Enumeration<E>&  Enumeration<E>::manifest()
    {
        static Enumeration s_instance;
        return s_instance;
    }

    template <typename E>
    Enumeration<E>::Enumeration() : m_definition{.declared=definition(CREATE)}, 
        m_name(std::meta::identifier_of(^^E))
    {
        bool first = true;
        for(auto& kv : m_definition.declared){
            if(first){
                m_values.def = m_values.min = m_values.max = kv.value;
                first = false;
            } else {
                if(kv.value > m_values.max)
                    m_values.max = kv.value;
                if(kv.value < m_values.min)
                    m_values.min = kv.value;
            }
            
            m_name2value[kv.key] = kv.value;
            m_value2name.emplace(kv.value, kv.key);
            m_value2names.insert({kv.value, kv.key});
            m_values.declared.push_back(kv.value);
            m_keys.declared.push_back(kv.key);
        }
        m_value2display = m_value2name;

        m_definition.ordered = m_definition.declared;
        std::stable_sort(m_definition.ordered.begin(), m_definition.ordered.end(), [&](const KeyValue&a, const KeyValue& b) -> bool {
            return a.value < b.value;
        });

        for(auto& kv : m_definition.ordered){
            m_keys.ordered.push_back(kv.key);
            m_values.ordered.push_back(kv.value);
        }

        m_definition.sorted = m_definition.declared;
        std::stable_sort(m_definition.sorted.begin(), m_definition.sorted.end(), [&](const KeyValue&a, const KeyValue& b) -> bool {
            return is_less_igCase_u8(a.key, b.key);
        });
        
        for(auto& kv : m_definition.sorted){
            m_keys.sorted.push_back(kv.key);
            m_values.sorted.push_back(kv.value);
        }
        
        for(auto& itr : m_value2name)
            m_values.unique.push_back(itr.first);
    }

    template <typename E>
    std::string_view    Enumeration<E>::display(E v) const
    {
        if(auto itr = m_value2display.find(v); itr != m_value2display.end())
            return itr->second;
        return {};
    }

    template <typename E>
    std::string_view    Enumeration<E>::key(E v) const
    {
        if(auto itr = m_value2name.find(v); itr != m_value2name.end())
            return itr->second;
        return {};
    }

    template <typename E>
    bool    Enumeration<E>::key(has_k, std::string_view k) const
    {
        return m_name2value.contains(k);
    }

    template <typename E>
        template <size_t N>
    void    Enumeration<E>::pretty(E v, const char (&k)[N])
    {
        if(!Meta::thread_safe_write())
            return;
        if(!m_value2name.contains(v))
            return;
        m_value2pretty[v]   = k;
        m_value2display[v]  = k;
    }
    
    template <typename E>
    std::string_view    Enumeration<E>::pretty(E v) const
    {
        if(auto itr = m_value2pretty.find(v); itr != m_value2pretty.end())
            return itr->second;
        return {};
    }

    template <typename E>
    typename Enumeration<E>::result_t   Enumeration<E>::value(std::string_view k) const
    {
        if(auto itr =m_name2value.find(k); itr != m_name2value.end())
            return { itr->second, true };
        return {};
    }

    template <typename E>
    void    Enumeration<E>::value(default_k, E v)
    {
        if(!Meta::thread_safe_write())
            return;
        if(!m_value2name.contains(v))
            return;
        m_values.def    = v;
    }
    
    template <typename E>
    bool    Enumeration<E>::value(has_k, E v) const
    {
        return m_value2name.contains(v);
    }

}

#define YQ_ENUM_IMPLEMENT(ecls) template class Enumeration<ecls>;
    

