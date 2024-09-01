////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/text/utilities32.hpp>

#include <0/basic/preamble.hpp>
#include <yq/trait/always_false.hpp>
#include <cstring>
#include <vector>
#include <iosfwd>
#include <string>
#include <string_view>

namespace yq {

    //! Concatenates the given 32-bit UTF character on to the u32string as UTF-8
//    std::u32string&  operator+=(std::u32string&, char32_t);
    
    
    
    /*! \brief Blanks all C++ comments in the given u32string 
    
        This goes over the u32string, all C++ comments are turned into spaces
    */
    void  blank_cpp_comments(std::u32string&);
    
    /*! \brief Capitalizes each word
    
        This capitalizes each word in the u32string, the first character going to upper case, the rest 
        converted to lower case.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
    */
    std::u32string  capitalize(const char32_t*s, size_t n);

    /*! \brief Capitalizes each word
    
        This capitalizes each word in the u32string, the first character going to upper case, the rest 
        converted to lower case.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
    */
    std::u32string  capitalize(std::u32string_view s);
    
    /*! \brief Conctenates two u32strings
    
        Concatenates two u32strings together.
        
        \param[in] a    First u32string
        \param[in] b    Second u32string
        \return new u32string of the concatenation
    */
    std::u32string concat(std::u32string_view a, std::u32string_view b);

    /*! \brief Checks if the haystack has the needle
    */
    bool    contains(const char32_t* haystack, size_t nHaystack, const char32_t* needle, size_t nNeedle);

    /*! \brief Checks if the haystack has the needle
    */
    bool    contains(std::u32string_view haystack, std::u32string_view needle);

    /*! \brief Checks if the haystack has the needle (ignoring case)
    */
    bool    contains_igCase(const char32_t* haystack, size_t nHaystack, const char32_t* needle, size_t nNeedle);

    /*! \brief Checks if the haystack has the needle (ignoring case)
    */
    bool    contains_igCase(std::u32string_view haystack, std::u32string_view needle);

    /*! \brief Copies the u32string
    
        This doesn't return a reference, but actually makes a copy.
    */
    inline std::u32string  copy(std::u32string_view s)
    {
        return std::u32string(s);
    }
    
    u32string_set_t        copy(const u32string_view_set_t&);

    /*! \brief Copies the vector of u32string
    
        This doesn't return a reference, but actually makes a copy.
    */
    std::vector<std::u32string>  copy(const std::vector<std::u32string>&);

    /*! \brief Copies the vector of u32string-views
    
        This doesn't return a reference, but actually makes a copy.
    */
    std::vector<std::u32string>  copy(const std::vector<std::u32string_view>&);
    
    std::vector<std::u32string>  copy(std::initializer_list<std::u32string_view>);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters(const char32_t* s, size_t n);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters(std::u32string_view s);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters(const char32_t* s, size_t n, char32_t ch);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters(std::u32string_view s, char32_t ch);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters_igCase(const char32_t* s, size_t n, char32_t ch);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters_igCase(std::u32string_view s, char32_t ch);

    /*! \brief Counts the opening number of space characters
    */
    size_t  count_start_spaces(std::u32string_view);
    
    /*! \brief Counts the number of the specified character that start the u32string
    */
    size_t  count_starts(std::u32string_view, char32_t);

    bool    ends(std::u32string_view hay, std::u32string_view pat);

