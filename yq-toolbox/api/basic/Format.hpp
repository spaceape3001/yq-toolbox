////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>
#include <basic/trait/not_copyable.hpp>


/*! Lightly formatting string

    Qt has it's .arg().  Anyways, we won't worry about recursive expansion here, simple %1 %2 etc.  
*/    


namespace yq {

    /*! \brief Simple string format
    
        This is a simple formatter, where the input string is parsed ONCE, stored for
        Further use (or use std::format... which will become the preferred TBH)
    */
    class Format : trait::not_copyable {
    public:

        class Args;

        //  Need a syntax...
        //  %(number)   Will join
        //  %+          Concatentate (in case of immediate number)
        //  %%          Percent
        
        
        //!  Assuming this is a compiled string or similarly stable source
        Format(std::string_view );    // will NOT store a copy
        Format(std::string&&);        // WILL store

            // MOVING is the way
        Format(Format&&) = default;
        Format& operator=(Format&&) = default;
        
        ~Format() = default;
        
        
        template <typename ... T>
        Args  arg(T... args) const;
        
        
    private:
        struct Token {
            std::string_view        bit;
            unsigned int            id  = ~0;
            
            constexpr Token() = default;
            constexpr Token(std::string_view b) : bit(b) {}
            constexpr Token(unsigned int i) : id(i) {}
        };

        std::string                 m_input;    // not always used... a string view/char* will NOT set this
        std::vector<Token>          m_tokens;   //  ZERO means no-tokens
        unsigned int                m_max   = 0;
        
        void parse(const char*, size_t);
    };

    Format operator ""_fmt(const char* z) { return Format(std::string_view(z)); }


    class Format::Args {
    public:

        Args&     arg(std::string_view );
        Args&     arg(bool, const char* szTrue="true", const char* szFalse="false");

        std::string          string() const;
        operator std::string() const { return string(); }


    private:
        friend class Format;
        Args(const Format*);
        const Format*               m_format    = nullptr;
        std::vector<std::string>  m_args;
        void    push(std::string_view );
    };


    template <typename ... T>
    Format::Args  Format::arg(T... args) const
    {
        Args ret(this);
        ret.arg(args...);
        return ret;
    }

}
