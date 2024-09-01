////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <set>

namespace yq {
    /*! \brief Changes in two sets
    
        Simple structure to record the additions, the subtractions, and the same items.
    */
    template <typename T, typename C=std::less<T>, typename A=std::allocator<T>>
    struct SetChanges {
        std::set<T,C,A>     added;      //!< Items that were added
        std::set<T,C,A>     same;       //!< Items that are in both
        std::set<T,C,A>     modified;   //!< Items that were modified (but are otherwise the same)
        std::set<T,C,A>     removed;    //!< Items that were removed
    };
}
