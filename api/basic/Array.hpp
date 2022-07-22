////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <concepts>
#include <basic/trait/can_add.hpp>
#include <basic/trait/can_two_multiply.hpp>
#include "preamble.hpp"
#include "Coords.hpp"
#include "IntRange.hpp"
#include <vector>
#include <span>

namespace yq {
    
    namespace impl {
    
        /*! \brief Ascending coordinate
        
            Simple utility to produce an ascending uint8_t coordinate, ie {1,2,3,4,5} 
            which would be perfect for your luggage!
            
            \tparam N  Dimension size
        */
        template <uint8_t N>
        consteval Coord<uint8_t, N> coord_ascending()
        {
            union {
                uint8_t             values[N];
                Coord<uint8_t, N>   ret;
            };
            for(uint8_t n=0;n<N;++n)
                return values[n] = n+1;
            return ret;
        }

        /*! \brief Descending coordinate
        
            Simple utility to produce a descending uint8_t coordinate, ie {5,4,3,2,1}.

            \tparam N  Dimension size
        */
        template <uint8_t N>
        consteval Coord<uint8_t, N> coord_descending()
        {
            union {
                uint8_t             values[N];
                Coord<uint8_t, N>   ret;
            };
            for(uint8_t n=1;n<=N;++n)
                return values[N-n] = n;
            return ret;
        }
        
        /*! \brief Uniform coordinate
        
            Simple utility to produce an uniform coordinate
        
            \tparam N   Dimension size
            \tparam T   Coordinate index type type
            \param[in]  val Value to use
        */
        template <typename T, uint8_t N>
        constexpr Coord<T, N>   uniform_coord(T val)
        {
            union {
                T             values[N];
                Coord<T, N>   ret;
            };
            for(uint8_t n=0;n<N;++n)
                values[n]  = val;
            return ret;
        }
        
        /*! \brief Determines the strides based on order
        
            This utility computes the stride based on the sizes using the order.  It's not super-effecient, 
            but it'll get the job done, and it's not a frequently called routine.
        */
        template <uint8_t N>
        Coord<size_t, N>        array_comingle(const Coord<size_t,N>& sizes, const Coord<uint8_t,N>& order)
        {
            using   uint8_p = std::pair<uint8_t, uint8_t>;
            uint8_p rote[N];
            
            for(uint8_t n=0;n<N;++n)
                rote[n] = { N-n-1, get(order, n) };
            std::stable_sort(std::begin(rote), std::end(rote), 
                [](uint8_p a, uint8_p b) -> bool { return a.second > b.second; }
            );
        
            union {
                size_t          values[N] = {};
                Coord<size_t,N> ret;
            };
            size_t  z       = 1ULL;
            for(uint8_t n=0;n<N;++n){
                uint8_t i = rote[n].first;
                values[i]  = z;
                z *= get(sizes, i);
            }
            
            return ret;
        }
     
        /*! \brief Reference to thread-safe bad data
        
            Rather than throwing exceptions, the array class uses this for a thread-safe buffer that
            can be mutated (and later ignored) for bad coordinate calls.
        */
        template <typename T>
        T&      thread_safe_bad_data()
        {
            static thread_local T    s_ret{};
            return s_ret;
        }
    }
    
    /*! Configration for the array
    
        This is an internal class used to configuring the array.  
        It's used to avoid the overload of template parameters that's otherwise needed.   
        (As the configuration details *may* change for new features, this seemed reasonable
    */
    template <typename I, uint8_t N, bool ORIGIN, bool GHOST>
    struct ArrayConfig {
        static_assert((1 <= N) && (N <= 6), "Invalid dimension count!");

        static constexpr const uint8_t  DIMS    = N;

        using coord_type    = Coord<I,N>;
        using index_type    = I;

        static constexpr const bool origin_flag  = ORIGIN;
        static constexpr const bool ghost_flag   = GHOST;

