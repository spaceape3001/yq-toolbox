////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <span>
#include <system_error>

namespace yq {
    
    class Any;
    class ArgMeta;

    /*! \brief Any Argument Helper
    
        Simple class to help with presenting Any argument as bunch of void* 
        pointers for indirect function calls.
        
        \note the ANYs are assumed to remain valid!
    */
    class AnyArgHelper {
    public:
    
        AnyArgHelper();
        ~AnyArgHelper();
    
        std::error_code     construct(std::span<const ArgMeta* const> spec, const std::span<const Any> data);
    
        operator const void* const *() const { return m_pointers.data(); }
        size_t      size() const { return m_pointers.size(); }
        bool        empty() const { return m_pointers.empty(); }
    
    private:
        std::vector<const void*>    m_pointers;
        std::vector<Any>            m_data;
        bool                        m_constructed   = false;
        
        AnyArgHelper(const AnyArgHelper&) = delete;
        AnyArgHelper(AnyArgHelper&&) = delete;
        AnyArgHelper& operator=(const AnyArgHelper&) = delete;
        AnyArgHelper& operator=(AnyArgHelper&&) = delete;
    };
}