    /*! \brief First non-blank character
        This returns the first non-blank character seen, or NULL if none found
    */
    char32_t  first_non_blank_char32_t(std::u32string_view sv);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::u32string_view  first_non_empty(std::u32string_view, std::u32string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::u32string_view  first_non_empty(std::u32string_view, std::u32string_view, std::u32string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::u32string_view  first_non_empty(std::u32string_view, std::u32string_view, std::u32string_view, std::u32string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::u32string_view  first_non_empty(std::initializer_list<std::u32string_view>);


    
    /*! \brief Hard wrap at the given size
    
        A hard wrap will break mid-word as necessary, and is based on the number of UTF-8 
        character code points.  (ie, entries might have different byte counts, but the character
        counts will remain identical until the last one.)
    
        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s pointer to u32string
        \param[in] n length of the u32string
        \param[in] width    number of characters to wrap at.
    */
    std::vector<std::u32string_view>  hard_wrap(const char32_t*s, size_t n, size_t width);
    
    /*! \brief Hard wrap at the given size
    
        A hard wrap will break mid-word as necessary, and is based on the number of UTF-8 
        character code points.  (ie, entries might have different byte counts, but the character
        counts will remain identical until the last one.)
    
        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        \param[in] width    number of characters to wrap at.
    */
    std::vector<std::u32string_view>  hard_wrap(std::u32string_view s, size_t width);

    /*! \brief Tests for emptiness
    
        \return TRUE if BOTH first & second are empty
    */
    inline bool is_empty(const u32string_view_pair_t& p)
    {
        return p.first.empty() && p.second.empty();
    }
    
    bool        is_equal(std::u32string_view, std::u32string_view);
    

    /*! \brief Tests if b > a ignoring case
    
        This ignores case differences as it compares u32strings a & b.
    */
    bool  is_greater_igCase(std::u32string_view a, std::u32string_view b);
    
    
    /*! \brief Test to see if u32string matches the pattern
    
        (this one is here so it signature matches the other
    */
    bool  is_in(std::u32string_view str, std::u32string_view pat);

    /*! \brief Test to see if u32string matches one of the patterns
    */
    bool  is_in(std::u32string_view str, std::initializer_list<std::u32string_view> pat);
    
    /*! \brief Test to see if u32string matches one of the patterns
    */
    bool  is_in(std::u32string_view str, const u32string_view_set_t& pat);

    /*! \brief Test to see if u32string matches one of the patterns
    */
    bool  is_in(std::u32string_view str, const std::vector<std::u32string_view>& pat);
    
    bool is_in(char32_t, std::u32string_view);

    /*! \brief Tests if b < a ignoring case
    
        This ignores case differences as it compares u32strings a & b.
    */
    bool  is_less_igCase(std::u32string_view a, std::u32string_view b);



    /*! \brief Tests for equality while ignoring case
    */
    bool  is_similar(char32_t, char32_t);


    /*! \brief Tests for equality while ignoring case
    */
    bool  is_similar(std::u32string_view, std::u32string_view);


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

    /*! \brief Checks to see if the haystack matches the pattern at position
    
        \note Check will end at the length pattern, so "matches_at("foobar rocks", 3, "bar")" will be TRUE
    */
    bool        matches_at(std::u32string_view haystack, size_t pos, std::u32string_view pattern);

    /*! \brief Checks to see if the haystack matches the pattern at position
    
        \note Check will end at the length pattern, so "matches_at("foobar rocks", 3, "bar")" will be TRUE
    */
    bool        matches_at_igCase(std::u32string_view haystack, size_t pos, std::u32string_view pattern);
    
    /*! \brief Left pads the result until the character count is met */
    std::u32string     pad_left(std::u32string_view data, size_t minSize, char32_t ch=U' ');
    
    /*! \brief Right pads the result until the character count is met */
    std::u32string     pad_right(std::u32string_view data, size_t minSize, char32_t ch=U' ');
    
    //! Will *attempt* to make a plural form, won't be perfect
    std::u32string     pluralize(std::u32string_view);
    
    /*! \brief Replaces all instances of old character with new character */
    size_t          replace_all(std::u32string&, char32_t what, char32_t with);
    
    /*! \brief Replaces all instances of old character with new character ignoring case */
    size_t          replace_all_igCase(std::u32string&, char32_t what, char32_t with);

    /*! \brief Set left to right if left is empty OR override is true
    
        \note if B is empty, this is a NOP
    */
    std::u32string&    set_if_empty(std::u32string&, std::u32string_view, bool fOverride=false);
    
    /*! \brief Simplifies the given u32string
    
        Simplifying a u32string removes start & end whitespace, replaces interior spaces with a single space character.
    */
    std::u32string     simplify(const char32_t*s, size_t n, char32_t sp=' ');

    /*! \brief Simplifies the given u32string
    */
    std::u32string     simplify(std::u32string_view, char32_t sp=' ');


    /*! \brief Strips the LAST extension
    
        This returns the input MINUS the last extension, call repeatedly to remove more than one.
    */
    std::u32string_view    strip_extension(std::u32string_view);

    /*! \brief Strips ALL spaces from the input
    */
    std::u32string  strip_spaces(const char32_t* s, size_t n);

    /*! \brief Strips ALL spaces from the input
    */
    std::u32string  strip_spaces(std::u32string_view);
    

    /*! Converts the u32string view to u32string u32string view
    
        Yes, there's a constructor, however, this is for the template (below);  Copy 
    */
    inline std::u32string  to_u32string(std::u32string_view s)
    {
        return std::u32string(s);
    }

    /*! No-op u32string to u32string, for templates
    
        Yes, there's a constructor, however, this is for the template (below);
    */
    inline const std::u32string&  to_u32string(const std::u32string& s)
    {
        return s;
    }

    /*! \brief Concatenates vector of T to std::u32string
    */
    template <typename T>
    auto  to_u32string(const std::vector<T>& input)
    {
        using ret_t  = decltype(to_u32string(T()));
        Vector<ret_t>   ret;
        ret.reserve(input.size());
        for(auto& i : input)
            ret << to_u32string(i);
        return ret;
    }


    /*! \brief Returns the character-array as a u32string.
    */
    inline std::u32string_view  to_u32string_view(const char32_t*z)
    {
        return std::u32string_view(z);
    }


    //! Simple to-string-view for a u32string
    //!
    //! Yes, it's defined on the class, however, this allows for templated "T" expectations to work
    inline std::u32string_view to_u32string_view( const std::u32string& sv)
    {
        return sv;
    }

    //! Simple to-string-view for a u32string_view
    //!
    //! Yes, it's a noop, however, this allows for templated "T" expectations to work
    inline std::u32string_view to_u32string_view( std::u32string_view sv)
    {
        return sv;
    }
    
    /*! \brief Converts to std::u32string_view
    */
    std::u32string_view    to_u32string_view(const std::u8string_view&s);

    
    /*! \brief Converts the u32string set to a u32string view set
        \note Contents of the return set are REFERENCES to the original set data
    */
    u32string_view_set_t   to_u32string_view_set(const u32string_set_t&);

    std::u32string      to_u32string(std::u32string_view);


    /*! \brief String not starting/ending with spaces
    */
    std::u32string_view    trimmed(std::u32string_view);
    
    /*! \brief String not starting/ending with specified character
    
    */
    std::u32string_view    trimmed(std::u32string_view, char32_t);

    /*! \brief String not ending with whitespaces
    */
    std::u32string_view    trimmed_end(std::u32string_view);
    
    /*! \brief String not ending with whitespaces specified character
    */
    std::u32string_view    trimmed_end(std::u32string_view, char32_t);

    /*! \brief String not starting with whitespace
    */
    std::u32string_view    trimmed_start(std::u32string_view);
    
    /*! \brief String not starting with whitespace specified character
    */
    std::u32string_view    trimmed_start(std::u32string_view, char32_t);

    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  IMPLEMENTATION
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    
    template <typename T>
    static constexpr const bool     has_to_u32string_view_v    = std::is_same_v<std::u32string_view, decltype(to_u32string_view(T()))>;

    template <typename T>
    static constexpr const bool     has_to_u32string_v    = std::is_same_v<std::u32string, decltype(to_u32string(T()))>;
    

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

    /*! \brief Tou32string when we have a to-string-view function
    */
    template <typename T>
    //requires (std::is_same_v<std::u32string_view, to_u32string_view(T())>)
    std::u32string    to_u32string(const T& v)
    {
        return std::u32string(to_u32string_view(v));
    }
}

namespace std {
    ostream& operator<<(ostream&, u32string_view);
    ostream& operator<<(ostream&, const u32string&);
}