        static constexpr const bool is_signed   = std::is_signed_v<I>;
        static constexpr const bool is_unsigned = std::is_unsigned_v<I>;
        static_assert((ORIGIN || GHOST) ? is_signed : true, "Origin & ghost features REQUIRE signed index type.");
    };
    
    namespace trait {
        template <typename> struct is_array_coord : std::false_type {};
        template <typename I, uint8_t N, bool ORIGIN, bool GHOST>
        struct is_array_coord<ArrayConfig<I,N,ORIGIN,GHOST>> : std::true_type {};
        template <typename T>
        inline constexpr bool is_array_coord_v = is_array_coord<T>::value;
    }
    
    
    /*! \brief "Array"
    
        \tparam DATA     Data type to be stored
        \tparam COORD    Array coordinate descriptor.
        
        \tparam COORD    Coordinate type, expected to be Coord
        \tparam ORIGIN   True to enable to set origin
        \tparam GHOST    True to inflate sizes by a padding (per side)
        
        \property Permutation
        
            As this object maps a multi-dimensional array into a linear memory 
            object, the permutation governs which coordinate is "major" vs "minor" 
            in the index mapping function.  A lower-number gives that axis major 
            weight.  If two dimensions have the same number, it's has the same 
            effect as linearly increasing numbers.
            
            ie. { 0, 0, 0 } is the default to a 3-D array, which effectively becomes
            { 1, 2, 3 } implying that "i" is major-major, so incrementing "i" means
            a stride of (cnt-i * cnt-j) elements.  
            
            In a 2D array, { 0, 0} or {0,1} is row-major, while { 1, 0 } would be
            a column major ordering.
            
        \property Origin
            
            If the flag is set, then it's possible to start the indexing at something
            other than (0...*).  When set, the origin can be configured to ANY value.
            
        \property Ghost
        
            Ghost is basically padding around the array, useful for boundary conditions 
            (for instance).  Or, maybe wanting [0...N] to all be valid?  
            
        \property Dims
            
            This is the number of elements for the array, one per dimension. 
            The setters will only allow positive (or zero) numbers for sizes.  
            Note zero is ill-advised!
            
        
            
            
    */
    template <typename DATA, typename COORD>
    class Array {
    public:
    
        static_assert(trait::is_array_coord_v<COORD>, "COORD parameter must be ArrayConfig based!");

        using value_type        = DATA;
        using coord_type        = typename COORD::coord_type;
        using index_type        = typename COORD::index_type;
    
        //static constexpr const bool         is_resizeable   = trait::is_stdvector_v<DATA>;
        //static constexpr const bool         is_array        = trait::is_stdarray_v<DATA>;
        //static constexpr const bool         is_span         = trait::is_stdspan_v<DATA>;
        //static constexpr const bool         is_vector       = trait::is_stdvector_v<DATA>;
        static constexpr const bool         is_constant     = std::is_const_v<value_type>;
        static constexpr const bool         is_mutable      = !std::is_const_v<value_type>;
        static constexpr const bool         is_signed       = std::is_signed_v<index_type>;
        static constexpr const bool         is_unsigned     = std::is_unsigned_v<index_type>;
        
        static constexpr const bool         ORIGIN          = COORD::origin_flag;
        static constexpr const bool         GHOST           = COORD::ghost_flag;
        static constexpr const uint8_t      DIMS            = COORD::DIMS;

        static_assert(std::is_integral_v<index_type>, "Coordinate-index must be integer based");

        using size_c            = Coord<size_t, DIMS>;
        using uint8_c           = Coord<uint8_t, DIMS>;
        using range_type        = IntRange<index_type>;
        using ranges_type       = Coord<range_type, DIMS>;

        
        template <typename=void>
        requires (!ORIGIN && !GHOST)
        explicit Array(const coord_type& c, const value_type& v={})
        {
            set_count(c);
            build(v);
        }


