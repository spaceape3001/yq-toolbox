////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceLibrary.hpp>

namespace yq {
    class SymbolLibrary : public ResourceLibrary {  
        YQ_RESOURCE_DECLARE(SymbolLibrary, ResourceLibrary)
    public:
        
        size_t data_size() const override;
        
        static void init_meta();
    };
}
