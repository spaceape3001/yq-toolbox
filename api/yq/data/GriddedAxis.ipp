////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "GriddedAxis.hpp"

namespace yq::data {
    GriddedAxis::GriddedAxis() = default;
    GriddedAxis::GriddedAxis(const GriddedAxis&) = default;
    GriddedAxis::GriddedAxis(GriddedAxis&&) = default;
    GriddedAxis::~GriddedAxis() = default;
    GriddedAxis& GriddedAxis::operator=(const GriddedAxis&) = default;
    GriddedAxis& GriddedAxis::operator=(GriddedAxis&&) = default;
}
