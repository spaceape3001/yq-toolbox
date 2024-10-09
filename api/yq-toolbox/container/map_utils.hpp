////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <map>
#include <vector>
#include <yq/trait/has_inequality.hpp>

namespace yq {
    template <typename K, typename V, typename C, typename A>
    V   get_value(const std::map<K,V,C,A>& data, const K& key, const V& defValue=V())
    {
        auto i = data.find(key);
        if(i != data.end()){
            return i->second;
        } else
            return defValue;
    }

    template <typename K, typename V, typename C=std::less<K>, typename A=std::allocator<std::pair<const K, V>> >
    std::map<K,V,C,A> make_map(const std::vector<std::pair<K,V>>&values, C cmp=C(), A alloc=A())
    {
        return std::map<K,V,C,A>(values.begin(), values.end(), cmp, alloc);
        
    }

    template <typename K, typename V, typename C=std::less<K>, typename A=std::allocator<std::pair<const K, V>> >
    std::map<K,V,C,A> make_map(const std::vector<std::pair<const K,V>>&values, C cmp=C(), A alloc=A())
    {
        return std::map<K,V,C,A>(values.begin(), values.end(), cmp, alloc);
        
    }

    /*! Executes on differences between two maps, in order
    
        \tparam K       key type
        \tparam V       value type
        \tparam C       comparator type
        \tparam AL      allocator type for left map
        \tparam AR      allocator type for right map
        \tparam LEFT    functor type for left-only
        \tparam MIDDLE  functor type for middle-changed
        \tparam RIGHT   functor type for right-only
            
        \param[in] A        Left map
        \param[in] B        Right map
        \param[in] left     functor to execute for left-only
        \param[in] middle   functor to execute for middle (changed second)
        \param[in] right    functor to execute for right-only
    */
    template <typename K, typename V, typename C, typename AL, typename AR, typename LEFT, typename MIDDLE, typename RIGHT>
    void    map_difference_exec(const std::map<K,V,C,AL>& A, const std::map<K,V,C,AR>& B, LEFT left, MIDDLE middle, RIGHT right)
    {
        static_assert( has_inequality_v<V>, "Type V must have an inequality operator for it.");
    
        auto    first1  = A.cbegin();
        auto    first2  = B.cbegin();
        auto    last1   = A.cend();
        auto    last2   = B.cend();
        
        while (first1 != last1 && first2 != last2) {
            if( first1->first < first2->first){
                left(*first1);
                *first1++;
            } else if( first1->first == first2->first){
                if(first1->second != first2->second){
                    middle(*first2);
                }
                ++first1, ++first2;
            } else {
                right(*first2);
                ++first2;
            }
        }
        
        for(;first1 != last1; ++first1)
            left(*first1);
            
        for(;first2 != last2; ++first2)
            right(*first2);
    }
    
    /*! Executes on differences between two maps, in order
    
        \tparam K       key type
        \tparam V       value type
        \tparam C       comparator type
        \tparam AL      allocator type for left map
        \tparam AR      allocator type for right map
        \tparam LEFT    functor type for left-only
        \tparam MIDDLE  functor type for middle-changed
        \tparam SAME    functor type for same-value
        \tparam RIGHT   functor type for right-only
            
        \param[in] A        Left map
        \param[in] B        Right map
        \param[in] left     functor to execute for left-only
        \param[in] middle   functor to execute for middle (changed second)
        \param[in] same     functor to execute for middle (unchanged second)
        \param[in] right    functor to execute for right-only
    */
    template <typename K, typename V, typename C, typename AL, typename AR, typename LEFT, typename MIDDLE, typename SAME, typename RIGHT>
    void    map_difference_exec2(const std::map<K,V,C,AL>& A, const std::map<K,V,C,AR>& B, LEFT left, MIDDLE middle, SAME same, RIGHT right)
    {
        static_assert( has_inequality_v<V>, "Type V must have an inequality operator for it.");
    
        auto    first1  = A.cbegin();
        auto    first2  = B.cbegin();
        auto    last1   = A.cend();
        auto    last2   = B.cend();
        
        while (first1 != last1 && first2 != last2) {
            if( first1->first < first2->first){
                left(*first1);
                *first1++;
            } else if( first1->first == first2->first){
                if(first1->second != first2->second){
                    middle(*first2);
                } else
                    same(*first2);
                ++first1, ++first2;
            } else {
                right(*first2);
                ++first2;
            }
        }
        
        for(;first1 != last1; ++first1)
            left(*first1);
            
        for(;first2 != last2; ++first2)
            right(*first2);
    }  
}
