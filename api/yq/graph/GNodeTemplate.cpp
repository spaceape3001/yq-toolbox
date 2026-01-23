////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GNodeTemplate.hpp"
#include <yq/resource/ResourceMetaWriter.hpp>

YQ_RESOURCE_IMPLEMENT(yq::graph::GNodeTemplate)

namespace yq::graph {
    void GNodeTemplate::init_meta()
    {
        auto w = writer<GNodeTemplate>();
        w.description("Graph Meta Node");
        w.property("category", &GNodeTemplate::category);
        w.property("symbol", &GNodeTemplate::symbol);
    }

    GNodeTemplate::GNodeTemplate() = default;
    GNodeTemplate::~GNodeTemplate() = default;

    size_t GNodeTemplate::data_size() const
    {
        return 0;   // TODO
    }
}
