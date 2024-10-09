////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/text/format32.hpp>
#include <yq/trait/always_false.hpp>

namespace yq {

    /*! \brief Joins the collection into a u32string
        \param[in] collection  The collection
        \param[in] separator   The separator between elements.
        \return The joined u32string
    */
    template <template <typename...> class Tmpl, typename... T>
    std::u32string     join32(const Tmpl<T...>& collection, std::u32string_view separator);
    
    /*! \brief Joins the collection into a u32string
        \param[in] collection  The collection
        \param[in] separator   The separator between elements.
        \return The joined u32string
    */
    template <template <typename...> class Tmpl, typename... T>
    std::u32string     join32(const Tmpl<T...>& collection, char32_t separator);

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  IMPLEMENTATION
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    


    //template <typename Ret, typename Sep, template <typename...> class Tmpl, typename ... T>
    //void     join_generic(Ret& ret, const Tmpl<T...>& collection, Sep sep, size_t nSep, bool is_string)
    //{
        
    //}
    

    /*! Joins a collection into a separator (no separator)
    
        Joins a collection of whatever into a resulting u32string, so long as it has either a "to_u32string" or 
        a "to_u32string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::u32string, std::u32string_view, or have to_u32string/to_u32string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return u32string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    std::u32string     join32(const Tmpl<T...>& collection)
    {
        std::u32string    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, std::u32string> || std::is_same_v<value_t, std::u32string_view>;
        
        if constexpr ( is_string ){
            size_t  n   = 0;
            for(const auto& s : collection)
                n += s.size();
            ret.reserve(n);
        }
        
        for(const auto&s : collection){
            if constexpr (is_string) {
                ret += s;
            } 
            if constexpr (!is_string){
                if constexpr ( has_to_u32string_view_v<value_t> ){
                    ret += to_u32string_view(s);
                } else if constexpr ( has_to_u32string_v<value_t> ){ 
                    ret += to_u32string(s);
                } else {
                    static_assert(always_false_v<value_t>, "Argument deduction failed");
                }
            }
        }
        return ret;
    }
    
    /*! Concatenates u32string
    
        Joins a collection of whatever into a resulting u32string, so long as it has either a "to_u32string" or 
        a "to_u32string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::u32string, std::u32string_view, or have to_u32string/to_u32string_view defined for it.
        \return u32string with the result
    */
    template <typename T>
    std::u32string     concat32(const std::initializer_list<T> collection)
    {
        return join32(collection);
    }

    /*! Joins a collection into a separator
    
        Joins a collection of whatever into a resulting u32string, so long as it has either a "to_u32string" or 
        a "to_u32string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::u32string, std::u32string_view, or have to_u32string/to_u32string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return u32string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    std::u32string     join32(const Tmpl<T...>& collection, std::u32string_view separator)
    {
        std::u32string    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, std::u32string> || std::is_same_v<value_t, std::u32string_view>;
        
        if constexpr ( is_string ){
            size_t  n   = collection.size() * separator.size();
            for(const auto& s : collection)
                n += s.size();
            ret.reserve(n);
        }
        
        bool    f   = true;
        for(const auto&s : collection){
            if(f){
                f   = false;
            } else {
                ret += separator;
            }
            
            if constexpr (is_string) {
                ret += s;
            } 
            if constexpr (!is_string){
                if constexpr ( has_to_u32string_view_v<value_t> ){
                    ret += to_u32string_view(s);
                } else if constexpr ( has_to_u32string_v<value_t> ){ 
                    ret += to_u32string(s);
                } else {
                    static_assert(always_false_v<value_t>, "Argument deduction failed");
                }
            }
        }
        return ret;
    }
    
    /*! Joins a collection into a separator
    
        Joins a collection of whatever into a resulting u32string, so long as it has either a "to_u32string" or 
        a "to_u32string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::u32string, std::u32string_view, or have to_u32string/to_u32string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return u32string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    std::u32string     join32(const Tmpl<T...>& collection, char32_t separator)
    {
        std::u32string    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, std::u32string> || std::is_same_v<value_t, std::u32string_view>;
        
        if constexpr ( is_string ){
            size_t  n   = collection.size();
            for(const auto& s : collection)
                n += s.size();
            ret.reserve(n);
        }
        
        bool    f   = true;
        for(const auto&s : collection){
            if(f){
                f   = false;
            } else {
                ret.push_back(separator);
            }
            
            if constexpr (is_string) {
                ret += s;
            } 
            if constexpr (!is_string){
                if constexpr ( has_to_u32string_view_v<value_t> ){
                    ret += to_u32string_view(s);
                } else if constexpr ( has_to_u32string_v<value_t> ){ 
                    ret += to_u32string(s);
                } else {
                    static_assert(always_false_v<value_t>, "Argument deduction failed");
                }
            }
        }
        return ret;
    }

}
