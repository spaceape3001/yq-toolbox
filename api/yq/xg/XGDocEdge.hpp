////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/xg/XGBitPoly.hpp>
#include <yq/xg/XGBitPri.hpp>
#include <yq/xg/XGDocBase.hpp>

namespace yq::xg {
    struct XGDocEdge : public XGDocBase, public XGBitPoly, public XGBitPri {
        //! Source ID (for edges)
        xg_id_t         source      = 0;

        //! Target ID (for edges)
        xg_id_t         target      = 0;
    };
}
