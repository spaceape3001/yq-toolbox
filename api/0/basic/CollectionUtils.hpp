////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <span>
#include <string>
#include <string_view>
#include <vector>
#include <yq/trait/has_inequality.hpp>

namespace yq {

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  INITIALIZER_LIST RELATED
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    bool    is_in(T val, std::initializer_list<T> vals)
    {
        for(auto& t : vals)
            if(val == t)
                return true;
        return false;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  MAP RELATED
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  SET RELATED
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    /*! \brief Finds items that are exclusive to one set or the other
    
        \tparam InputIt1        Iterator type for container 1
        \tparam InputIt2        Iterator type for container 2, should be comparable to Iterator type 1
        \tparam OutputIt        Output iterator type, should be assignaable from either input iterator type
        
        \param[in] first1       First iterator of container 1
        \param[in] last1        Last iterator of container 1
        \param[in] first2       First iterator of container 2
        \param[in] last2        Last iterator of container 2
        \param[out] d_first     Insert iterator into output
    */
    template<class InputIt1, class InputIt2, class OutputIt>
    void    set_exclusive(InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              OutputIt d_first)
    {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                *d_first++  = *first1++;
            } else  {
                if (!(*first2 < *first1)) { 
                    // *first1 and *first2 are equivalent.
                } else {
                    *d_first++ = *first2; 
                }
                ++first2;
            }
        }
        
            // pure left (after right has ended)
        while(first1 != last1)
            *d_first++  = *first1++;
        