        /*! \brief Builds up the vector
        
            *IF* the vector option is chosen, then this will 
            restale & build according to the current specifications.
        */
        bool    build(const value_type& v = {})
        {
            if(needs_compute())
                compute();
            
            if(!m_vector.empty())
                m_vector.clear();
                
            try {
                m_vector.resize(m_calc.total, v);
                m_data  = m_vector;
                return true;
            } 
            catch (std::bad_alloc&)
            {
                return false;
            }
        }
        
        /*! \brief Clears & resets the structure
        */
        void    clear()
        {
            m_vector.clear();
            m_data  = {};
            m_calc  = {};
        }

        template <typename=void>
        requires (DIMS == 2)
        range_type          columns() const
        {
            return range(m_calc.softLo.j, m_calc.softHi.j);
        }


        /*! \brief Restales dimensions & stride
        
            This stales the strides, dimensions, and total size required.
        */
        void                compute()
        {
            m_calc.dim           = (size_c) m_calc.count;
            if constexpr (GHOST)
                m_calc.dim       = m_calc.dim  + (size_c) m_calc.ghostLo + (size_c) m_calc.ghostHi;
            m_calc.stride        = impl::array_comingle<DIMS>(m_calc.dim, m_calc.order);
            m_calc.total         = product(m_calc.dim);
            m_calc.softLo        = m_calc.zero;
            m_calc.softHi        = m_calc.zero + m_calc.count;
            m_calc.hardLo        = m_calc.zero - m_calc.ghostLo;
            m_calc.hardHi        = m_calc.softHi + m_calc.ghostHi;
            m_calc.stale       = false;
        }

        /*! \brief Counts per dimension
        
            These are the user specified counts (below). 
        */
        constexpr const coord_type&  count() const noexcept
        {
            return m_calc.count;
        }
        
        
        /*! \brief Total count per dimension
        
            This is the count plus any ghost, updated with compute().
        */
        constexpr const coord_type&  dim() const noexcept
        {
            return m_calc.dim;
        }
        
        /*! \brief Pointer to the underlying data
        */
        constexpr const value_type* data() const noexcept
        { 
            return m_data.data(); 
        }

        /*! \brief Checks for an empty container
        
            Checks the underlying container, returning TRUE if empty
        */
        constexpr bool          empty() const noexcept
        {
            return m_data.empty();
        }
        
        /*! \brief Ghost on high-side
        
            This is the current ghost configuration for the high-side of indices.
        */
        constexpr const coord_type&  ghost_high() const noexcept
        { 
            return m_calc.ghostHi; 
        }


        /*! \brief Ghost on low-side
        
            This is the current ghost configuration for the low-side of indices.
        */
        constexpr const coord_type&  ghost_low() const noexcept
        { 
            return m_calc.ghostLo; 
        }

        /*! \brief FULL upper-index value
        
            Always available, this routine returns the first invalid coordinate on the high side per dim.
        */
        constexpr const coord_type&  hard_high() const noexcept
        {
            return m_calc.hardHi;
        }

        /*! \brief FULL lower-index value
        
            Always available, this routine returns the lower valid coordinate per dim.
        */
        constexpr const coord_type&  hard_low() const noexcept
        {
            return m_calc.hardLo;
        }
        
        /*! \brief FULL lower-index value
        
            Always available, this routine returns the lower valid coordinate per dim.
        */
        constexpr const coord_type&  hard_lower() const noexcept
        {
            return m_calc.hardLo;
        }

        constexpr ranges_type hard_ranges() const noexcept
        {
            return range(m_calc.hardLo, m_calc.hardHi);
        }

        constexpr ranges_type hard_ranges(const coord_type& bumper) const noexcept
        {
            coord_type   L   = hard_low();
            coord_type   U   = hard_upper() - bumper;
            return range(L, max(L,U));
        }

