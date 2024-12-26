////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Statistics.hpp"

#include <initializer_list>
#include <yq/container/initlist_utils.hpp>
#include <yq/trait/has_abs.hpp>
#include <yq/trait/is_floating_point.hpp>
#include <yq/trait/ieee754.hpp>

namespace yq {    
    template <typename T>
    Statistics<T>   statistics(std::span<const T> values)
    {
        static_assert(is_floating_point_v<T>, "Needs to be a floating point type");
        Statistics<T>   ret{.count = values.size()};
        if(values.empty())
            return ret;
        
        T               sum{};
        T               sum1{};
        square_t<T>     sum²{};
        
        ret.min     = values[0];
        ret.max     = values[0];
        
        for(const T& v : values){
            sum     += v;
            sum²    += v * v;
            if(v < ret.min)
                ret.min = v;
            if(v > ret.max)
                ret.max = v;
            
            T   w   = abs(v);
            if(w > ret.normI)
                ret.normI   = w;
            sum1 += w;
        }
        
        ieee754_t<T> divisor = ieee754_t<T>(values.size());
        
        ret.mean        = sum / divisor;
        ret.norm1       = sum1 / divisor;
        ret.norm2       = sqrt(sum²/divisor);
        
        if(values.size() > 1){
            sum²    = {};
            for(const T& v : values){
                T w = v - ret.mean;
                sum² += w * w;
            }
            ret.variance    = sum² / divisor;
            ret.stddev      = sqrt(sum² / ieee754_t<T>(values.size() - 1));
        }
        return ret;
    }

    template <typename T>
    Statistics<T>   statistics(std::initializer_list<T> values)
    {
        return statistics(span(values));
    }
}
