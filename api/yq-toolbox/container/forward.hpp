////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <cstdint>
#include <yq-toolbox/typedef/array.hpp>

namespace yq {
    template <typename T, size_t N> class BitArray;
    class ByteArray;
    template <typename T> class Deque;
    template <typename E, typename V> class EnumMap;
    template <typename K, typename V>   class Hash;
    template <typename> class List;
    template <typename K, typename V, typename C=std::less<K>> class Map;
    template <typename K, typename V, typename C=std::less<K>> class MultiMap;
    template <typename T, typename C=std::less<T>> class Set;
    template <typename T> struct Span;
    template <typename T> class Stack;
    template <typename T> class Vector;
    template <typename T> class PVector;
}
