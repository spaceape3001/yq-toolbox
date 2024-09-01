////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/text/basics32.hpp>

namespace yq {


    /*! \brief Split via visitor pattern
    
        This "splits" the u32string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the u32string
        \param[in]      n    Length of the u32string (in bytes)
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::u32string_view.
    */
    template <typename Pred>
    auto            vsplit(const char32_t* s, size_t n, char32_t ch, Pred pred)
    {
        using return_t  = decltype(pred(std::u32string_view()));
        if(s && n){
            const char32_t* end = s + n;
            const char32_t* i   = nullptr;
            const char32_t* j   = nullptr;
            for(i = s; (j = strnchr(i, end-i, ch)); i = j+1){
                if constexpr (!std::is_same_v<return_t, void>){
                    return_t    t   = pred(std::u32string_view(i, j));
                    if(t != return_t())
                        return t;
                } else
                    pred(std::u32string_view(i,j));
            }
            return pred(std::u32string_view(i, end));
        }
        return return_t();
    }

    /*! \brief Split via visitor pattern
    
        This "splits" the u32string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the u32string
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::u32string_view.
    */
    template <typename Pred>
    auto            vsplit(const char32_t* s, char32_t ch, Pred pred)
    {
        using return_t = decltype(vsplit(s, strlen(s), ch, pred));
        if(s)
            return vsplit(s, strlen(s), ch, pred);
        return return_t();
    }

    /*! \brief Split via visitor pattern
    
        This "splits" the u32string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::u32string_view.
    */
    template <typename Pred>
    auto            vsplit(std::u32string_view s, char32_t ch, Pred pred)
    {
        return vsplit(s.data(), s.size(), ch, pred);
    }
    
    /*! \brief Split via visitor pattern
    
        This "splits" the u32string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the u32string
        \param[in]      n    Length of the u32string (in bytes)
        \param[in]      p    Pattern to split on
        \param[in]      pn   Length of the pattern (in bytes)
        \param[in,out]  pred Function-like object, taking a std::u32string_view.
    */
    template <typename Pred>
    void            vsplit(const char32_t* s, size_t n, const char32_t* p, size_t pn, Pred pred)
    {
        if(s && n && p && pn){
            const char32_t* end = s + n;
            const char32_t* i   = nullptr;
            const char32_t* j   = nullptr;
            for(i = s; (j = strnstr(i, end-i, p, pn)); i = j+1)
                pred(std::u32string_view(i, j-i));
            pred(std::u32string_view(i, end-i));
        }
    }
    
    /*! \brief Split via visitor pattern
    
        This "splits" the u32string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      p    String view to split on
        \param[in,out]  pred Function-like object, taking a std::u32string_view.
    */
    template <typename Pred>
    void            vsplit(std::u32string_view s, std::u32string_view pattern, Pred pred)    
    {
        vsplit(s.data(), s.size(), pattern.data(), pattern.size(), pred);
    }
    
    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the u32string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the u32string
        \param[in]      n    Length of the u32string (in bytes)
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::u32string_view.
    */

    template <typename Pred>
    void            vsplit_igCase(const char32_t* s, size_t n, char32_t ch, Pred pred)
    {
        if(s && n){
            const char32_t* end = s + n;
            const char32_t* i   = nullptr;
            const char32_t* j   = nullptr;
            for(i = s; (j = strnchr_igCase(i, end-i, ch)); i = j+1)
                pred(std::u32string_view(i, j-i));
            pred(std::u32string_view(i, end-i));
        }
    }

    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the u32string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::u32string_view.
    */
    template <typename Pred>
    void            vsplit_igCase(std::u32string_view s, char32_t ch, Pred pred)
    {
        vsplit_igCase(s.data(), s.size(), pred);
    }

    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the u32string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the u32string
        \param[in]      n    Length of the u32string (in bytes)
        \param[in]      p    Pattern to split on
        \param[in]      pn   Length of the pattern (in bytes)
        \param[in,out]  pred Function-like object, taking a std::u32string_view.
    */
    template <typename Pred>
    void            vsplit_igCase(const char32_t* s, size_t n, const char32_t* p, size_t pn, Pred pred)
    {
        if(s && n && p && pn){
            const char32_t* end = s + n;
            const char32_t* i   = nullptr;
            const char32_t* j   = nullptr;
            for(i = s; (j = strnstr_igCase(i, end-i, p, pn)); i = j+1)
                pred(std::u32string_view(i, j-i));
            pred(std::u32string_view(i, end-i));
        }
    }
    
    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the u32string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      p    String view to split on
        \param[in,out]  pred Function-like object, taking a std::u32string_view.
    */
    template <typename Pred>
    void            vsplit_igCase(std::u32string_view s, std::u32string_view pattern, Pred pred)    
    {
        vsplit_igCase(s.data(), s.size(), pattern.data(), pattern.size(), pred);
    }
}
