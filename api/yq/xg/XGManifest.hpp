////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/Resource.hpp>
#include <yq/graph/GNodeTemplate.hpp>

namespace yq::xg {

    /*! \brief Meta manifest for graphs
    
        This is a comprehensive listing of things for a XG element...
    */
    class XGManifest : public Resource {
        YQ_RESOURCE_DECLARE(XGManifest, Resource)
    public:
    
        std::vector<GNodeTemplateCPtr>       m_nodes;

        XGManifest();
        ~XGManifest();
        
        size_t        data_size() const override;
        
        static void init_meta();
    };
}

