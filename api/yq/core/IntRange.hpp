////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Integer based range
    
        General Point of this is to have something compatible with a range-based for loop.  
        But also useful to caputuring low & high, might be combined with a span at a future point.
    */
    template <typename T>
    struct IntRange {
    
        //! Iterator to enable it to iterate
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

        //! Constant iterator
        typedef iterator const_iterator;

        //! Starting iterator
        iterator begin() const
        {
            return iterator(low);
        }
        
        //! Ending iterator
        iterator end() const
        {
            return iterator(high);
        }
        
        //! Count between
        constexpr T     count() const { return high - low; }
        
        //! True if empty
        bool            empty() const { return low == high; }
        
        //! TRUE if not empty
        bool            not_empty() const { return low != high; }
        
        //! Equality operator
        constexpr bool operator==(const IntRange&) const noexcept = default;

        T               low, high;      // while const was nice, it implicitly deleted copy & move operations :(
    };


    /*! \brief Creates an iterable object from the specified range */
    template <typename T>
    constexpr IntRange<T> int_range(T a, T b) noexcept
    {
        return IntRange<T>{a,b};
    }

}
