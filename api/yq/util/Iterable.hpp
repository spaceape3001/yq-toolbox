////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <utility>
#include <type_traits>

namespace yq {
    template <typename Iterator>
    struct Iterable {
        using iterator_type = Iterator;
        Iterator    m_begin, m_end;
        Iterator    begin() const { return m_begin; }
        Iterator    end() const { return m_end; }
    };
    
    template <typename Iterator>
    constexpr auto as_iterable(const std::pair<Iterator, Iterator>& p)
    {
        return Iterable<Iterator>{p.first, p.second};
    }
    
    template <typename Iterator>
    constexpr auto as_iterable(Iterator a, std::type_identity_t<Iterator> b)
    {
        return Iterable<Iterator>{a, b};
    }
}
