////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq::raster {
    /*! \brief Marches the line between the two points
    
        Bresenham
    */
    template <typename I, typename Pred>
    auto bresenham_line_algorithm(I x0, I y0, I x1, I y1, Pred pred) -> decltype(pred(x0, y0))
    {
        static_assert(std::is_integer_v<I>, "bresenham_line_algorithm works on integers");
        using return_t  = decltype(pred(x0, y0));
        static constexpr const bool is_void_v     = std::is_same_v<return_t, void>;
        using S = std::make_signed_t<I>;
        
        if(abs(y1-y0) < abs(x1-x0)){
            //  The "low" line
            if(x0 > x1){
                std::swap(x0, x1);
                std::swap(y0, y1);
            }
            
            S dx = (S) x1 - (S) x0;
            S dy = (S) y1 - (S) y0;
            S yi = 1;
            
            if(dy < 0){
                yi  = -1;
                dy  = -dy;
            }
            
            S D = (S) (2*dy) - (S) dx;
            S y = (S) y0;
            for(S x = (S) x0; x <= (S) x1; ++x){
                if constexpr (is_void_v){
                    pred(x, y);
                } 
                if constexpr (!is_void_v){
                    return_t r  = pred(x,y);
                    if(r != return_t{})
                        return r;
                }
                
                if(D > S{}){
                    y = y + yi;
                    D = D + (2*(dy-dx));
                } else {
                    D = D + 2*dy;
                }
            }
        } else {
            //  The "high" line
            if(y0 > y1){
                std::swap(x0, x1);
                std::swap(y0, y1);
            }
            
            S dx = (S) x1 - (S) x0;
            S dy = (S) y1 - (S) y0;
            S xi = 1;
            
            if(dx < 0){
                xi  = -1;
                dx  = -dx;
            }

            S D  = (S) (2 * dx) - (S) dy;
            S x  = x0;
            
            for(S y = (S) y0; y <= (S) y1; ++y){
                if constexpr (is_void_v){
                    pred(x, y);
                } 
                if constexpr (!is_void_v){
                    return_t r  = pred(x,y);
                    if(r != return_t{})
                        return r;
                }
                
                if(D>0){
                    x = x + xi;
                    D = D + (2*(dx-dy));
                } else {
                    D = D + 2*dx;
                }
            }
        }
        
        if constexpr (!is_void_v){
            return return_t{};
        }
    }
}

