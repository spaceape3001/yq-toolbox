////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/Resource.hpp>

namespace yq {

    struct GNodeMeta;

    /*! \brief Meta manifest for graphs (ie...traits)
    
        This is a comprehensive listing of things for a graph
    */
    class GManifest : public Resource {
        YQ_RESOURCE_DECLARE(GManifest, Resource)
    public:
    
        enum Direction {
            Unidir  = 0,
            Bidir
        };
        
        std::vector<GNodeMeta>      m_nodes;
        Direction                   m_direction = Direction::Unidir;

        GManifest();
        ~GManifest();
        
        size_t        data_size() const override;
        
        static void init_meta();
    };
}

