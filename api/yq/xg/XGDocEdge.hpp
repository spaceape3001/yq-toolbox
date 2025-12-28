////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/xg/XGBitPoly.hpp>
#include <yq/xg/XGBitPri.hpp>
#include <yq/xg/XGDocBase.hpp>

namespace yq {
    struct XGDocEdge : public XGDocBase, public XGBitPoly, public XGBitPri {
        //! Target ID (for edges)
        xg_id_t         target      = 0;
    };
}
