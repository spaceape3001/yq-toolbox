////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>

/*
    2024 SEP 01 -- CSA

        I think this is a stub/prototype, yet to fleshed out idea
*/

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
