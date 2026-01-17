////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Symbol.hpp"
#include <yq/resource/ResourceMetaWriter.hpp>
#include <yq/symbol/Pin.hpp>
#include <yq/symbol/Shape.hpp>

YQ_RESOURCE_IMPLEMENT(yq::Symbol)

namespace yq {
    Symbol::Symbol() = default;
    Symbol::~Symbol() = default;
    size_t Symbol::data_size() const { return 0; }
    void Symbol::init_meta()
    {
        auto w = writer<Symbol>();
        w.description("User Symbol (ie Glyph, etc)");
    }
}
