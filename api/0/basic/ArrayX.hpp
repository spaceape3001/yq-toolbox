////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>

namespace yq {

    template <typename Value, typename ... Indices >
    class ArrayXView {
    public:
        static constexpr const size_t   DIMS    = sizeof...(Indices);
    
    private:
        Value*      m_data  = nullptr;
        size_t      m_dims[DIMS];
        ssize_t     m_zero[DIMS];
    
    };
}
