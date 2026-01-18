////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Symbol.hpp"
#include "SymbolLibrary.hpp"
#include <yq/resource/ResourceLibraryMetaWriter.hpp>


YQ_RESOURCE_IMPLEMENT(yq::SymbolLibrary)

namespace yq {
    SymbolLibrary::SymbolLibrary()
    {
    }
    
    SymbolLibrary::~SymbolLibrary() 
    {
    }

    size_t SymbolLibrary::data_size() const 
    {
        return 0; // TODO
    }
    
    void SymbolLibrary::init_meta()
    {
        auto w = writer<SymbolLibrary>();
        w.description("Symbol Library");
        w.resource<Symbol>();
    }
}
