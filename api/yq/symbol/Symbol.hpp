////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/Resource.hpp>
#include <yq/shape/AxBox2.hpp>
#include <yq/symbol/transform.hpp>

namespace yq {
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
        
        //! Lock the aspect ratio, so if text requires it, expand both
        bool                            aspectLocked  = true;
        
        Symbol();
        ~Symbol();
        size_t data_size() const override;
        static void init_meta();
    };
}