        constexpr ranges_type hard_ranges(index_type bumper) const noexcept
        {
            return hard_ranges(impl::uniform_coord<index_type, DIMS>(bumper));
        }

        /*! \brief FULL upper-index value
        
            Always available, this routine returns the first invalid coordinate on the high side per dim.
        */
        constexpr const coord_type&  hard_upper() const noexcept
        {
            return m_calc.hardHi;
        }

        constexpr const coord_type&  high() const noexcept
        {
            return m_calc.softHi;
        }
        
        /*! \brief Index mapping function
        
            \note No bounds checking is done, an index is returned.
        */
        constexpr size_t    index(const coord_type& c) const noexcept
        {
            coord_type   l;
            if constexpr (!GHOST && !ORIGIN){
                l   = c;
            } else
                l   = c - m_calc.hardLo;
            return sum( m_calc.stride * (size_c) l );
        }
        
        /*! \brief Tests for a coordinate in the ghost-region
        */
        constexpr bool      is_ghost(const coord_type& c) const noexcept
        {
            if constexpr (GHOST){
                return is_valid(c) && !is_interior(c);
            } else {
                return false;
            }
        }
        
        /*! \brief Tests for a coordinate in the interior (non-ghost)
        */
        constexpr bool      is_interior(const coord_type&c) const noexcept
        {
            if constexpr (ORIGIN || is_signed){
                return all_greater_equal(m_calc.softLo, c) && all_less(c, m_calc.softHi);
            } else {
                return all_less(c, m_calc.softHi);
            }
        }
        
        /*! \brief Tests for a coordinate outside the interior
        
            (Should be opposite of is_valid)
        */
        constexpr bool  is_exterior(const coord_type& c) const noexcept
        {
            return !is_valid(c);
        }
        
        /*! \brief Checks for a good array
        
            A good array is one whose parameters are in good standing AND the container's size 
            has the minimum number of elements.
        */
        constexpr bool  is_good() const noexcept
        {
            return (m_data.size() >= m_calc.total) && !m_calc.stale;
        }

        /*! \brief Tests that coordinate is either interior or ghots
        */
        constexpr bool  is_valid(const coord_type& c) const noexcept
        {
            if constexpr (GHOST || ORIGIN || is_signed){
                return all_greater_equal(m_calc.hardLo, c) && all_less(c, m_calc.hardHi);
            } else {
                return all_less(c, m_calc.hardHi);
            }
        }

        /*! \brief Low-side
        
            This is the low-side coordinate for each dimension.  
            (Only valid for non-ghost).
        */
        constexpr const coord_type & low() const noexcept
        {
            return m_calc.softLo;
        }
        
        template <typename F>
        requires (std::is_floating_point_v<F> && trait::can_add_v<value_type> && trait::can_two_multiply_v<value_type,F>)
        value_type  linear(const coord_type& c, const Coord<F,DIMS>& frac) const
        {
            value_type  ret = {};
            linear_march(index(c), frac, 0, (F) 1., [&](size_t idx, F f){
                ret += f * m_data[idx];
            });
            return ret;
        }
        

        /*! \brief Needs a compute() call
        
            If a "set_()" call routine alters the general shape of the array (ie, dimensions, ghosts),
            then this will return TRUE until compute() is called.  This allows the user to control
            the data & rebuild process.
        */
        bool    needs_compute() const noexcept
        {
            return m_calc.stale;
        }

        /*! \brief Permutation order 
        */
        constexpr uint8_c   permutation() const noexcept
        { 
            return m_calc.order; 
        }
        
        constexpr ranges_type ranges() const noexcept
        {
            return range(low(), high());
        }

        /*! \brief Ranges with a bumper
        
            The bumper can be used to not hit the edge of the domain (ie, 2)
        */
        constexpr ranges_type ranges(const coord_type& bumper) const noexcept
        {
            coord_type   L   = low();
            coord_type   U   = high() - bumper;
            return range(L, max(L,U));
        }

