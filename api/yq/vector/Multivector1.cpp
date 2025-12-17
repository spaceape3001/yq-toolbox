////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Multivector1.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>
#include <yq/vector/Vector1.hpp>

#include "Multivector1.hxx"

YQ_TYPE_IMPLEMENT(yq::Multivector1D)
YQ_TYPE_IMPLEMENT(yq::Multivector1F)

using namespace yq;

static void reg_multivector1()
{
    {
        auto w  = writer<Multivector1D>();
        w.description("1D Multivector in double");
        w.property(szA, &Multivector1D::a).description(szA_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szX, &Multivector1D::x).description(szX_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector1D>();
        w.format<math_io::format<Multivector1D>>();
        w.parse<math_io::parse<Multivector1D>>();
        w.print<math_io::print<Multivector1D>>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Multivector1D>();
    }

    {
        auto w  = writer<Multivector1F>();
        w.description("1D Multivector in float");
        w.property(szA, &Multivector1F::a).description(szA_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.property(szX, &Multivector1F::x).description(szX_Multivector).tag(kTag_Save).tag(kTag_Print);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector1F>();
        w.format<math_io::format<Multivector1F>>();
        w.parse<math_io::parse<Multivector1F>>();
        w.print<math_io::print<Multivector1F>>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Multivector1F>();
    }

}

YQ_INVOKE(reg_multivector1();)
