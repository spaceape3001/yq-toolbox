////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ID.hpp"

#include <yq/core/DelayInit.hpp>
#include <yq/meta/TypeInfoWriter.hpp>
#include <yq/meta/Init.hpp>

namespace yq::spatial {
    static void reg_id()
    {
        auto w = writer<ID>();
        w.description("ID type");
    }
    
    YQ_INVOKE(reg_id();)
}

YQ_TYPE_IMPLEMENT(yq::spatial::ID)
