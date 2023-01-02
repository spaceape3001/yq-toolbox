////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/AxBox2.hpp>
#include <math/AxCorners2.hpp>
#include <math/Vector2.hpp>
#include <math/Size2.hpp>

namespace yq {

    /*! \brief Rectangle in two dimensions
    */
    template <typename T>
    struct Rectangle2 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        //! Our position
        Vector2<T>      position;
        
        //! Our size
        Size2<T>        size;
        
        //! Defaulted comparison operator
        constexpr bool    operator==(const Rectangle2&) const noexcept = default;

        //! Our bounding box
        constexpr AxBox2<T>   bounds() const noexcept
        {
            return aabb(southwest(), northeast());
        }

        //! Computes the corners
        constexpr AxCorners2<Vector2<T>>  corners() const noexcept
        {
            return { 
                southwest(),
                northwest(),
                southeast(),
                northeast()
            };
        }

        //! Computes the north east corner, returns it
        constexpr Vector2<T>  northeast() const noexcept
        {
            return { position.x+size.x, position.y+size.y };
        }

        //! Computes the north west corner, returns it
        constexpr Vector2<T>  northwest() const noexcept
        {
            return { position.x, position.y+size.y };
        }

        //! Computes the south east corner, returns it
        constexpr Vector2<T>  southeast() const noexcept
        {
            return { position.x+size.x, position.y };
        }

        //! Computes the south west corner, returns it
        constexpr Vector2<T>  southwest() const noexcept
        {
            return { position.x, position.y };
        }
    };

    YQ_IEEE754_1(Rectangle2)

    YQ_NAN_1(Rectangle2, Rectangle2<T>{nan_v<Vector2<T>>, nan_v<Size2<T>>})
    YQ_ZERO_1(Rectangle2, Rectangle2<T>{zero_v<Vector2<T>>, zero_v<Size2<T>>})


    YQ_IS_NAN_1(Rectangle2, is_nan(v.position) || is_nan(v.size))
    YQ_IS_FINITE_1(Rectangle2, is_finite(v.position) && is_finite(v.size))

    /*! \brief Computes the bounding box of the given rectangle
    */
    template <typename T>
    constexpr AxBox2<T>   aabb(const Rectangle2<T>& rect) noexcept
    {
        return rect.bounds();
    }
    
    /*! \brief Computes the corners of the given rectangle
    */
    template <typename T>
    constexpr AxCorners2<Vector2<T>>  corners(const Rectangle2<T>& rect) noexcept
    {
        return rect.corners();
    }
}

YQ_TYPE_DECLARE(yq::Rectangle2D)
YQ_TYPE_DECLARE(yq::Rectangle2F)
YQ_TYPE_DECLARE(yq::Rectangle2I)
YQ_TYPE_DECLARE(yq::Rectangle2U)
