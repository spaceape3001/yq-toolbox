////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Ref.hpp>

namespace yq {
    //! This is a "smarter" pointer, when to keep T alive, a different pointer
    //! must be kept alive too
    template <typename O, typename T>
    struct Ptr {
        Ref<O>      owner;
        T*          pointer = nullptr;

        T*          ptr() 
        {
            return owner ? pointer : (T*) nullptr;
        }

        const T*    ptr() const
        {
            return owner ? pointer : (T*) nullptr;
        }
        
        bool    invalid() const { return ptr() == nullptr; }
        bool    valid() const { return ptr() != nullptr; }
        
        operator T* () { return ptr(); }
        operator const T* () const { return ptr(); }
        
        T*  operator->() { return ptr(); }
        const T*  operator->() const { return ptr(); }
    };
}

