////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/text/utilities.hpp>

#include <0/basic/preamble.hpp>
#include <yq/trait/always_false.hpp>
#include <cstring>
#include <vector>

namespace yq {

    
    //! Concatenates the given 32-bit UTF character on to the string as UTF-8
    std::string&  operator+=(std::string&, char32_t);
    
    
    /*! \brief Blanks all C++ comments in the given string 
    
        This goes over the string, all C++ comments are turned into spaces
    */
    void  blank_cpp_comments(std::string&);
    
    /*! \brief Capitalizes each word
    
        This capitalizes each word in the string, the first character going to upper case, the rest 
        converted to lower case.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
    */
    std::string  capitalize(const char*s, size_t n);

    /*! \brief Capitalizes each word
    
        This capitalizes each word in the string, the first character going to upper case, the rest 
        converted to lower case.

        \param[in] s    String view (which is auto-gen from std::string if need be.
    */
    std::string  capitalize(std::string_view s);
    
    /*! \brief Conctenates two strings
    
        Concatenates two strings together.
        
        \param[in] a    First string
        \param[in] b    Second string
        \return new string of the concatenation
    */
    std::string concat(std::string_view a, std::string_view b);

    /*! \brief Checks if the haystack has the needle
    */
    bool    contains(const char* haystack, size_t nHaystack, const char* needle, size_t nNeedle);

    /*! \brief Checks if the haystack has the needle
    */
    bool    contains(std::string_view haystack, std::string_view needle);

    /*! \brief Checks if the haystack has the needle (ignoring case)
    */
    bool    contains_igCase(const char* haystack, size_t nHaystack, const char* needle, size_t nNeedle);

    /*! \brief Checks if the haystack has the needle (ignoring case)
    */
    bool    contains_igCase(std::string_view haystack, std::string_view needle);

    /*! \brief Copies the string
    
        This doesn't return a reference, but actually makes a copy.
    */
    inline std::string  copy(std::string_view s)
    {
        return std::string(s);
    }
    
    string_set_t        copy(const string_view_set_t&);

    /*! \brief Copies the vector of string
    
        This doesn't return a reference, but actually makes a copy.
    */
    std::vector<std::string>  copy(const std::vector<std::string>&);

    /*! \brief Copies the vector of string-views
    
        This doesn't return a reference, but actually makes a copy.
    */
    std::vector<std::string>  copy(const std::vector<std::string_view>&);
    
