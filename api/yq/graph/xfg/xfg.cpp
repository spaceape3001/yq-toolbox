////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#include "PinMeta.ipp"
#include "Node.ipp"

#include "Executive.ipp"

#include "NodeMeta.ipp"
#include "OutputPin.ipp"

#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::xfg::Execute)

using namespace yq;
using namespace yq::xfg;

namespace {
    void    reg_xfg()
    {
        {
            auto w   = writer<Execute>();
            w.description("Execution signal");
        }
    }
    
    YQ_INVOKE(reg_xfg();)
}


