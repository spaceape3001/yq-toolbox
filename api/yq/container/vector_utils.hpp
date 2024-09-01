////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <span>
#include <set>
#include <string>
#include <string_view>
#include <vector>

namespace yq {

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

    /*! \brief Add right string-view vector into left string vector
    */
    template <typename A, typename A2>
    std::vector<std::u32string, A>&    operator+=(std::vector<std::u32string, A>& a, const std::vector<std::u32string_view, A2>& b)
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
}