    std::vector<std::string>  copy(std::initializer_list<std::string_view>);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(const char* s, size_t n);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(std::string_view s);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(const char* s, size_t n, char ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(std::string_view s, char ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(const char* s, size_t n, char32_t ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(std::string_view s, char32_t ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters_igCase(const char* s, size_t n, char ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters_igCase(std::string_view s, char ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters_igCase(const char* s, size_t n, char32_t ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters_igCase(std::string_view s, char32_t ch);

    /*! \brief Counts the opening number of space characters
    */
    size_t  count_start_spaces(std::string_view);
    
    /*! \brief Counts the number of the specified character that start the string
    */
    size_t  count_starts(std::string_view, char);

    bool    ends(std::string_view hay, std::string_view pat);

    /*! \brief First non-blank character
        This returns the first non-blank character seen, or NULL if none found
    */
    char32_t  first_non_blank_char(std::string_view sv);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::string_view  first_non_empty(std::string_view, std::string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::string_view  first_non_empty(std::string_view, std::string_view, std::string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::string_view  first_non_empty(std::string_view, std::string_view, std::string_view, std::string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::string_view  first_non_empty(std::initializer_list<std::string_view>);


    /*! \brief Hard wrap at the given size
    
        A hard wrap will break mid-word as necessary, and is based on the number of UTF-8 
        character code points.  (ie, entries might have different byte counts, but the character
        counts will remain identical until the last one.)
    
        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s pointer to string
        \param[in] n length of the string
        \param[in] width    number of characters to wrap at.
    */
    std::vector<std::string_view>  hard_wrap(const char*s, size_t n, size_t width);
    
    /*! \brief Hard wrap at the given size
    
        A hard wrap will break mid-word as necessary, and is based on the number of UTF-8 
        character code points.  (ie, entries might have different byte counts, but the character
        counts will remain identical until the last one.)
    
        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        \param[in] width    number of characters to wrap at.
    */
    std::vector<std::string_view>  hard_wrap(std::string_view s, size_t width);

    /*! \brief Tests for emptiness
    
        \return TRUE if BOTH first & second are empty
    */
    inline bool is_empty(const string_view_pair_t& p)
    {
        return p.first.empty() && p.second.empty();
    }

    
    bool        is_equal(std::string_view, std::string_view);

    /*! \brief Tests if b > a ignoring case
    
        This ignores case differences as it compares strings a & b.
    */
    bool  is_greater_igCase(std::string_view a, std::string_view b);
    
    
    /*! \brief Test to see if string matches the pattern
    
        (this one is here so it signature matches the other
    */
    bool  is_in(std::string_view str, std::string_view pat);

    /*! \brief Test to see if string matches one of the patterns
    */
    bool  is_in(std::string_view str, std::initializer_list<std::string_view> pat);
    
    /*! \brief Test to see if string matches one of the patterns
    */
    bool  is_in(std::string_view str, const string_view_set_t& pat);

    /*! \brief Test to see if string matches one of the patterns
    */
    bool  is_in(std::string_view str, const std::vector<std::string_view>& pat);

    /*! \brief Tests if b < a ignoring case
    
        This ignores case differences as it compares strings a & b.
    */
    bool  is_less_igCase(std::string_view a, std::string_view b);

    bool  is_less_igCase_u8(std::string_view a, std::string_view b);


    /*! \brief Tests for equality while ignoring case
    */
    bool  is_similar(char, char);


    /*! \brief Tests for equality while ignoring case
    */
    bool  is_similar(std::string_view, std::string_view);


    
    /*! \brief Tests for a valid key
    
        Test for a valid key, one that can be a component of a full key.  Directory paths, 
        extensions, are not tolerated by this routine.  A valid key is one that starts with
        a letter or a number, and is followed by an unlimited number of letters, 
        numbers, "_", "+", or "-".
    */
    bool        is_valid_key(std::string_view);
    
    

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

    /*! \brief Checks to see if the haystack matches the pattern at position
    
        \note Check will end at the length pattern, so "matches_at("foobar rocks", 3, "bar")" will be TRUE
    */
    bool        matches_at(std::string_view haystack, size_t pos, std::string_view pattern);

    /*! \brief Checks to see if the haystack matches the pattern at position
    
        \note Check will end at the length pattern, so "matches_at("foobar rocks", 3, "bar")" will be TRUE
    */
    bool        matches_at_igCase(std::string_view haystack, size_t pos, std::string_view pattern);
    
    /*! \brief Left pads the result until the character count is met */
    std::string     pad_left(std::string_view data, size_t minSize, char ch=' ');
    
    /*! \brief Left pads the result until the character count is met */
    std::string     pad_left(std::string_view data, size_t minSize, char32_t ch);

    /*! \brief Right pads the result until the character count is met */
    std::string     pad_right(std::string_view data, size_t minSize, char ch=' ');

    /*! \brief Right pads the result until the character count is met */
    std::string     pad_right(std::string_view data, size_t minSize, char32_t ch);
    
    //! Will *attempt* to make a plural form, won't be perfect
    std::string     pluralize(std::string_view);
    
    /*! \brief Replaces all instances of old character with new character */
    size_t          replace_all(std::string&, char what, char with);
    
    /*! \brief Replaces all instances of old character with new character ignoring case */
    size_t          replace_all_igCase(std::string&, char what, char with);

    /*! \brief Set left to right if left is empty OR override is true
    
        \note if B is empty, this is a NOP
    */
    std::string&    set_if_empty(std::string&, std::string_view, bool fOverride=false);
    
    /*! \brief Simplifies the given string
    
        Simplifying a string removes start & end whitespace, replaces interior spaces with a single space character.
    */
    std::string     simplify(const char*s, size_t n, char sp=' ');

    /*! \brief Simplifies the given string
    */
    std::string     simplify(std::string_view, char sp=' ');

 

    /*! \brief Strips the LAST extension
    
        This returns the input MINUS the last extension, call repeatedly to remove more than one.
    */
    std::string_view    strip_extension(std::string_view);

    /*! \brief Strips ALL spaces from the input
    */
    std::string  strip_spaces(const char* s, size_t n);

    /*! \brief Strips ALL spaces from the input
    */
    std::string  strip_spaces(std::string_view);
    

    
    /*! \brief Returns the character-array as a string.
    */
    std::string   to_string(const char32_t*);


    
    /*! Converts the string view to string string view
    
        Yes, there's a constructor, however, this is for the template (below);  Copy 
    */
    inline std::string_view  to_string(std::string_view s)
    {
        return s;
    }

    /*! No-op string to string, for templates
    
        Yes, there's a constructor, however, this is for the template (below);
    */
    inline const std::string&  to_string(const std::string& s)
    {
        return s;
    }

    /*! \brief Converts u32string to std::string
    */
    std::string         to_string(const std::u32string&s);
    
    /*! \brief Converts to std::string
    */
    std::string         to_string(const std::u32string_view&s);

    /*! \brief Converts wstring to std::string
    */
    std::string         to_string(const std::wstring&);

    /*! \brief Converts wstring_view to std::string
    */
    std::string         to_string(const std::wstring_view&);


    /*! \brief Concatenates vector of T to std::string
    */
    template <typename T>
    auto  to_string(const std::vector<T>& input)
    {
        using ret_t  = decltype(to_string(T()));
        Vector<ret_t>   ret;
        ret.reserve(input.size());
        for(auto& i : input)
            ret << to_string(i);
        return ret;
    }

    /*! \brief Returns the character-array as a string.
    */
    inline std::string_view  to_string_view(const char*z)
    {
        return std::string_view(z);
    }


    //! Simple to-string-view for a string
    //!
    //! Yes, it's defined on the class, however, this allows for templated "T" expectations to work
    inline std::string_view to_string_view( const std::string& sv)
    {
        return sv;
    }

    //! Simple to-string-view for a string_view
    //!
    //! Yes, it's a noop, however, this allows for templated "T" expectations to work
    inline std::string_view to_string_view( std::string_view sv)
    {
        return sv;
    }
    
    /*! \brief Converts to std::string_view
    */
    std::string_view    to_string_view(const std::u8string_view&s);
    
    /*! \brief Converts the string set to a string view set
        \note Contents of the return set are REFERENCES to the original set data
    */
    string_view_set_t   to_string_view_set(const string_set_t&);

    
    std::u32string      to_u32string(std::string_view);


    /*! \brief String not starting/ending with spaces
    */
    std::string_view    trimmed(std::string_view);
    
    /*! \brief String not starting/ending with specified character
    
    */
    std::string_view    trimmed(std::string_view, char);

    /*! \brief String not ending with whitespaces
    */
    std::string_view    trimmed_end(std::string_view);
    
    /*! \brief String not ending with whitespaces specified character
    */
    std::string_view    trimmed_end(std::string_view, char);

    /*! \brief String not starting with whitespace
    */
    std::string_view    trimmed_start(std::string_view);
    
    /*! \brief String not starting with whitespace specified character
    */
    std::string_view    trimmed_start(std::string_view, char);
    
    /*! \brief Web decodes (with %) the string
    */
    std::string     web_decode(std::string_view);
    
    StringMultiMap  web_decode(StringViewMultiMap);
    
    /*! \brief Web encodes (with %) the string
    */
    std::string     web_encode(std::string_view);

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  IMPLEMENTATION
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    
    template <typename T>
    static constexpr const bool     has_to_string_view_v    = std::is_same_v<std::string_view, decltype(to_string_view(T()))>;

    template <typename T>
    static constexpr const bool     has_to_string_v    = std::is_same_v<std::string, decltype(to_string(T()))>;
    

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

    /*! \brief To string when we have a to-string-view function
    */
    template <typename T>
    //requires (std::is_same_v<std::string_view, to_string_view(T())>)
    std::string    to_string(const T& v)
    {
        return std::string(to_string_view(v));
    }
}


