////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGManifest.hpp"
#include <yq/graph/GNodeTemplate.hpp>

#include <yq/resource/ResourceMetaWriter.hpp>

YQ_RESOURCE_IMPLEMENT(yq::XGManifest)

namespace yq {
    XGManifest::XGManifest() = default;
    XGManifest::~XGManifest() = default;
    
    size_t        XGManifest::data_size() const 
    {
        return 0;
        //  TODO... more here
        //return m_nodes.size() * sizeof(XGNodeMeta);
    }

    void XGManifest::init_meta()
    {
        auto w = writer<XGManifest>();
        w.description("Executive Graph Node Manifest (ie... available nodes)");
    }
}
