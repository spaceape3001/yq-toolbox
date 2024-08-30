////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Fraction.hpp"
#include <0/math/strings.hpp>
#include <0/basic/DelayInit.hpp>
#include <0/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::FractionI)
//YQ_TYPE_IMPLEMENT(yq::Frac16)
//YQ_TYPE_IMPLEMENT(yq::Frac32)
//YQ_TYPE_IMPLEMENT(yq::Frac64)

static void reg_fraction_math()
{

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Fractions

    {
        auto w  = writer<FractionI>();
        w.description("Fraction using integers");
        w.property(szNumerator, &FractionI::num).description(szNumerator_Fraction).alias({szNum, szN});
        w.property(szDenominator, &FractionI::den).description(szDenominator_Fraction).alias({szDen, szD});
        w.operate_self();
    }
    
    /*
        auto frac16 = writer<Frac16>();
        frac16.property("n", &Frac16::num);
        frac16.property("d", &Frac16::den);

        auto frac32 = writer<Frac32>();
        frac32.property("n", &Frac32::num);
        frac32.property("d", &Frac32::den);

        auto frac64 = writer<Frac64>();
        frac64.property("n", &Frac64::num);
        frac64.property("d", &Frac64::den);
    */
}

YQ_INVOKE(reg_fraction_math();)

#include "Fraction.hxx"
