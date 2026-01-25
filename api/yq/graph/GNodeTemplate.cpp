////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GNodeTemplate.hpp"
#include <yq/resource/ResourceMetaWriter.hpp>

YQ_RESOURCE_IMPLEMENT(yq::GNodeTemplate)

namespace yq {
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

    std::string_view    GNodeTemplate::icon(uint16_t n) const
    {
        auto x = icons.find(n);
        if(x != icons.end())
            return x->second;
        return {};
    }
}
