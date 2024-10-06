////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Pixels.hpp"

#include <yq-toolbox/basic/Any.hpp>
#include <yq-toolbox/coord/Coord.hpp>
#include <yq-toolbox/coord/Coord1.hpp>
#include <yq-toolbox/coord/Coord2.hpp>
#include <yq-toolbox/coord/Coord3.hpp>
#include <yq-toolbox/coord/Coord4.hpp>
#include <yq-toolbox/coord/Coord5.hpp>
#include <yq-toolbox/coord/Coord6.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>
#include <yq-toolbox/meta/TypeInfo.hpp>

namespace yq::pixel {
    template <uint8_t DIMS, class C>
    typename Pixels<DIMS,C>::coord_t     Pixels<DIMS,C>::coord(std::span<const index_t> pix) 
    {
        coord_t ret;
        for(uint8_t n=0;n<kDimensions;++n){
            if(pix.size() > n){
                yq::set(ret, n, pix[n]);
            } else {
                yq::set(ret, n, (index_t) 0);
            }
        }
        return ret;
    }

    template <uint8_t DIMS, class C>
    Pixels<DIMS,C>::Pixels()
    {
    }
    
    template <uint8_t DIMS, class C>
    Pixels<DIMS,C>::Pixels(coord_t cc, const C& def) : array_t(cc, def)
    {
    }
    
    template <uint8_t DIMS, class C>
    Pixels<DIMS,C>::Pixels(coord_t cc, copy_t, const C* pValues) : array_t(cc, COPY, pValues)
    {
    }
    
    template <uint8_t DIMS, class C>
    Pixels<DIMS,C>::~Pixels()
    {
    }

    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::bytes(pixel_t) const 
    { 
        return sizeof(C);
    }
        
    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::bytes(total_t) const 
    {
        return count(PIXELS) * sizeof(C);
    }
    
    template <uint8_t DIMS, class C>
    uint8_t Pixels<DIMS,C>::count(dimensions_t) const 
    {
        return kDimensions;
    }
    
    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::count(i_t) const 
    {
        return count().i;
    }
    
    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::count(j_t) const 
    {
        if constexpr (kDimensions >= 2){
            return count().j;
        } else {
            return 0ULL;
        }
    }
    
    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::count(k_t) const 
    {
        if constexpr (kDimensions >= 3){
            return count().k;
        } else {
            return 0ULL;
        }
    }
    
    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::count(l_t) const 
    {
        if constexpr (kDimensions >= 4){
            return count().l;
        } else {
            return 0ULL;
        }
    }
    
    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::count(m_t) const 
    {
        if constexpr (kDimensions >= 5){
            return count().m;
        } else {
            return 0ULL;
        }
    }
    
    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::count(n_t) const 
    {
        if constexpr (kDimensions >= 6){
            return count().k;
        } else {
            return 0ULL;
        }
    }
    
    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::count(pixels_t) const 
    {
        coord_t     cc  = count();
        size_t      ret = cc.i;
        
        if constexpr (kDimensions >= 2){
            ret *= cc.j;
        }
        if constexpr (kDimensions >= 3){
            ret *= cc.k;
        }
        if constexpr (kDimensions >= 4){
            ret *= cc.l;
        }
        if constexpr (kDimensions >= 5){
            ret *= cc.m;
        }
        if constexpr (kDimensions >= 6){
            ret *= cc.n;
        }
        return ret;
    }

    template <uint8_t DIMS, class C>
    index_span_t  Pixels<DIMS,C>::dimensions() const 
    {
        static thread_local index_t ret[kDimensions];
        coord_t             cc  = count();
        for(uint8_t n=0;n<kDimensions;++n){
            ret[n] = yq::get(cc, n);
        }
        return ret;
    }

    template <uint8_t DIMS, class C>
    bool    Pixels<DIMS,C>::empty() const 
    {
        return array_t::empty();
    }

    template <uint8_t DIMS, class C>
    Any     Pixels<DIMS,C>::get(const coord_t& cc) const 
    {
        return Any(pixel(cc));
    }
    
    template <uint8_t DIMS, class C>
    Any     Pixels<DIMS,C>::get(index_span_t pix) const 
    {
        return Any(pixel(coord(pix)));
    }

    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::index(index_span_t pix) const 
    {
        return index(coord(pix));
    }

    template <uint8_t DIMS, class C>
    size_t  Pixels<DIMS,C>::index(const coord_t&c) const 
    {
        return array_t::index(c);
    }
    
    template <uint8_t DIMS, class C>
    C       Pixels<DIMS,C>::pixel(const coord_t& coord) const 
    {
        if(any(coord) >= count())
            return C{};
        return array_t::get(coord);
    }
    
    template <uint8_t DIMS, class C>
    const void*   Pixels<DIMS,C>::pointer(data_t) const 
    {
        return array_t::data();
    }

    template <uint8_t DIMS, class C>
    bool    Pixels<DIMS,C>::set(const coord_t& cc, const Any& val) 
    {
        if(any(cc) >= count())
            return false;

        static const auto&  kMeta   = meta<C>();
        static const auto   kId     = kMeta.id();

        const TypeInfo&     type    = val.type();
        const void*         ptr     = val.raw_ptr();
        
        if(type.id() == kId){
            array_t::edit(cc) = *(const C*) ptr;
        } else {
            TypeInfo::FNConvert   cvt = type.converter(kMeta);
            if(!cvt)
                return false;
            cvt(&array_t::edit(cc), ptr);
        }
        return true;
    }

    template <uint8_t DIMS, class C>
    bool    Pixels<DIMS,C>::set(index_span_t pix, const Any& val) 
    {
        return set(coord(pix), val);
    }
    
    template <uint8_t DIMS, class C>
    bool    Pixels<DIMS,C>::set(const coord_t& cc, const C& val) 
    {
        if(any(cc) >= count())
            return false;
        array_t::edit(cc) = val;
        return true;
    }

    template <uint8_t DIMS, class C>
    const TypeInfo&  Pixels<DIMS,C>::type(pixel_t) const 
    {
        return meta<C>();
    }
}
