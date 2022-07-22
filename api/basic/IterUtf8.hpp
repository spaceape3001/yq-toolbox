////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//#include <basic/preamble.hpp>
#include <basic/trait/always_false.hpp>
#include <cassert>
#include <cuchar>
#include <cwchar>
#include <charconv>
#include <string>
#include <string_view>

namespace yq {
    /*! Decodes one CHARACTER to a unicode string
    
        This may be multiple bytes, if those bytes are missing, it's considered an error
        and (-1) is returned.
        
        \return Number of bytes this character consumed
    */
    int utf8_decode(char32_t&, const char*, size_t);

    /*! \brief Used to iterate through the string as char32_t
        \note This stores a REFERENCE to the string!  and do NOT modify the string
    */
    class IterUtf8 {
    public:
        IterUtf8(std::string_view s) : IterUtf8(s.data(), s.size()) {}
        IterUtf8(IterUtf8&&) = default;
        IterUtf8&  operator=(IterUtf8&&) = default;
        
        char32_t  next()
        {
            char32_t ret = 0;
            if(m_data && (m_data < m_end) && !m_error){
                int len = utf8_decode(ret, m_data, m_end-m_data);
                if(len > 0){
                    m_data     += len;
                } else {
                    m_error     = true;
                }
            }
            return ret;
        }
        
        size_t  position() const
        {
            return m_data - m_begin;
        }
        
        bool  done() const { return m_data >= m_end; }
        bool  more() const { return (m_data < m_end) && !m_error; }
        bool  error() const { return m_error; }
        
        operator bool () const { return more(); }
        operator const char*() const { return m_data; }
        
        constexpr IterUtf8(const char*z, size_t n) :
            m_begin(z), 
            m_data(z), 
            m_end(z+n), 
            m_error(false)
        {
            assert(z || !n);
        }
        
    private:
        IterUtf8(std::string_view&&) = delete;
        IterUtf8(const IterUtf8&) = delete;
        IterUtf8& operator=(const IterUtf8&) = delete;
        
        const char*     m_begin;
        const char*     m_data;
        const char*     m_end;
        bool            m_error;
    };
    
    
    /*! \brief Iterates across string
    
        This iterates the string, calling the provided predicate for every char32_t value.
        
        \param[in] pred The predicate
        
        Current forms... for a boolean return, allows for abort.   
    */
    template <typename Pred>
    bool  iter_utf8(const char* s, size_t n, Pred pred)
    {
        const char* p   = s;
        const char* e   = p + n;
        char32_t     wc = 0;
        int          len = 0;

        while((p < e) && ((len = utf8_decode(wc, p, e-p)) > 0)){
            if constexpr (std::is_invocable_v<Pred, char32_t>){
                    // In this case, a simple character
                pred(wc);
            } else if constexpr (std::is_invocable_v<Pred, const char*, char32_t>){
                    // Want the pointer & character
                pred(p, wc);
            } else if constexpr (std::is_invocable_v<Pred, const char*, int, char32_t>){
                    // Want the pointer, length, & character
                pred(p, len, wc);
            } else if constexpr (std::is_invocable_v<Pred, const char*, int>){
                    // Want the pointer & length
                pred(p, len);
            } else {
                static_assert(trait::always_false_v<Pred>, "Argument deduction failed");
            }
            p += len;
        }
        return p == e;
    }
    
    /*! \brief Iterates across string
    
        This iterates the string, calling the provided predicate for every char32_t value.
    */
    template <typename Pred>
    bool  iter_utf8(const std::string_view&s, Pred pred)
    {
        return iter_utf8(s.data(), s.size(), pred);
    }
    

