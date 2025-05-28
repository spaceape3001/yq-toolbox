////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/SetChanges.hpp>

#include <algorithm>
#include <set>
#include <string>
#include <string_view>
#include <vector>
#include <initializer_list>

namespace yq {

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

    /*! \brief Augment set, string view into string set
    
        This augments the set on the left with the contents of the right, allowing for string view set
        to augment a string set.
    */
    template <typename C, typename C2, typename A, typename A2>
    std::set<std::u32string, C, A>&    operator+=(std::set<std::u32string, C, A>& a, const std::set<std::u32string_view, C2, A2>& b)
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

    //! \brief Make a set from an initializer list
    template <typename T>
    std::set<T>                 make_set(const std::initializer_list<T>& data)
    {
        return std::set<T>(data.begin(), data.end());
    }


    //! \brief Make a set from a vector (with a custom comparison)
    template <typename T, typename C, typename A>
    std::set<T,C,A>      make_set(const std::vector<T, A>& data, const C& lesser)
    {
        return std::set<T,C,A>(data.begin(), data.end(), lesser, data.get_allocator());
    }
    
    //! \brief Make a set from an initializer list (with a custom comparison)
    template <typename T, typename C>
    std::set<T,C>      make_set(const std::initializer_list<T>& data, const C& lesser)
    {
        return std::set<T,C>(data.begin(), data.end(), lesser);
    }

    template <typename T, typename C, typename C2, typename A>
    std::set<T,C2,A>    make_set(const std::set<T,C,A>& data, const C2& lesser)
    {
        return std::set<T,C2,A>(data.begin(), data.end(), lesser, data.get_allocator());
    }
}
