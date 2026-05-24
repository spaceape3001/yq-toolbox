////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Expect.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/string_vectors.hpp>

#include <map>
#include <meta>
#include <type_traits>
#include <vector>

namespace yq {

    struct EnumerationInfo;
    
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
        
        static constexpr const size_t  count_n = std::meta::enumerators_of(^^E).size();
        using definition_t       = std::array<KeyValue,count_n>;
    
        static size_t                   count() { return count_n; }
        
        static const EnumerationInfo&   info();
        static Enumeration&             manifest();
        
        //! Similar as value(string) but in failed lookup, it uses the default
        E                   decode(std::string_view) const; 

        const auto&         definition() const { return m_definition.declared; }
        const auto&         definition(ordered_k) const { return m_definition.ordered; }
        const auto&         definition(sorted_k) const { return m_definition.sorted; }

        std::string_view    display(E) const;
        std::string_view    key(E) const;
        bool                key(has_k, std::string_view) const;
        //! All keys as declared
        const auto&         keys() const { return m_keys.declared; }
        
        //! All keys as ordered by value
        const auto&         keys(ordered_k) const { return m_keys.ordered; }
        
        //! All keys as sorted in alphabetical order
        const auto&         keys(sorted_k) const { return m_keys.sorted; }

        //! All keys as sorted in alphabetical order (with same values eliminated)
        const auto&         keys(unique_k) const { return m_keys.unique; }
        
        std::string_view    name() const { return m_name; }
        std::string_view    pretty(E) const;

        Expect<E>           value(std::string_view) const;
        bool                value(has_k, E) const;
        E                   value(default_k) const { return m_values.def; }
        constexpr E         value(maximum_k) const { return m_values.max; }
        constexpr E         value(minimum_k) const { return m_values.min; }
        
        //! All values as declared (note, might be extra)
        const auto&         values() const { return m_values.declared; }
        
        //! All values as ordered by value
        const auto&         values(ordered_k) const { return m_values.ordered; }

        //! All values as sorted by key
        const auto&         values(sorted_k) const { return m_values.sorted; }

        //! All values (sorted by key/unique)
        const auto&         values(unique_k) const { return m_values.unique; }
        
        //  non const here.... (using meta thread safe write to guard)
        
        template <size_t N>
        void    pretty(E, const char (&)[N]);
        
        void    value(default_k, E);
    
    protected:
        using name2val_t        = std::map<std::string_view,E,IgCase>;
        using val2name_t        = std::map<E,std::string_view>;
        using val2names_t       = std::multimap<E,std::string_view>;
    
    
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
            E                               def{}, min{}, max{};
        } m_values;

        struct {
            std::vector<std::string_view>   declared, unique, ordered, sorted;
        } m_keys;

        static constexpr definition_t     definition(create_k);
        Enumeration();
    };

    /*! \brief Key/value mapping
        This accesses the key/value/pretty mapping
    */
    template <typename E>
    const Enumeration<E>& enumeration()
    {
        return Enumeration<E>::manifest();
    }

    template <typename E>
    Enumeration<E>& enumeration(write_k)
    {
        return Enumeration<E>::manifest();
    }

    template <typename E>
    requires std::is_enum_v<E>
    E default_of()
    {
        return enumeration<E>().value(DEFAULT);
    }
    
    template <typename E>
    requires std::is_enum_v<E>
    std::string_view display_of(E v)
    {
        return enumeration<E>().display(v);
    }

    template <typename E>
    requires std::is_enum_v<E>
    std::string_view key_of(E v)
    {
        return enumeration<E>().key(v);
    }
    
    template <typename E>
    requires std::is_enum_v<E>
    auto keys_of()
    {
        return enumeration<E>().keys();
    }
    
    template <typename E>
    requires std::is_enum_v<E>
    auto keys_of(ordered_k)
    {
        return enumeration<E>().keys(ORDERED);
    }

    template <typename E>
    requires std::is_enum_v<E>
    auto keys_of(sorted_k)
    {
        return enumeration<E>().keys(SORTED);
    }
    
    template <typename E>
    requires std::is_enum_v<E>
    auto keys_of(unique_k)
    {
        return enumeration<E>().keys(UNIQUE);
    }
    
    template <typename E>
    requires std::is_enum_v<E>
    E maximum_of()
    {
        return enumeration<E>().value(maximum_k{});
    }

    template <typename E>
    requires std::is_enum_v<E>
    E minimum_of()
    {
        return enumeration<E>().value(minimum_k{});
    }

    template <typename E>
    requires std::is_enum_v<E>
    E value_of(std::string_view s, default_k)
    {
        return enumeration<E>().decode(s);
    }

    template <typename E>
    requires std::is_enum_v<E>
    auto value_of(std::string_view s)
    {
        return enumeration<E>().value(s);
    }

    template <typename E>
    requires std::is_enum_v<E>
    auto values_of()
    {
        return enumeration<E>().values(UNIQUE);
    }

    class EnumerationInfo {
    public:

        virtual size_t  count() const = 0;

        virtual std::string_view display(int) const = 0;

        //virtual const std::vector<
        virtual std::string_view            key(int) const = 0;

        virtual const string_view_vector_t& keys() const = 0;
        virtual const string_view_vector_t& keys(ordered_k) const = 0;
        virtual const string_view_vector_t& keys(sorted_k) const = 0;
        virtual const string_view_vector_t& keys(unique_k) const = 0;

        virtual std::string_view pretty(int) const = 0;

        virtual int value(default_k) const = 0;
        virtual int value(minimum_k) const = 0;
        virtual int value(maximum_k) const = 0;
        virtual integer_x value(std::string_view) const = 0;
        
        const auto& values() const { return m_values.declared; }
        const auto& values(ordered_k) const { return m_values.ordered; }
        const auto& values(sorted_k) const { return m_values.sorted; }
        const auto& values(unique_k) const { return m_values.unique; }
        
    protected:
        EnumerationInfo();
        virtual ~EnumerationInfo();
        
        struct {
            std::vector<int>        declared, ordered, sorted, unique;
        } m_values;
    };

    template <typename E>
    const EnumerationInfo& enumeration(info_k)
    {
        return Enumeration<E>::info();
    }

}


