////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/text/format.hpp>
#include <yq/trait/always_false.hpp>

namespace yq {

    /*! \brief Joins the collection into a string
        \param[in] collection  The collection
        \param[in] separator   The separator between elements.
        \return The joined string
    */
    template <template <typename...> class Tmpl, typename... T>
    std::string     join(const Tmpl<T...>& collection, std::string_view separator);
    
    /*! \brief Joins the collection into a string
        \param[in] collection  The collection
        \param[in] separator   The separator between elements.
        \return The joined string
    */
    template <template <typename...> class Tmpl, typename... T>
    std::string     join(const Tmpl<T...>& collection, char separator);

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  IMPLEMENTATION
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



    //template <typename Ret, typename Sep, template <typename...> class Tmpl, typename ... T>
    //void     join_generic(Ret& ret, const Tmpl<T...>& collection, Sep sep, size_t nSep, bool is_string)
    //{
        
    //}
    

    /*! Joins a collection into a separator (no separator)
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    std::string     join(const Tmpl<T...>& collection)
    {
        std::string    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, std::string> || std::is_same_v<value_t, std::string_view>;
        
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
                if constexpr ( has_to_string_view_v<value_t> ){
                    ret += to_string_view(s);
                } else if constexpr ( has_to_string_v<value_t> ){ 
                    ret += to_string(s);
                } else {
                    static_assert(always_false_v<value_t>, "Argument deduction failed");
                }
            }
        }
        return ret;
    }
    
    /*! Concatenates string
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \return string with the result
    */
    template <typename T>
    std::string     concat(const std::initializer_list<T> collection)
    {
        return join(collection);
    }

    /*! Joins a collection into a separator
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    std::string     join(const Tmpl<T...>& collection, std::string_view separator)
    {
        std::string    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, std::string> || std::is_same_v<value_t, std::string_view>;
        
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
                if constexpr ( has_to_string_view_v<value_t> ){
                    ret += to_string_view(s);
                } else if constexpr ( has_to_string_v<value_t> ){ 
                    ret += to_string(s);
                } else {
                    static_assert(always_false_v<value_t>, "Argument deduction failed");
                }
            }
        }
        return ret;
    }
    
    /*! Joins a collection into a separator
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    std::string     join(const Tmpl<T...>& collection, char separator)
    {
        std::string    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, std::string> || std::is_same_v<value_t, std::string_view>;
        
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
                ret += separator;
            }
            
            if constexpr (is_string) {
                ret += s;
            } 
            if constexpr (!is_string){
                if constexpr ( has_to_string_view_v<value_t> ){
                    ret += to_string_view(s);
                } else if constexpr ( has_to_string_v<value_t> ){ 
                    ret += to_string(s);
                } else {
                    static_assert(always_false_v<value_t>, "Argument deduction failed");
                }
            }
        }
        return ret;
    }


}
