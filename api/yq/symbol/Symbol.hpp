////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/Resource.hpp>
#include <yq/shape/AxBox2.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/symbol/style.hpp>
#include <yq/symbol/transform.hpp>
#include <yq/typedef/symbol.hpp>

namespace yq {
    class Stream;
    namespace symbol {
        struct Shape;
        struct Pin;
        struct Pins;
    }

    class Symbol : public Resource {
        YQ_RESOURCE_DECLARE(Symbol, Resource)
    public:
        
        //! All the little shapes that make up this symbol
        std::vector<symbol::Shape>      shape;
        
        //! Regular pins
        std::vector<symbol::Pin>        pin;
        
        //! Dynamic pins (ie... 1...N)
        std::vector<symbol::Pins>       pins;
        
        //! Bounds of the symbol
        AxBox2F                         bounds;
        
        //! Permitted transforms
        symbol::TransformTypes          transforms;
        
        struct {
            symbol::stroke_style_t      stroke;
            symbol::fill_style_t        fill;
            symbol::font_style_t        font;
        }   style;
        
        //! Lock the aspect ratio, so if text requires it, expand both
        bool                            aspectLocked  = true;


        
        Symbol();
        ~Symbol();
        size_t data_size() const override;
        void normalize();
        static void init_meta();
    };
 
    struct SymbolSVGOptions {
        float       scale   = 1024.f;
    };
    
    std::error_code     exportSymbolToSVG(const std::filesystem::path&, const Symbol&, const SymbolSVGOptions& opts={});
}
