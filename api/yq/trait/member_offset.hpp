////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>

namespace yq {
    template<class T, typename U>
    size_t member_offset(U T::* member)
    {
        //  UGLY hack to get an offset for a member pointer
        //  credit to https://stackoverflow.com/questions/5617251/offset-of-pointer-to-member
        //  top answer
        return reinterpret_cast<size_t>(&(reinterpret_cast<T*>((void*) 0)->*member));
    }    
}
