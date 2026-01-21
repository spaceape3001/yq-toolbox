////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GNodeLibrary.hpp"
#include "GNodeTemplate.hpp"
#include <yq/resource/ResourceLibraryMetaWriter.hpp>

YQ_RESOURCE_IMPLEMENT(yq::GNodeLibrary)

namespace yq {
    GNodeLibrary::GNodeLibrary()
    {
    }
    
    GNodeLibrary::~GNodeLibrary()
    {
    }
        
    size_t        GNodeLibrary::data_size() const 
    {
        return 0;
    }
        
    void GNodeLibrary::init_meta()
    {
        auto w = writer<GNodeLibrary>();
        w.description("Library of Creatable Nodes");
        w.resource<GNodeTemplate>();
    }
}

