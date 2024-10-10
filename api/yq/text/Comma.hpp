////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string_view>

namespace yq {

    /*! \brief Sequence generator for commas
    
        Used when you need commas.
    */
    class Comma {
    public:
        Comma(const std::string_view& sep=", ") : m_separator(sep), m_first(true) {}
        
        
        /*! \brief Text
        
            On first call, this will be blank.  On subsequent calls, it'll have the separator 
        */
        const std::string_view&       text() const
        {
            static const std::string_view s_blank   = "";
            return m_first ? s_blank : m_separator;
        }
        
        //! Advances the sequence
        Comma&              operator++()
        {
            m_first = false;
            return *this;
        }
        
    private:
        std::string_view    m_separator;
        bool                m_first;
    };
}
