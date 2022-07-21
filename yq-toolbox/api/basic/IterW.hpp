////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
//#include <basic/preamble.hpp>
#include <basic/trait/always_false.hpp>
#include <cassert>

#include <cwchar>
#include <string_view>

namespace yq {
    /*! \brief Stores a REFERENCE to the string!
    */
    class IterW {
    public:

        IterW(const std::string_view&);
        IterW(IterW&&) = default;
        IterW& operator=(IterW&&) = default;

        bool        done() const { return m_data >= m_end; }
        bool        error() const { return m_error; }
        bool        more() const { return (m_data < m_end) && !m_error; }
        wchar_t     next()
        {
            wchar_t ret = 0;
            if((m_data < m_end) && !m_error){
                int len = std::mbrtowc(&ret, m_data, m_end - m_data, &m_state);
                if(len > 0){
                    m_data  += len;
                } else {
                    m_error = true;
                }
            }
            return ret;
        }
        
        size_t      position() const { return m_data - m_begin; }

        IterW(const char*z, size_t n) : 
            m_begin(z), m_data(z), m_end(z+n), m_state{}, m_error(false)
        {
        }
        
    private:
        IterW(std::string&&) = delete;
        IterW(std::string_view&&) = delete;
        IterW(const IterW&) = delete;
        
        const char*     m_begin;
        const char*     m_data;
        const char*     m_end;
        std::mbstate_t  m_state;
        bool            m_error;
    };

    template <typename Pred>
    bool            iterW(const char* s, size_t n, Pred pred) 
    {
        assert(s);
        if(!n)
            return true;
        
        const char* p   = s;
        const char* e   = p + n;
        std::mbstate_t  state{};
        wchar_t         wc = 0;
        int             len = 0;

        while((p < e) && ((len = std::mbrtowc(&wc, p, e-p, &state)) > 0)){
            pred(wc);
            p += len;
        }
        return p == e;
    }

    template <typename Pred>
    bool            iterW(const std::string_view& s, Pred pred) 
    {
        return iterW(s.data(), s.size());
    }
}
