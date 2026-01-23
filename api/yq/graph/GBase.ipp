////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GBase.hpp"

namespace yq::graph {
    GBase::GBase() = default;
    GBase::GBase(const GBase&) = default;
    GBase::GBase(GBase&&) = default;
    GBase::~GBase() = default;
    GBase::GBase(GDocumentPtr gp, uint64_t ip) : m_doc(gp), m_id(ip) {}
}
