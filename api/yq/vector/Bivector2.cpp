////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Bivector2.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/vector/Multivector2.hpp>
#include <yq/vector/Vector2.hpp>

#include "Bivector2.hxx"

YQ_TYPE_IMPLEMENT(yq::Bivector2D)
YQ_TYPE_IMPLEMENT(yq::Bivector2F)

using namespace yq;

static void reg_bivector2()
{
    {
        auto w = writer<Bivector2D>();
        w.description("2D Bivector in double");
        w.property(szXY, &Bivector2D::xy).description(szXY_Bivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Multivector2D>();
        w.operate_with<Vector2D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Bivector2D>();
    }

    {
        auto w = writer<Bivector2F>();
        w.description("2D Bivector in float");
        w.property(szXY, &Bivector2F::xy).description(szXY_Bivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Multivector2F>();
        w.operate_with<Vector2F>();
    }
    
    {
        auto w = writer<float>();
        w.operate_with<Bivector2F>();
    }
}

namespace {
    YQ_INVOKE(reg_bivector2();)
}
