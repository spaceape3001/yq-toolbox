////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Multivector1.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/vector/Vector1.hpp>

#include "Multivector1.hxx"

YQ_TYPE_IMPLEMENT(yq::Multivector1D)
YQ_TYPE_IMPLEMENT(yq::Multivector1F)

using namespace yq;

static void reg_multivector1()
{
    {
        auto w  = writer<Multivector1D>();
        w.description("1D Multivector in double");
        w.property(szA, &Multivector1D::a).description(szA_Multivector);
        w.property(szX, &Multivector1D::x).description(szX_Multivector);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Vector1D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Multivector1D>();
    }

    {
        auto w  = writer<Multivector1F>();
        w.description("1D Multivector in float");
        w.property(szA, &Multivector1F::a).description(szA_Multivector);
        w.property(szX, &Multivector1F::x).description(szX_Multivector);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Vector1F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Multivector1F>();
    }

}

YQ_INVOKE(reg_multivector1();)
