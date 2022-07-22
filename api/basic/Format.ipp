////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Format.hpp"
#include <basic/CollectionUtils.hpp>
#include <basic/Map.hpp>
#include <charconv>

namespace yq {


    Format::Format(std::string_view  str)
    {
        parse(str.data(), str.size());
    }


    Format::Format(std::string&& str) : m_input(std::move(str))
    {
        if(!m_input.empty()){
            parse(m_input.data(), m_input.size());
        }
    }

    //Format& Format::arg(std::string_view v)
    //{
        //m_output += v;
        //if(!m_left.empty())
            
    //}

    void    Format::parse(const char* z, size_t n)
    {
        if(!z)
            return;
        if(!*z)
            return;
        if(!n)
            return ;

        size_t  per=0;
        size_t  i;
        for(i=0;i<n;++i){ // estimate the tokens
            if(z[i] == '%')
                ++per;
        }
                
        m_tokens.reserve(per + 1);
        if(!per){               // no chance of a token, make it all none
            m_tokens << Token{{z, n}};
            return ;
        }
        
        size_t          j       = ~0;    // usage for tracking
        bool            inper   = false;
        
        auto token  = [&](){
            if(j+1 < i){
                if(inper){
                    unsigned int k = 0;
                    auto    r   = std::from_chars(z+j+1, z+i, k);
                    if(r.ec == std::error_code())
                        m_tokens << Token(k);
                } else 
                    m_tokens << Token(std::string_view(z+j, i-j));
            }
            j       = i;
        };
        
        //  reusing per for decoding percentage
        for(i=0; z[i] && (i<n); ++i){
            if(inper){
                if(!isdigit(z[i])){
                    //  pass it on, start new token
                    j       = i;
                    inper  = false;
                }
            } else if(z[i] == '%'){
                token();
                inper = true;
            }
        }

        token();
        
        //  Now, reordering the numbers
        Map<size_t, size_t>                 rmap;
        for(Token& t : m_tokens){
            if(t.id != ~0U)
                rmap[t.id]  = 0;
        }
        unsigned int    m   = 0;
        for(auto& r : rmap)
            r.second    = ++m;
        for(Token& t : m_tokens)
            t.id        = rmap.get(t.id);
        m_max       = ++m;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    Format::Args::Args(const Format*f) : m_format(f) 
    { 
        m_args.reserve(m_format->m_max);
        m_args << std::string(); 
    }

    void    Format::Args::push(std::string_view s)
    {
        if(m_args.size() < m_format->m_max)
            m_args << std::string(s);
    }

    Format::Args&     Format::Args::arg(std::string_view  s)
    {
        push(s);
        return *this;
    }

    Format::Args&     Format::Args::arg(bool v, const char* szTrue, const char* szFalse)
    {
        push( { v ? szTrue : szFalse });
        return *this;
    }

    std::string          Format::Args::string() const
    {
        size_t  cnt = 0;
        std::vector<std::string_view>  bits;
        bits.reserve(m_format->m_tokens.size());
        for(auto& t : m_format -> m_tokens){
            if(t.id){
                if(t.id < m_args.size()){
                    auto & k = m_args[t.id];
                    bits << std::string_view(k);
                    cnt += k.size();
                }
            } else {
                bits << t.bit;
                cnt += t.bit.size();
            }
        }
        
        
        std::string      result;
        if(cnt){
            result.reserve(cnt);
            for(auto&b : bits)
                result += b;
        }
        return result;
    }
}