            // pure right (after left has ended)
        while(first2 != last2)
            *d_first++ = *first2++;
    }
    
    /*! \brief Compare two containers
    
        This compares two containers and, for each item, will report whether it's in container 1, container 2, or both,
        and will be put into the relevant output iterator.
    
        \tparam InputIt1        Iterator type for container 1
        \tparam InputIt2        Iterator type for container 2, should be comparable to Iterator type 1
        \tparam OutputIt        Output iterator type, should be assignaable from either input iterator type
        \tparam Compare         Comparator type
        
        \param[in] first1       First iterator of container 1
        \param[in] last1        Last iterator of container 1
        \param[in] first2       First iterator of container 2
        \param[in] last2        Last iterator of container 2
        \param[in] comp         Comparator
        
        \param[out] d_left      Output iterator for things only in container 1
        \param[out] d_middle    Output iterator for things in both containers
        \param[out] d_right     Output iterator for things only in container 2
    */
    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    void    set_changes(InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              OutputIt d_left, OutputIt d_middle, 
                              OutputIt d_right, Compare comp
    ){
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *d_left++  = *first1++;
            } else  {
                if (!comp(*first2,  *first1)) { 
                    *d_middle++ = *first1++;
                } else {
                    *d_right++ = *first2; 
                }
                ++first2;
            }
        }
        
            // pure left (after right has ended)
        while(first1 != last1)
            *d_left++  = *first1++;
        
            // pure right (after left has ended)
        while(first2 != last2)
            *d_right++ = *first2++;
    }
                              
    /*! \brief Compare two containers
    
        This compares two containers, reporting on items that are only in container one or container two.
    
        \tparam InputIt1        Iterator type for container 1
        \tparam InputIt2        Iterator type for container 2, should be comparable to Iterator type 1
        \tparam OutputIt        Output iterator type, should be assignaable from either input iterator type
        \tparam Compare         Comparator type
        
        \param[in] first1       First iterator of container 1
        \param[in] last1        Last iterator of container 1
        \param[in] first2       First iterator of container 2
        \param[in] last2        Last iterator of container 2
        \param[in] comp         Comparator
        
        \param[out] d_left      Output iterator for things only in container 1
        \param[out] d_right     Output iterator for things only in container 2
    */
    template<class InputIt1, class InputIt2, class OutputIt, class Compare>
    void    set_left_right(InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              OutputIt d_left, 
                              OutputIt d_right, Compare comp
    ){
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *d_left++  = *first1++;
            } else  {
                if (!comp(*first2, *first1)) { 
                    ++first1;
                } else {
                    *d_right++ = *first2; 
                }
                ++first2;
            }
        }
        
            // pure left (after right has ended)
        while(first1 != last1)
            *d_left++  = *first1++;
        
            // pure right (after left has ended)
        while(first2 != last2)
            *d_right++ = *first2++;
    }

    /*! \brief Merges two sets
    */
    template <typename T, typename C, typename A>
    std::set<T, C, A>    operator+(const std::set<T, C, A>& a, const std::set<T, C, A>& b)
    {
        std::set<T, C, A>   ret = a;
        ret.insert(b.begin(), b.end());
        return ret;
    }
    
    /*! \brief Augment set
    
        This augments the set on the left with the new item
    */
    template <typename T, typename C, typename A>
    std::set<T, C, A>&    operator+=(std::set<T, C, A>& a, const T& b)
    {
        a.insert(b);
        return a;
    }

    /*! \brief Augment set
    
        This augments the set on the left with the new item
    */
    template <typename T, typename C, typename A>
    std::set<T, C, A>&    operator+=(std::set<T, C, A>& a, T&& b)
    {
        a.insert(std::move(b));
        return a;
    }

    /*! \brief Augment set
    
        This augments the set on the left with the contents of the right
    */
    template <typename T, typename C, typename C2, typename A, typename A2>
    std::set<T, C, A>&    operator+=(std::set<T, C, A>& a, const std::set<T, C2, A2>& b)
    {
        a.insert(b.begin(), b.end());
        return a;
    }

    /*! \brief Augment set, string view into string set
    
        This augments the set on the left with the contents of the right, allowing for string view set
        to augment a string set.
    */
    template <typename C, typename C2, typename A, typename A2>
    std::set<std::string, C, A>&    operator+=(std::set<std::string, C, A>& a, const std::set<std::string_view, C2, A2>& b)
    {
        a.insert(b.begin(), b.end());
        return a;
    }


    /*! \brief Augment set
    
        This augments the set on the left with the contents of the vector
    */
    template <typename T, typename C, typename A, typename A2>
    std::set<T, C, A>&    operator+=(std::set<T, C, A>& a, const std::vector<T, A2>& b)
    {
        a.insert(b.begin(), b.end());
        return a;
    }
    
    /*! \brief "Difference" of the set
    
        In this case, the difference is items in A that aren't in B.
    */
    template <typename T, typename C, typename A>
    std::set<T, C, A>    operator-(const std::set<T, C, A>& a, const std::set<T, C, A>& b)
    {
        std::set<T, C, A>   ret;
        std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(ret, ret.begin()));
        return ret;
    }

    /*! \brief Merges two sets
    
        This returns the union of these two sets.
    */
    template <typename T, typename C, typename A>
    std::set<T, C, A>    operator|(const std::set<T, C, A>& a, const std::set<T, C, A>& b)
    {
        std::set<T, C, A>   ret;
        std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::inserter(ret, ret.begin()));
        return ret;
    }

    /*! \brief Intersection two sets
    
        This returns the intersection, ie, items in BOTH sets.
    */
    template <typename T, typename C, typename A>
    std::set<T, C, A>    operator&(const std::set<T, C, A>& a, const std::set<T, C, A>& b)
    {
        std::set<T, C, A>   ret;
        std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(ret, ret.begin()));
        return ret;
    }

    /*! \brief Exclusive XOR of the sets
    
        This returns the set of items that's in one or the other, but not BOTH sets
    */
    template <typename T, typename C, typename A>
    std::set<T, C, A>    operator^(const std::set<T, C, A>& a, const std::set<T, C, A>& b)
    {
        std::set<T, C, A>   ret;
        set_exclusive(a.begin(), a.end(), b.begin(), b.end(), std::inserter(ret, ret.begin()));
        return ret;
    }

    /*! \brief Insert into set
    
        Simple streaming operator to insert (copy) an item into a set.
    */
    template <typename T, typename C, typename A>
    std::set<T,C,A>&    operator<<(std::set<T, C, A>& a, const T& b)
    {
        a.insert(b);
        return a;
    }

    /*! \brief Insert into set
    
        Simple streaming operator to insert (move) an item into a set.
    */
    template <typename T, typename C, typename A>
    std::set<T,C,A>&    operator<<(std::set<T, C, A>& a, T&& b)
    {
        a.insert(std::move(b));
        return a;
    }

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

    /*! \brief Compute changes between sets
    
        Use this to determine what items were added, removed, and stayed the same between two
        sets.
    */
    template <typename T, typename C, typename A>
    SetChanges<T,C,A>    changes(const std::set<T,C,A>& from, const std::set<T,C,A>& to, C c=C())
    {
        SetChanges<T,C,A>    ret;
        set_changes(from.begin(), from.end(), to.begin(), to.end(), 
            std::inserter(ret.removed, ret.removed.end()), 
            std::inserter(ret.same, ret.same.end()), 
            std::inserter(ret.added, ret.added.end()), c
        );
        return ret;
    }

    /*! \brief Compute changes between sets
        
        Use this to determine what items were added vs removed between two sets.
    */
    template <typename T, typename C, typename A>
    SetChanges<T,C,A>    add_remove(const std::set<T,C,A>& from, const std::set<T,C,A>& to, C c=C())
    {
        SetChanges<T,C,A>    ret;
        set_left_right(from.begin(), from.end(), to.begin(), to.end(), 
            std::inserter(ret.removed, ret.removed.end()), 
            std::inserter(ret.added, ret.added.end()), c);
        return ret;
    }

    //! \brief Make a set from a vector
    template <typename T, typename A>
    std::set<T, std::less<T>, A>         make_set(const std::vector<T,A>& data)
    {
        return std::set<T, std::less<T>, A>(data.begin(), data.end(), std::less<T>(), data.get_allocator());
    }
    
    //! \brief Make a set from a vector (with a custom comparison)
    template <typename T, typename C, typename A>
    std::set<T,C,A>      make_set(const std::vector<T, A>& data, const C& lesser)
    {
        return std::set<T,C>(data.begin(), data.end(), lesser, data.get_allocator());
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  VECTOR RELATED
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    /*! \brief Add right vector into left
    */
    template <typename T, typename A>
    std::vector<T, A>&    operator+=(std::vector<T, A>& a, const std::vector<T, A>& b)
    {
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }
    
    /*! \brief Add right string-view vector into left string vector
    */
    template <typename A, typename A2>
    std::vector<std::string, A>&    operator+=(std::vector<std::string, A>& a, const std::vector<std::string_view, A2>& b)
    {
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }

    /*! \brief Append (copy) into vector
    */
    template <typename T, typename A>
    std::vector<T,A>&    operator<<(std::vector<T, A>& a, const T& b)
    {
        a.push_back(b);
        return a;
    }

    /*! \brief Append (move) into vector
    */
    template <typename T, typename A>
    std::vector<T,A>&    operator<<(std::vector<T, A>& a, T&& b)
    {
        a.push_back(std::move(b));
        return a;
    }
    
    template <typename T, typename C, typename A>
    std::vector<T,A>    make_vector(const std::set<T,C,A>& data)
    {
        return std::vector<T,A>(data.begin(), data.end());
    }

    template <typename T>
    bool    is_same(const std::span<const T>& a, const std::span<const T>& b)
    {
        if(a.size() != b.size())
            return false;
        for(size_t  n=0;n<a.size();++n){
            if(a[n] != b[n])
                return false;
        }
        return true;
    }
    
    template <typename T, typename A>
    bool    is_same(const std::vector<T, A>& a, const std::initializer_list<T>& b)
    {
        return is_same(span(a), span(b));
    }
    

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  REVERSING!
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    //! \brief Class to switch the begin/end of a container
    template <typename T>
    struct ReverseIter {
        ReverseIter(const T& _c) : c(_c) {}
        typename T::const_reverse_iterator begin() const { return c.rbegin(); }
        typename T::const_reverse_iterator end() const { return c.rend(); }
        const T& arg() const { return c; }
    private:
        const T& c;
    };

    /*! \brief Used to reverse-iterate a class
    
        This is useful in ranged for-loops.
    */
    template <typename T>
    ReverseIter<T> reverse(const T& c) 
    { 
        return ReverseIter<T>(c); 
    }

    /*! \brief Compares class with revere-iterator */
    template <typename T>
    bool  operator==(const T&a, const ReverseIter<T>& b)
    {
        if(a.size() != b.arg().size())
            return false;
        auto itr = a.begin();
        auto jtr = b.begin();
        for(; itr != a.end(); ++itr, ++jtr){
            if(*itr != *jtr)
                return false;
        }
        return true;
    }
}
