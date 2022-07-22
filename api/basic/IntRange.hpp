////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    template <typename T>
    struct IntRange {
        class iterator {
        public:
        
            iterator() : value(0){}
            iterator(T v) : value(v) {}
            
            iterator& operator++() 
            {
                ++value;
                return *this;
            } 
            
            bool operator!=(const iterator& b) const 
            { 
                return value != b.value; 
            }
            
            T operator*()  { return value; }

        private:
            T     value;
        };

        typedef iterator const_iterator;

        iterator begin() const
        {
            return iterator(low);
        }
        
        iterator end() const
        {
            return iterator(high);
        }
        
        constexpr T     count() const { return high - low; }
        
        bool            empty() const { return low == high; }
        bool            not_empty() const { return low != high; }
        
        
        bool operator==(const IntRange&) const = default;

        const T         low, high;
    };


    /*! \brief Creates an iterable object from the specified range */
    template <typename T>
    constexpr IntRange<T> range(T a, T b) noexcept
    {
        return IntRange<T>{a,b};
    }

}
