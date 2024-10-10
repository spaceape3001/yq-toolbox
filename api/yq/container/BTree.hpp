////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <stdexcept>
#include <iterator>

namespace yq {

    template <typename Key, typename T, typename C, size_t N=4>
    class BTree {
    public:
    
        static constexpr size_t  M   = std::max(1ULL, (N >> 1));
    
        using key_type      = Key;
        using mapped_type   = T;
        using value_type    = std::pair<const Key, T>;
        
        struct value_type {
            key_type    key;
            T           value   = {};
        };
        
        struct data_type : public value_type {
            bool        used    = false;
        };
        
        struct iterator {
        };
        
        using const_iterator            = const iterator;
        using reverse_iterator          = std::reverse_iterator<iterator>;
        using const_reverse_iterator    = std::reverse_iterator<const_iterator>;
    
    
    
        BTree();
        BTree(const BTree&);
        BTree(BTree&&);
        BTree&  operator=(const BTree&);
        BTree&  operator=(BTree&&);
        ~BTree();
        
        T& at(const Key&);
        const T& at(const Key&) const;
        
        T& operator[](const Key&);
        T& operator[](Key&&);
        
        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const noexcept;

        iterator end();
        const_iterator end() const;
        const_iterator cend() const noexcept;

        iterator rbegin();
        const_iterator rbegin() const;
        const_iterator crbegin() const noexcept;

        iterator rend();
        const_iterator rend() const;
        const_iterator crend() const noexcept;
        
        bool    empty() const;
        
        size_t size() const;
        size_t max_size() const;
        
        void    clear();
        
        iterator erase(iterator);
        iterator erase(const_iterator);
        iterator erase(iterator, iterator);
        iterator erase(const_iterator, const_iterator);
        size_t  erase(const Key&);
        
    private:
        std::vector<data_type>      m_data;
    };

}

