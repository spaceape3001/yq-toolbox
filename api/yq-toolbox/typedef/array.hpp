////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {
    template <typename I, uint8_t N, bool ORIGIN, bool GHOST> struct ArrayConfig;
    
    template <typename I> using BasicAC1    = ArrayConfig<I, 1, false, false>;
    template <typename I> using BasicAC2    = ArrayConfig<I, 2, false, false>;
    template <typename I> using BasicAC3    = ArrayConfig<I, 3, false, false>;
    template <typename I> using BasicAC4    = ArrayConfig<I, 4, false, false>;
    template <typename I> using BasicAC5    = ArrayConfig<I, 5, false, false>;
    template <typename I> using BasicAC6    = ArrayConfig<I, 6, false, false>;
    
    template <typename I> using GhostAC1    = ArrayConfig<I, 1, true, true>;
    template <typename I> using GhostAC2    = ArrayConfig<I, 2, true, true>;
    template <typename I> using GhostAC3    = ArrayConfig<I, 3, true, true>;
    template <typename I> using GhostAC4    = ArrayConfig<I, 4, true, true>;
    template <typename I> using GhostAC5    = ArrayConfig<I, 5, true, true>;
    template <typename I> using GhostAC6    = ArrayConfig<I, 6, true, true>;
    
    template <typename I> using OriginAC1   = ArrayConfig<I, 1, true, false>;
    template <typename I> using OriginAC2   = ArrayConfig<I, 2, true, false>;
    template <typename I> using OriginAC3   = ArrayConfig<I, 3, true, false>;
    template <typename I> using OriginAC4   = ArrayConfig<I, 4, true, false>;
    template <typename I> using OriginAC5   = ArrayConfig<I, 5, true, false>;
    template <typename I> using OriginAC6   = ArrayConfig<I, 6, true, false>;
    
    template <typename DATA, typename COORDSYS> class Array;
    
    template <typename T, typename I=unsigned int> using Array1 = Array<T, BasicAC1<I>>;
    template <typename T, typename I=unsigned int> using Array2 = Array<T, BasicAC2<I>>;
    template <typename T, typename I=unsigned int> using Array3 = Array<T, BasicAC3<I>>;
    template <typename T, typename I=unsigned int> using Array4 = Array<T, BasicAC4<I>>;
    template <typename T, typename I=unsigned int> using Array5 = Array<T, BasicAC5<I>>;
    template <typename T, typename I=unsigned int> using Array6 = Array<T, BasicAC6<I>>;

    template <typename T, typename I=int> using ZArray1 = Array<T, OriginAC1<I>>;
    template <typename T, typename I=int> using ZArray2 = Array<T, OriginAC2<I>>;
    template <typename T, typename I=int> using ZArray3 = Array<T, OriginAC3<I>>;
    template <typename T, typename I=int> using ZArray4 = Array<T, OriginAC4<I>>;
    template <typename T, typename I=int> using ZArray5 = Array<T, OriginAC5<I>>;
    template <typename T, typename I=int> using ZArray6 = Array<T, OriginAC6<I>>;

    template <typename T, typename I=int> using ZGArray1 = Array<T, GhostAC1<I>>;
    template <typename T, typename I=int> using ZGArray2 = Array<T, GhostAC2<I>>;
    template <typename T, typename I=int> using ZGArray3 = Array<T, GhostAC3<I>>;
    template <typename T, typename I=int> using ZGArray4 = Array<T, GhostAC4<I>>;
    template <typename T, typename I=int> using ZGArray5 = Array<T, GhostAC5<I>>;
    template <typename T, typename I=int> using ZGArray6 = Array<T, GhostAC6<I>>;
}
