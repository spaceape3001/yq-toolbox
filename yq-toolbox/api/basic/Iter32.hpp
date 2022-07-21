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

    /*! \brief Used to iterate through the string as char32_t
        \note This stores a REFERENCE to the string!  and do NOT modify the string
    */
    class Iter32 {
    public:
        Iter32(std::string_view s) : Iter32(s.data(), s.size()) {}
        Iter32(Iter32&&) = default;
        Iter32&  operator=(Iter32&&) = default;
        
        char32_t  next()
        {
            char32_t ret = 0;
            if(m_data && (m_data < m_end) && !m_error){
                int len = std::mbrtoc32(&ret, m_data, m_end-m_data, &m_state);
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
        
        constexpr Iter32(const char*z, size_t n) :
            m_begin(z), 
            m_data(z), 
            m_end(z+n), 
            m_state{},
            m_error(false)
        {
            assert(z || !n);
        }
        
    private:
        Iter32(std::string_view&&) = delete;
        Iter32(const Iter32&) = delete;
        Iter32& operator=(const Iter32&) = delete;
        
        const char*     m_begin;
        const char*     m_data;
        const char*     m_end;
        std::mbstate_t  m_state;
        bool            m_error;
    };
    
    
    /*! \brief Iterates across string
    
        This iterates the string, calling the provided predicate for every char32_t value.
        
        \param[in] pred The predicate
        
        Current forms... for a boolean return, allows for abort.   
    */
    template <typename Pred>
    bool  iter32(const char* s, size_t n, Pred pred)
    {
        const char* p   = s;
        const char* e   = p + n;
        std::mbstate_t  state{};
        char32_t     wc = 0;
        int          len = 0;

        while((p < e) && ((len = std::mbrtoc32(&wc, p, e-p, &state)) > 0)){
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
    bool  iter32(const std::string_view&s, Pred pred)
    {
        return iter32(s.data(), s.size(), pred);
    }
    

    /*! \brief Iterates across string with abort
    
        This iterates the string, calling the provided predicate for every char32_t value.
        Predicate returning FALSE will abort the iteration.
    */
    template <typename Pred>
    bool  iter32_abort(const char* s, size_t n, Pred pred)
    {
        const char* p   = s;
        const char* e   = p + n;
        std::mbstate_t  state{};
        char32_t     wc = 0;
        int          len = 0;

        while((p < e) && ((len = std::mbrtoc32(&wc, p, e-p, &state)) > 0)){
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
    bool  iter32_abort(const std::string_view&s, Pred pred)
    {
        return iter32_abort(s.data(), s.size(), pred);
    }

    /*! \brief Filters by accepting characters
        
        This iterates the string, building a new string with char32_t that have been 
        accepted by the predicate (ie, returns true).
    */
    template <typename Pred>
    std::string  iter32_accept(const char* s, size_t n, Pred pred)
    {
    
        std::string      ret;
        if(s && n){
            ret.reserve(n);
            const char* p   = s;
            const char* e   = p + n;
            std::mbstate_t  state{};
            char32_t     wc = 0;
            int         len = 0;

            while((p < e) && ((len = std::mbrtoc32(&wc, p, e-p, &state)) > 0)){
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
    std::string  iter32_accept(const std::string_view&s, Pred pred)
    {
        return iter32_accept(s.data(), s.size(), pred);
    }
    
    /*! \brief Iterates across string with find
    
        This iterates the string, calling the provided predicate for every char32_t value.
        Predicate returning FALSE will abort the iteration.
    */
    template <typename Pred>
    const char*  iter32_find(const char* s, size_t n, Pred pred)
    {
        const char* p   = s;
        const char* e   = p + n;
        std::mbstate_t  state{};
        char32_t     wc = 0;
        int          len = 0;

        while((p < e) && ((len = std::mbrtoc32(&wc, p, e-p, &state)) > 0)){
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
    std::string  iter32_reject(const char* s, size_t n, Pred pred)
    {
    
        std::string      ret;
        if(s && n){
            ret.reserve(n);
            const char* p   = s;
            const char* e   = p + n;
            std::mbstate_t  state{};
            char32_t     wc = 0;
            int         len = 0;

            while((p < e) && ((len = std::mbrtoc32(&wc, p, e-p, &state)) > 0)){
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
    std::string  iter32_reject(const std::string_view& s, Pred pred)
    {
        return iter32_reject(s.data(), s.size(), pred);
    }
    
    
}
