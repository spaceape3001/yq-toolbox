////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Plane3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Plane3.hxx"

YQ_TYPE_IMPLEMENT(yq::Plane3D)
YQ_TYPE_IMPLEMENT(yq::Plane3F)

using namespace yq;

static void reg_plane3()
{
    {   
        auto     w  = writer<Plane3D>();
        w.description("3D plane in double");
        w.property(szNormal,   &Plane3D::normal).description(szNormal_Plane).alias(szN);
        w.property(szDistance, &Plane3D::distance).description(szDistance_Plane).alias(szD);
    }
    {   
        auto     w  = writer<Plane3F>();
        w.description("3D plane in float");
        w.property(szNormal,   &Plane3F::normal).description(szNormal_Plane).alias(szN);
        w.property(szDistance, &Plane3F::distance).description(szDistance_Plane).alias(szD);
    }
}
YQ_INVOKE(reg_plane3();)
