////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/math/Operator.hpp>
#include <yq/typedef/string.hpp>
#include <yq-toolbox/userexpr/impl/SymCategory.hpp>
#include <yq-toolbox/userexpr/impl/SymKind.hpp>

namespace yq::expr {
    struct OpData {
        string_view_t       text;
        Operator            code        = Operator::None;
        OperatorType        type        = OperatorType::None;
        SymCategory		    category	= SymCategory::None;
        SymKind			    kind		= SymKind::None;
        string_view_t       other;
        uint8_t             priority    = 0;
        uint8_t             args        = 0;
        bool				left		= false;
        bool				right		= false;
        bool                self        = false;
    };

}