        /*! \brief Ranges with a bumper
        
            The bumper can be used to not hit the edge of the domain (ie, 2)
        */
        constexpr ranges_type ranges(index_type bumper) const noexcept
        {
            return ranges(impl::uniform_coord<index_type, DIMS>(bumper));
        }

        /*! \brief Resizes a vector array
        
            This resizes a vector-based array, equivalent to set_limits() & build().
        */
        template <typename=void>
        requires (ORIGIN && !GHOST)
        void    resize(const coord_type&a, const coord_type& b, const value_type& v = {})
        {
            set_limits(a, b);
            build(v);
        }

        /*! \brief Resizes a vector array
        
            This resizes a vector-based array, equivalent to set_limits() & build().
        */
        template <typename=void>
        requires (!ORIGIN && !GHOST)
        void    resize(const coord_type&sz, const value_type& v = {})
        {
            set_count(sz);
            build(v);
        }

        template <typename=void>
        requires (DIMS == 2)
        range_type          rows() const
        {
            return range(m_calc.softLo.i, m_calc.softHi.i);
        }

        /*! \brief Set the counts for the array
        
            This is LIKELY what you want.  
            Resizes the count, requires a restale & rebuild.
            
            \note It'll force the counts to be at least one
        */
        void    set_count(const coord_type& v) noexcept
        {
            m_calc.count     = max(v, impl::uniform_coord<index_type, DIMS>(1));
            m_calc.stale   = true;
        }
        
        /*! \brief Sets the count (uniform)
        
            \note It'll force the counts to be at least one
        */
        void    set_count(index_type v) noexcept
        {
            m_calc.count     = max(v, index_type{1});
            m_calc.stale   = true;
        }
    
    
        /*! \brief Sets the data object by copying in the vector
        */
        void    set_data_copy(const std::vector<value_type>& d) 
        {
            m_vector    = d;
            m_data      = m_vector;
        }
        
        /*! \brief Sets the data object by moving in the vector
        */
        void    set_data_move(value_type&& d) 
        {
            m_vector    = std::move(d);
            m_data      = m_vector;
        }
        
        /*! \brief Sets the data object by copying the span
        
            \note THIS DOES NOT TAKE OWNERSHIP OF THE DATA, the span must remain VALID
            for the entire lifetime of use!
        */
        void    set_data_span(const std::span<value_type>& d)
        {
            m_vector.clear();
            m_data      = d;
        }

        /*! \brief Sets the ghost 
        
            This sets the ghost on dimension-by-dimension basis, 
            both low & high will be set to the same values.

            \note A rebuild/reallocation will be required after this call.
        */
        template <typename=void>
        requires GHOST
        void    set_ghost(const coord_type&v) noexcept
        {
            m_calc.ghostLo   = m_calc.ghostHi     = std::max(v, {});
            m_calc.stale   = true;
        }
        
        /*! \brief Sets the ghost 
        
            This sets the ghost on a uniform value basis,
            both low & high will be set to this value.
        */
        template <typename=void>
        requires GHOST
        void    set_ghost(index_type v) noexcept
        {
            m_calc.ghostLo   = m_calc.ghostHi     = std::max(v, {});
            m_calc.stale   = true;
        }

        /*! \brief Sets the high-side ghost 
        
            This sets the high-side ghost on dimension-by-dimension basis.

            \note A rebuild/reallocation will be required after this call.
        */
        template <typename=void>
        requires GHOST
        void    set_ghost_high(const coord_type&v) noexcept
        {
            m_calc.ghostHi   = max(v, {});
            m_calc.stale   = true;
        }
        
        /*! \brief Sets the high-side ghost 
        
            This sets the high-side ghost uniformly to the specified value.

            \note A rebuild/reallocation will be required after this call.
        */
        template <typename=void>
        requires GHOST
        void    set_ghost_high(index_type v) noexcept
        {
            m_calc.ghostHi   = max(v, {});
            m_calc.stale   = true;
        }

