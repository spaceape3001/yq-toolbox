////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceLibrary.hpp>
#include <yq/typedef/symbol_library.hpp>

namespace yq {
    class SymbolLibrary : public ResourceLibrary {  
        YQ_RESOURCE_DECLARE(SymbolLibrary, ResourceLibrary)
    public:
        
        SymbolLibrary();
        ~SymbolLibrary();
        
        size_t data_size() const override;
        
        static void init_meta();
    };
    
    symbol_library_ptr_x    loadSymLibrary(const std::filesystem::path&);
}