    /*! \brief Iterates across string with abort
    
        This iterates the string, calling the provided predicate for every char32_t value.
        Predicate returning FALSE will abort the iteration.
    */
    template <typename Pred>
    bool  iter_utf8_abort(const char* s, size_t n, Pred pred)
    {
        const char* p   = s;
        const char* e   = p + n;
        char32_t     wc = 0;
        int          len = 0;

        while((p < e) && ((len = utf8_decode(wc, p, e-p)) > 0)){
            if constexpr (std::is_invocable_r_v<bool, Pred, char32_t>){
                if(!pred(wc))
                    break;
            } else if constexpr (std::is_invocable_r_v<bool, Pred, const char*, char32_t>){
                    // Want the pointer & character
                if(!pred(p, wc))
                    break;
            } else if constexpr (std::is_invocable_r_v<bool, Pred,  const char*, int, char32_t>){
                    // Want the pointer, length, & character
                if(!pred(p, len, wc))
                    break;
            } else if constexpr (std::is_invocable_r_v<bool, Pred, const char*, int>){
                    // Want the pointer & length
                if(!pred(p, len))
                    break;
            } else {
                static_assert(trait::always_false_v<Pred>, "Argument deduction failed");
            } 
            p += len;
        }
        return p == e;
    }
    

    /*! \brief Iterates across string with abort
    
        This iterates the string, calling the provided predicate for every char32_t value.
        Predicate returning FALSE will abort the iteration.
    */
    template <typename Pred>
    bool  iter_utf8_abort(const std::string_view&s, Pred pred)
    {
        return iter_utf8_abort(s.data(), s.size(), pred);
    }

    /*! \brief Filters by accepting characters
        
        This iterates the string, building a new string with char32_t that have been 
        accepted by the predicate (ie, returns true).
    */
    template <typename Pred>
    std::string  iter_utf8_accept(const char* s, size_t n, Pred pred)
    {
    
        std::string      ret;
        if(s && n){
            ret.reserve(n);
            const char* p   = s;
            const char* e   = p + n;
            char32_t     wc = 0;
            int         len = 0;

            while((p < e) && ((len = utf8_decode(wc, p, e-p)) > 0)){
                if constexpr (std::is_invocable_r_v<bool, Pred, char32_t>){
                    if(pred(wc))
                        ret.append(p, len);
                } else {
                    static_assert(trait::always_false_v<Pred>, "Argument deduction failed");
                } 
                p += len;
            }
        }
        return ret;
    }
    
    /*! \brief Filters by accepting characters
        
        This iterates the string, building a new string with char32_t that have been 
        accepted by the predicate (ie, returns true).
    */
    template <typename Pred>
    std::string  iter_utf8_accept(const std::string_view&s, Pred pred)
    {
        return iter_utf8_accept(s.data(), s.size(), pred);
    }
    
    /*! \brief Iterates across string with find
    
        This iterates the string, calling the provided predicate for every char32_t value.
        Predicate returning FALSE will abort the iteration.
    */
    template <typename Pred>
    const char*  iter_utf8_find(const char* s, size_t n, Pred pred)
    {
        const char* p   = s;
        const char* e   = p + n;
        char32_t     wc = 0;
        int          len = 0;

        while((p < e) && ((len = utf8_decode(wc, p, e-p)) > 0)){
            if constexpr (std::is_invocable_r_v<bool, Pred, char32_t>){
                if(pred(wc))
                    return p;
            } else {
                static_assert(trait::always_false_v<Pred>, "Argument deduction failed");
            }
            p += len;
        }
        return nullptr;
    }


    /*! \brief Filters by rejecting characters
        
        This iterates the string, building a new string with char32_t that have not been 
        rejected by the predicate (ie, returns true).
    */
    template <typename Pred>
    std::string  iter_utf8_reject(const char* s, size_t n, Pred pred)
    {
    
        std::string      ret;
        if(s && n){
            ret.reserve(n);
            const char* p   = s;
            const char* e   = p + n;
            char32_t     wc = 0;
            int         len = 0;

            while((p < e) && ((len = utf8_decode(wc, p, e-p)) > 0)){
                if constexpr (std::is_invocable_r_v<bool, Pred, char32_t>){
                    if(!pred(wc))
                        ret.append(p, len);
                } else {
                    static_assert(trait::always_false_v<Pred>, "Argument deduction failed");
                } 
                p += len;
            }
        }
        return ret;
    }
    
    /*! \brief Filters by rejecting characters
        
        This iterates the string, building a new string with char32_t that have not been 
        rejected by the predicate (ie, returns true).
    */
    template <typename Pred>
    std::string  iter_utf8_reject(const std::string_view& s, Pred pred)
    {
        return iter_utf8_reject(s.data(), s.size(), pred);
    }
    
    
}
