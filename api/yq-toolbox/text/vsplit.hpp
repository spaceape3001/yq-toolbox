////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/text/basic.hpp>

namespace yq {

    /*! \brief Split via visitor pattern
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the string
        \param[in]      n    Length of the string (in bytes)
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    auto            vsplit(const char* s, size_t n, char ch, Pred pred)
    {
        using return_t  = decltype(pred(std::string_view()));
        if(s && n){
            const char* end = s + n;
            const char* i   = nullptr;
            const char* j   = nullptr;
            for(i = s; (j = strnchr(i, end-i, ch)); i = j+1){
                if constexpr (!std::is_same_v<return_t, void>){
                    return_t    t   = pred(std::string_view(i, j));
                    if(t != return_t())
                        return t;
                } else
                    pred(std::string_view(i,j));
            }
            return pred(std::string_view(i, end));
        }
        return return_t();
    }

    /*! \brief Split via visitor pattern
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the string
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    auto            vsplit(const char* s, char ch, Pred pred)
    {
        using return_t = decltype(vsplit(s, strlen(s), ch, pred));
        if(s)
            return vsplit(s, strlen(s), ch, pred);
        return return_t();
    }

    /*! \brief Split via visitor pattern
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    auto            vsplit(std::string_view s, char ch, Pred pred)
    {
        return vsplit(s.data(), s.size(), ch, pred);
    }
    
    /*! \brief Split via visitor pattern
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the string
        \param[in]      n    Length of the string (in bytes)
        \param[in]      p    Pattern to split on
        \param[in]      pn   Length of the pattern (in bytes)
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    void            vsplit(const char* s, size_t n, const char* p, size_t pn, Pred pred)
    {
        if(s && n && p && pn){
            const char* end = s + n;
            const char* i   = nullptr;
            const char* j   = nullptr;
            for(i = s; (j = strnstr(i, end-i, p, pn)); i = j+1)
                pred(std::string_view(i, j-i));
            pred(std::string_view(i, end-i));
        }
    }
    
    /*! \brief Split via visitor pattern
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      p    String view to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    void            vsplit(std::string_view s, std::string_view pattern, Pred pred)    
    {
        vsplit(s.data(), s.size(), pattern.data(), pattern.size(), pred);
    }
    
    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the string
        \param[in]      n    Length of the string (in bytes)
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */

    template <typename Pred>
    void            vsplit_igCase(const char* s, size_t n, char ch, Pred pred)
    {
        if(s && n){
            const char* end = s + n;
            const char* i   = nullptr;
            const char* j   = nullptr;
            for(i = s; (j = strnchr_igCase(i, end-i, ch)); i = j+1)
                pred(std::string_view(i, j-i));
            pred(std::string_view(i, end-i));
        }
    }

    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    void            vsplit_igCase(std::string_view s, char ch, Pred pred)
    {
        vsplit_igCase(s.data(), s.size(), pred);
    }

    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the string
        \param[in]      n    Length of the string (in bytes)
        \param[in]      p    Pattern to split on
        \param[in]      pn   Length of the pattern (in bytes)
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    void            vsplit_igCase(const char* s, size_t n, const char* p, size_t pn, Pred pred)
    {
        if(s && n && p && pn){
            const char* end = s + n;
            const char* i   = nullptr;
            const char* j   = nullptr;
            for(i = s; (j = strnstr_igCase(i, end-i, p, pn)); i = j+1)
                pred(std::string_view(i, j-i));
            pred(std::string_view(i, end-i));
        }
    }
    
    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      p    String view to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    void            vsplit_igCase(std::string_view s, std::string_view pattern, Pred pred)    
    {
        vsplit_igCase(s.data(), s.size(), pattern.data(), pattern.size(), pred);
    }
}
