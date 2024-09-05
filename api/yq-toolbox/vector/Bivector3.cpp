////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Bivector3.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Bivector3.hxx"

YQ_TYPE_IMPLEMENT(yq::Bivector3D)
YQ_TYPE_IMPLEMENT(yq::Bivector3F)

using namespace yq;

static void reg_bivector3()
{
}

namespace {
    YQ_INVOKE(reg_bivector3();)
}
