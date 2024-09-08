////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Quadrilateral2.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Quadrilateral2.hxx"

YQ_TYPE_IMPLEMENT(yq::Quadrilateral2D)
YQ_TYPE_IMPLEMENT(yq::Quadrilateral2F)
YQ_TYPE_IMPLEMENT(yq::Quadrilateral2I)
YQ_TYPE_IMPLEMENT(yq::Quadrilateral2U)

using namespace yq;

static void reg_quadrilateral2()
{

    {
        auto w = writer<Quadrilateral2D>();
        w.description("2D Quadrilateral in double");
        w.property(szA, &Quadrilateral2D::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2D::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2D::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2D::d).description(szD_Quadrilateral);
    }

    {
        auto w = writer<Quadrilateral2F>();
        w.description("2D Quadrilateral in float");
        w.property(szA, &Quadrilateral2F::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2F::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2F::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2F::d).description(szD_Quadrilateral);
    }

    {
        auto w = writer<Quadrilateral2I>();
        w.description("2D Quadrilateral in integer");
        w.property(szA, &Quadrilateral2I::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2I::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2I::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2I::d).description(szD_Quadrilateral);
    }

    {
        auto w = writer<Quadrilateral2U>();
        w.description("2D Quadrilateral in unsigned integer");
        w.property(szA, &Quadrilateral2U::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2U::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2U::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2U::d).description(szD_Quadrilateral);
    }
}

YQ_INVOKE(reg_quadrilateral2();)
