////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGNodeType.hpp"
#include <yq/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::XGNodeType)

namespace yq {
    bool    is_flow(XGNodeType v)
    {
        switch(v){
        case XGNodeType::Unspecified:
        case XGNodeType::Command:
        case XGNodeType::Decision:
            return false;
        case XGNodeType::Always:
        case XGNodeType::Continue:
        case XGNodeType::Start:
        case XGNodeType::Resume:
        case XGNodeType::Done:
            return true;
        default:
            return false;
        }
    }

    static void reg_nodetype()
    {
        auto w = writer<XGNodeType>();
        w.description("Executive Graph Node Type");
    }
    
    YQ_INVOKE(reg_nodetype();)
}
