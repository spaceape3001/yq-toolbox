////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Exception.hpp>

namespace yq {
    template <typename Pred>
    void    barf_bag(Barf::Actions acts, Pred&&x)
    {
        // TODO...swallow
        x();
    }

    template <typename Pred>
    void    barf_bag(Barf::ActionList list, Pred&& x)
    {
        barf_bag(Barf::Actions(list), std::move(x));
    }

    template <typename Pred>
    void    barf_bag(Pred x)
    {
        barf_bag(Barf::Actions(Barf::kDefaultActions), std::move(x));
    }

}