        /*! \brief Sets the low-side ghost 
        
            This sets the low-side ghost on dimension-by-dimension basis.

            \note A rebuild/reallocation will be required after this call.
        */
        template <typename=void>
        requires GHOST
        void    set_ghost_low(const coord_type&v) noexcept
        {
            m_calc.ghostLo   = max(v, {});
            m_calc.stale   = true;
        }

        /*! \brief Sets the low-side ghost 
        
            This sets the low-side ghost uniformly to the specified value.

            \note A rebuild/reallocation will be required after this call.
        */
        template <typename=void>
        requires GHOST
        void    set_ghost_low(index_type v) noexcept
        {
            m_calc.ghostLo   = max(v, {});
            m_calc.stale   = true;
        }

        /*! \brief Sets counts & zero based on the values
        */
        template <typename=void>
        requires ORIGIN
        void    set_limits(const coord_type& a, const coord_type& b) noexcept
        {
            coord_type L = min(a,b);
            coord_type U = max(a,b);
            m_calc.zero      = L;
            m_calc.count     = U - L;
            m_calc.stale   = true;
        }
        
        /*! \brief Sets the low-side "zero"
        
            This is the zero-index for the array, ie, the low-side.
        */
        template <typename=void>
        requires ORIGIN
        void    set_low(const coord_type& v) noexcept
        {
            m_calc.zero      = v;
        }
    
        /*! \brief Sets the low-side "zero"
        
            This is the zero-index for the array, ie, the low-side.
        */
        template <typename=void>
        requires ORIGIN
        void    set_low(index_type v) noexcept
        {
            m_calc.zero      = v;
            m_calc.stale   = true;
        }
        
        /*! \brief Sets the permutation order

            \note A rebuild/reallocation will be required after this call.
        */
        void    set_permutation(const uint8_c& v) noexcept
        {
            m_calc.order     = v;
            m_calc.stale   = true;
        }

        /*! \brief Sets permutation to ascending
        
            In 2D this will result in row-major (default)

            \note A rebuild/reallocation will be required after this call.
        */
        void    set_permutation_ascending() noexcept
        {
            set_permutation(impl::coord_ascending<DIMS>());
        }
        
        /*! \brief Sets permutation to descending
        
            In 2D this will result in column-major.

            \note A rebuild/reallocation will be required after this call.
        */
        void    set_permutation_descending() noexcept
        {
            set_permutation(impl::coord_descending<DIMS>());
        }
        

        /*! \brief Number of elements in the data
        */
        constexpr size_t  size() const  noexcept{ return m_data.size(); }
        

        /*! \brief Interior upper-index value
        
            Always available, this routine returns the first non-interior 
            coordinate on the high side per dim.
        */
        constexpr const coord_type& soft_high() const noexcept
        {
            return m_calc.softHi;
        }

        /*! \brief Interior lower-index value
        
            Always available, this routine returns the lower interior coordinate per dim.
        */
        constexpr const coord_type&    soft_low() const noexcept
        {
            return m_calc.softLo;
        }

        /*! \brief Interior lower-index value
        
            Always available, this routine returns the lower interior coordinate per dim.
        */
        constexpr const coord_type&    soft_lower() const noexcept
        {
            return m_calc.softLo;
        }

        constexpr ranges_type soft_ranges() const noexcept
        {
            return range(soft_low(), soft_high());
        }
        
        constexpr ranges_type soft_ranges(const coord_type& bumper) const noexcept
        {
            coord_type L = soft_low();
            coord_type U = soft_high() - bumper;
            return range(L, max(L,U));
        }

        constexpr ranges_type  soft_ranges(index_type bumper) const noexcept
        {
            return soft_ranges(impl::uniform_coord<index_type, DIMS>(bumper));
        }

