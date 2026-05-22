////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/result.hpp>

#include <map>
#include <meta>
#include <type_traits>
#include <vector>

namespace yq {
    template <typename E>
    class Enumeration {
    public:
        static_assert(std::is_enum_v<E>, "Must be a valid enumeration!");
        struct KeyValue {
            std::string_view    key;
            E                   value;
        };
    
        using integer_t     = std::underlying_type_t<E>;
        using enumeration_t = E;
        using result_t      = Result<E>;
        
        static constexpr const size_t  count_n = std::meta::enumerators_of(^^E).size();
        using definition_t       = std::array<KeyValue,count_n>;
    
        constexpr std::string_view  name() const { return m_name; }
        E               value(default_k) const { return m_values.def; }
        constexpr E     value(maximum_k) const { return m_values.max; }
        constexpr E     value(minimum_k) const { return m_values.min; }
        
        const auto&     definition() const { return m_definition.declared; }
        const auto&     definition(ordered_k) const { return m_definition.ordered; }
        const auto&     definition(sorted_k) const { return m_definition.sorted; }
        
        result_t            value_of(std::string_view) const;
        std::string_view    key_of(E) const;
        std::string_view    pretty_of(E) const;
        std::string_view    display_of(E) const;
        bool                has_value(E) const;
        bool                has_key(std::string_view) const;
        
        static size_t   count(value_k) { return count_n; }
        
        //! All keys as declared
        const auto&     all_keys() const { return m_keys.declared; }
        
        //! All keys as ordered by value
        const auto&     all_keys(ordered_k) const { return m_keys.ordered; }
        
        //! All keys as sorted in alphabetical order
        const auto&     all_keys(sorted_k) const { return m_keys.sorted; }
        
        //! All values as declared (note, might be extra)
        const auto&     all_values() const { return m_values.declared; }
        
        //! All values as ordered by value
        const auto&     all_values(ordered_k) const { return m_values.ordered; }

        //! All values as sorted by key
        const auto&     all_values(sorted_k) const { return m_values.sorted; }

        //! All values (sorted by value/unique)
        const auto&     all_values(unique_k) const { return m_values.unique; }
        
        //  non const here.... (using meta thread safe write to guard)
        
        static Enumeration&     static_manifest();
        
        template <size_t N>
        void    pretty(E, const char (&)[N]);
    
    protected:
        using name2val_t        = std::map<std::string_view,E,IgCase>;
        using val2name_t        = std::map<E,std::string_view>;
        using val2names_t       = std::multimap<E,std::string_view>;
    
        static constexpr definition_t     create_definition();
    
        struct {
            definition_t        declared, ordered, sorted;
        } m_definition;
    
        definition_t            m_sorted;
        definition_t            m_ordered;
        std::string_view        m_name;
        
        name2val_t              m_name2value;
        val2name_t              m_value2name;
        val2names_t             m_value2names;
        val2name_t              m_value2display;
        val2name_t              m_value2pretty;
        
        struct {
            std::vector<E>                  declared, unique, ordered, sorted;
            E                               def, min, max;
        } m_values;

        struct {
            std::vector<std::string_view>   declared, ordered, sorted;
        } m_keys;

        Enumeration();
    };
    
    /*! \brief Key/value mapping
        This accesses the key/value/pretty mapping
    */
    template <typename E>
    const Enumeration<E>& enumeration()
    {
        return Enumeration<E>::static_manifest();
    }

    template <typename E>
    Enumeration<E>& enumeration(write_k)
    {
        return Enumeration<E>::static_manifest();
    }
    
    template <typename E>
    requires std::is_enum_v<E>
    std::string_view key_of(E v)
    {
        return enumeration<E>().key_of(v);
    }
}


