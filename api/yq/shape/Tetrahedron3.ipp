////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Tetrahedron3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Tetrahedron3.hxx"

YQ_TYPE_IMPLEMENT(yq::Tetrahedron3D)
YQ_TYPE_IMPLEMENT(yq::Tetrahedron3F)
YQ_TYPE_IMPLEMENT(yq::Tetrahedron3I)
YQ_TYPE_IMPLEMENT(yq::Tetrahedron3U)

using namespace yq;

static void reg_tetrahedron3()
{

    {
        auto w = writer<Tetrahedron3D>();
        w.description("3D Tetrahedron in double");
        w.property(szA, &Tetrahedron3D::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3D::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3D::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3D::d).description(szD_Tetrahedron);
    }

    {
        auto w = writer<Tetrahedron3F>();
        w.description("3D Tetrahedron in float");
        w.property(szA, &Tetrahedron3F::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3F::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3F::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3F::d).description(szD_Tetrahedron);
    }

    {
        auto w = writer<Tetrahedron3I>();
        w.description("3D Tetrahedron in integer");
        w.property(szA, &Tetrahedron3I::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3I::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3I::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3I::d).description(szD_Tetrahedron);
    }
    
    {
        auto w = writer<Tetrahedron3U>();
        w.description("3D Tetrahedron in unsigned integer");
        w.property(szA, &Tetrahedron3U::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3U::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3U::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3U::d).description(szD_Tetrahedron);
    }
}

YQ_INVOKE(reg_tetrahedron3();)

