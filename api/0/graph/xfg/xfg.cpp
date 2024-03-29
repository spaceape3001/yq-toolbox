////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#include "PinInfo.ipp"
#include "Node.ipp"

#include "Executive.ipp"

#include "NodeInfo.ipp"
#include "OutputPin.ipp"

#include <0/basic/DelayInit.hpp>
#include <0/meta/Init.hpp>

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


