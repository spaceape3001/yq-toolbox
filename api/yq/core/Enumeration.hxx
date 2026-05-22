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
    constexpr typename Enumeration<E>::definition_t Enumeration<E>::create_definition()
    {
        definition_t        result;
        size_t k=0;
        for(auto mem: std::meta::enumerators_of(^^E))
            result[k++] = { std::meta::identifier_of(mem), std::meta::extract<E>(mem) };
        return result;
    }

    template <typename E>
    Enumeration<E>&  Enumeration<E>::static_manifest()
    {
        static Enumeration s_instance;
        return s_instance;
    }

    template <typename E>
    Enumeration<E>::Enumeration() : m_definition{.declared=create_definition()}, 
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
    std::string_view    Enumeration<E>::display_of(E v) const
    {
        if(auto itr = m_value2display.find(v); itr != m_value2display.end())
            return itr->second;
        return {};
    }

    template <typename E>
    bool    Enumeration<E>::has_key(std::string_view k) const
    {
        return m_name2value.contains(k);
    }

    template <typename E>
    bool    Enumeration<E>::has_value(E v) const
    {
        return m_value2name.contains(v);
    }
    
    template <typename E>
    std::string_view    Enumeration<E>::key_of(E v) const
    {
        if(auto itr = m_value2name.find(v); itr != m_value2name.end())
            return itr->second;
        return {};
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
    std::string_view    Enumeration<E>::pretty_of(E v) const
    {
        if(auto itr = m_value2pretty.find(v); itr != m_value2pretty.end())
            return itr->second;
        return {};
    }
    
    template <typename E>
    typename Enumeration<E>::result_t   Enumeration<E>::value_of(std::string_view k) const
    {
        if(auto itr =m_name2value.find(k); itr != m_name2value.end())
            return { itr->second, true };
        return {};
    }
}

#define YQ_ENUMERATION_IMPLEMENT(ecls) template class Enumeration<ecls>;
    

