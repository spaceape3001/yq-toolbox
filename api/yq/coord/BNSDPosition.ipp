////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "BNSDPosition.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDPosition)

namespace {
    void    reg_bnsdposition()
    {
        auto w = writer<BNSDPosition>();
        w.description("BNSD Position");
    }
    
    YQ_INVOKE(reg_bnsdposition();)
}