        /*! \brief Interior upper-index value
        
            Always available, this routine returns the first non-interior 
            coordinate on the high side per dim.
        */
        constexpr const coord_type&  soft_upper() const noexcept
        {
            return m_calc.softHi;
        }

        constexpr const size_c&  stride() const noexcept
        {
            return m_calc.stride();
        }

        constexpr size_t  total_bytes() const noexcept
        {
            return m_calc.total * sizeof(value_type);
        }


        /*! \brief Total number of elements (required)
        
            This is the TOTAL number of data elements needed to 
            meet what's been specified.
        */
        constexpr size_t    total_elements() const noexcept
        {
            return m_calc.total;
        }
        
        /*! \brief TRUE if the array's data is undersized.
        */
        constexpr bool    undersized() const noexcept
        {
            return size() < total_elements();
        }
        
        const value_type&    operator()( const coord_type& c) const 
        {
            size_t  idx = index(c);
            if(idx >= m_data.size()) [[unlikely]]
                return impl::thread_safe_bad_data<value_type>();
            return m_data[idx];
        }
        
        template <typename=void>
        requires is_mutable
        value_type&    operator()( const coord_type& c)
        {
            size_t  idx = index(c);
            if(idx >= m_data.size()) [[unlikely]]
                return impl::thread_safe_bad_data<value_type>();
            return m_data[idx];
        }

        template <typename=void>
        requires (DIMS==1)
        const value_type&   operator()( index_type i ) const
        {
            return operator()({ i });
        }

        template <typename=void>
        requires (is_mutable && DIMS==1)
        value_type&   operator()( index_type i ) 
        {
            return operator()({ i });
        }

        template <typename=void>
        requires (DIMS==2)
        const value_type&   operator()( index_type i, index_type j ) const
        {
            return operator()({ i, j });
        }

        template <typename=void>
        requires (is_mutable && DIMS==2)
        value_type&   operator()( index_type i, index_type j ) 
        {
            return operator()({ i, j });
        }

        template <typename=void>
        requires (DIMS==3)
        const value_type&   operator()( index_type i, index_type j, index_type k ) const
        {
            return operator()({ i, j, k });
        }

        template <typename=void>
        requires (is_mutable && DIMS==3)
        value_type&   operator()( index_type i, index_type j, index_type k ) 
        {
            return operator()({ i, j, k });
        }

        template <typename=void>
        requires (DIMS==4)
        const value_type&   operator()( index_type i, index_type j, index_type k, index_type l ) const
        {
            return operator()({ i, j, k, l });
        }

        template <typename=void>
        requires (is_mutable && DIMS==4)
        value_type&   operator()( index_type i, index_type j, index_type k, index_type l ) 
        {
            return operator()({ i, j, k, l });
        }

        template <typename=void>
        requires (DIMS==5)
        const value_type&   operator()( index_type i, index_type j, index_type k, index_type l, index_type m ) const
        {
            return operator()({ i, j, k, l, m });
        }

        template <typename=void>
        requires (is_mutable && DIMS==5)
        value_type&   operator()( index_type i, index_type j, index_type k, index_type l, index_type m ) 
        {
            return operator()({ i, j, k, l, m });
        }

        template <typename=void>
        requires (DIMS==6)
        const value_type&   operator()( index_type i, index_type j, index_type k, index_type l, index_type m, index_type n ) const
        {
            return operator()({ i, j, k, l, m, n });
        }

        template <typename=void>
        requires (is_mutable && DIMS==6)
        value_type&   operator()( index_type i, index_type j, index_type k, index_type l, index_type m, index_type n )
        {
            return operator()({ i, j, k, l, m, n });
        }

        const value_type&   operator[]( size_t idx ) const
        {
            if(idx >= m_data.size()) [[unlikely]]
                return impl::thread_safe_bad_data<value_type>();
            return m_data[idx];
        }
        
