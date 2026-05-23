////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/b3fmt/logging.hpp>
#include <yq/meta/Init.hpp>

#include "SymbolLibrary.ipp"
#include "Shape.ipp"
#include "Symbol.ipp"
#include "transform.ipp"

#include <yq/core/Enumeration.hxx>

YQ_ENUM_IMPLEMENT(yq::symbol::TransformMode)
YQ_TYPE_IMPLEMENT(yq::symbol::TransformMode)
