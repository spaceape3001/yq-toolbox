////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/preamble.hpp>

namespace yq {

    /*! \brief Light weight Key-Value structure
    */
    template <typename T>
    struct BasicKV {
        T       key, value;
        bool    empty() const { return key.empty() && value.empty(); }
        bool    operator==(const BasicKV&) const = default;
    };
    
    //! Key-value alias
    using KV        = BasicKV<std::string>;

    //! Key-value alias
    using KVView    = BasicKV<std::string_view>;

    //! Key-value map alias
    using KVVMMap   = MultiMap<std::string_view, std::string_view, IgCase>;
}