        value_type&         operator[]( size_t idx ) 
        {
            if(idx >= m_data.size()) [[unlikely]]
                return impl::thread_safe_bad_data<value_type>();
            return m_data[idx];
        }

        constexpr auto begin() noexcept { return m_data.begin(); }
        constexpr auto end() noexcept { return m_data.end(); }
        constexpr auto begin() const noexcept { return m_data.begin(); }
        constexpr auto end() const noexcept { return m_data.end(); }
        constexpr auto cbegin() const noexcept { return m_data.cbegin(); }
        constexpr auto cend() const noexcept { return m_data.cend(); }

        constexpr auto rbegin() noexcept { return m_data.begin(); }
        constexpr auto rend() noexcept { return m_data.end(); }
        constexpr auto rbegin() const noexcept { return m_data.begin(); }
        constexpr auto rend() const noexcept { return m_data.end(); }
        constexpr auto crbegin() const noexcept { return m_data.cbegin(); }
        constexpr auto crend() const noexcept { return m_data.cend(); }

        Array() = default;
        Array(const std::vector<value_type>& cp) : m_vector(cp)
        {
            m_data  = m_vector;
        }
        
        Array(std::vector<value_type>&& mv) : m_vector(std::move(mv))
        {
            m_data  = m_vector;
        }
        
        Array(const Array&cp)
        {
            m_vector    = cp.m_vector;
            if(m_vector.empty()){
                m_data  = cp.m_data;
            } else {
                m_data  = m_vector;
            }
            m_calc      = cp.m_calc;
        }
        
        Array(Array&&mv)
        {
            m_vector        = std::move(mv.m_vector);
            if(m_vector.empty()){
                m_data  = mv.m_data;
            } else {
                m_data  = m_vector;
            }
            m_calc      = mv.m_calc;
        }
        
        Array& operator=(const Array&cp)
        {
            if(&cp != this){
                m_vector    = cp.m_vector;
                if(m_vector.empty()){
                    m_data  = cp.m_data;
                } else {
                    m_data  = m_vector;
                }
                m_calc  = cp.m_calc;
            }
            return *this;
        }
        
        Array& operator=(Array&&mv)
        {
            if(&mv != this){
                m_vector    = std::move(mv.m_vector);
                if(m_vector.empty()){
                    m_data  = mv.m_data;
                } else {
                    m_data  = m_vector;
                }
                m_calc  = mv.m_calc;
            }
            return *this;
        }
        
        ~Array() = default;
        bool    operator==(const Array&rhs) const
        {
            return (m_calc == rhs.m_calc) && (m_data == rhs.m_data);
        }
    
    private:
        
        std::vector<value_type>   m_vector;
        std::span<value_type>     m_data;
        
        struct Calc {
            size_c              stride;     // multipliers for coord -> index
            size_c              dim;        // total sizes per axis

            union {
                coord_type      zero;
                coord_type      softLo;
            };
            
            coord_type          count;      // our size (as user-defined)
            coord_type          ghostLo;
            coord_type          ghostHi;
            coord_type          softHi;
            coord_type          hardLo;
            coord_type          hardHi;
            size_t              total;      //  total size (required by numbers)
            uint8_c             order;
            bool                stale;      //  "stale" needs recompute
            
            bool operator==(const Calc&) const = default;
        }               m_calc  = {};
        
        template <typename F, typename Pred>
        requires (std::is_floating_point_v<F> && trait::can_add_v<value_type> && trait::can_two_multiply_v<value_type,F>)
        void    linear_march(uint64_t idx, const Coord<F, DIMS>& frac, uint8_t n, F prod, Pred pred)
        {
            if(n<DIMS){
                F   g   = get(frac, n);
                linear_march<F,Pred>(idx, n+1, prod*((F) 1.-g), pred);
                linear_march<F,Pred>(idx+get(m_calc.stride, n), n+1, prod*g, pred);
            } else {
                pred(idx, prod);
            }
        }
    };
}
