////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/container/Array.hpp>
#include <yq/raster/forward.hpp>

namespace yq {
    class Any;
    class TypeMeta;

    //! Root for generic pixel data handling (note, *ANYTHING* can be used here for pixels)
    class Pixmap {
    public:
    
        using index_t       = raster::index_t;
        using index_span_t  = raster::index_span_t;
    
        //! Bytes per pixel
        virtual size_t              bytes(pixel_k) const = 0;
        
        //! Total bytes of all the data
        virtual size_t              bytes(total_k) const = 0;
        
        //! Number of dimensions
        virtual uint8_t             count(dimensions_k) const = 0;
        
        //! Count of pixels in the I-axis
        virtual size_t              count(i_k) const = 0;

        //! Count of pixels in the J-axis
        virtual size_t              count(j_k) const = 0;

        //! Count of pixels in the K-axis
        virtual size_t              count(k_k) const = 0;

        //! Count of pixels in the L-axis
        virtual size_t              count(l_k) const = 0;

        //! Count of pixels in the M-axis
        virtual size_t              count(m_k) const = 0;

        //! Count of pixels in the N-axis
        virtual size_t              count(n_k) const = 0;

        //! Count of pixels (total)
        virtual size_t              count(pixels_k) const = 0;
        
        size_t                      count(total_k) const 
        { 
            return count(PIXELS); 
        }
        
        /*! Dimensions
        
            \note This is a span to temporary thread-local data, so copy it off to retain it.
        */
        virtual index_span_t        dimensions() const = 0;

        //! TRUE if we're empty
        virtual bool                empty() const = 0;
        
        /*! Gets pixel data
        
            Gets the pixel value at the specified coordinate.  
            Unspecified coordinates will be assumed to be zero.
            
            \param[in] coordinate   The coordinate, the number of which should match count(DIMENSIONS)
            \return Valid any if the coordinate is correct, otherwise, it'll be an error
        */
        virtual Any                 get(std::span<const index_t> coordinate) const = 0;

        /*! \brief Computes the linear index of the specified coordinate
        */
        virtual size_t              index(index_span_t) const = 0;

        //! TRUE if the given coordinate is inside the box of the pixel data
        virtual bool                inside(index_span_t) const = 0;

        //! Gets a memory compatible object, bound in reference
        virtual Memory              memory(ref_k) const = 0;
        
        //! Gets a memory compatible object, a copy of the data
        virtual Memory              memory(copy_k) const = 0;

        //! Data pointer (warning, can be null if empty)
        virtual const void*         pointer(data_k) const = 0;
        

        //! Sets pixel (returns false if unable)
        virtual bool                set(std::span<const index_t>, const Any&) = 0;
        
        //! Pixel data meta type
        virtual const TypeMeta&     type(pixel_k) const = 0;
        
        virtual ~Pixmap();
        
        
    protected:
        Pixmap();
    };
    
    /*! \brief Specialized pixmap, to number of dimensions
    */
    template <uint8_t DIMS>
    class PixmapN : public Pixmap {
    public:
        
        using coord_t                           = Coord<index_t, DIMS>;

        using Pixmap::get;
        
        //! Getter using specific coord type
        virtual Any     get(const coord_t&) const = 0;
        
        using Pixmap::index;
        
        /*! \brief Computes the linear index of the specified coordinate
        */
        virtual size_t  index(const coord_t&) const = 0;

        using Pixmap::inside;
        
        virtual bool    inside(const coord_t&) const = 0;
        
        using Pixmap::set;
        
        //! Setter using specific coord type
        virtual bool    set(const coord_t&, const Any&) = 0;
    };
    
    #if 0    
        //! Governs lookups
        enum class Edge : uint8_t {
            Zero,
            Clamp,
            Extrapolate,
            Mirror,
            Repeat,
            MirrorRepeat
        };
    #endif
}

