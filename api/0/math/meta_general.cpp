////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/math/preamble.hpp>
#include <0/math/Complex.hpp>
#include <0/math/Counter.hpp>
#include <0/math/Fraction.hpp>
#include <0/math/Pose3.hpp>
#include <0/math/Range.hpp>
#include <0/math/strings.hpp>

#include <0/math/color/RGB.hpp>
#include <0/math/color/RGBA.hpp>

#include <0/basic/DelayInit.hpp>
#include <0/meta/Init.hpp>

#include <0/math/SimpleSpace.hpp>

using namespace yq;



YQ_TYPE_IMPLEMENT(yq::ComplexD)
YQ_TYPE_IMPLEMENT(yq::ComplexF)
YQ_TYPE_IMPLEMENT(yq::ComplexI)
YQ_TYPE_IMPLEMENT(yq::ComplexU)

YQ_TYPE_IMPLEMENT(yq::CountI8)
YQ_TYPE_IMPLEMENT(yq::CountI16)
YQ_TYPE_IMPLEMENT(yq::CountI32)
YQ_TYPE_IMPLEMENT(yq::CountI64)

YQ_TYPE_IMPLEMENT(yq::CountU8)
YQ_TYPE_IMPLEMENT(yq::CountU16)
YQ_TYPE_IMPLEMENT(yq::CountU32)
YQ_TYPE_IMPLEMENT(yq::CountU64)


YQ_TYPE_IMPLEMENT(yq::FractionI)
//YQ_TYPE_IMPLEMENT(yq::Frac16)
//YQ_TYPE_IMPLEMENT(yq::Frac32)
//YQ_TYPE_IMPLEMENT(yq::Frac64)

YQ_TYPE_IMPLEMENT(yq::HCountI8)
YQ_TYPE_IMPLEMENT(yq::HCountI16)
YQ_TYPE_IMPLEMENT(yq::HCountI32)
YQ_TYPE_IMPLEMENT(yq::HCountI64)

YQ_TYPE_IMPLEMENT(yq::HCountU8)
YQ_TYPE_IMPLEMENT(yq::HCountU16)
YQ_TYPE_IMPLEMENT(yq::HCountU32)
YQ_TYPE_IMPLEMENT(yq::HCountU64)

YQ_TYPE_IMPLEMENT(yq::LCountI8)
YQ_TYPE_IMPLEMENT(yq::LCountI16)
YQ_TYPE_IMPLEMENT(yq::LCountI32)
YQ_TYPE_IMPLEMENT(yq::LCountI64)


YQ_TYPE_IMPLEMENT(yq::Pose3D)
YQ_TYPE_IMPLEMENT(yq::Pose3F)

YQ_TYPE_IMPLEMENT(yq::RangeD)
YQ_TYPE_IMPLEMENT(yq::RangeF)
YQ_TYPE_IMPLEMENT(yq::RangeI)
YQ_TYPE_IMPLEMENT(yq::RangeU)

YQ_TYPE_IMPLEMENT(yq::RGB3D)
YQ_TYPE_IMPLEMENT(yq::RGB3F)
YQ_TYPE_IMPLEMENT(yq::RGB3U8)
YQ_TYPE_IMPLEMENT(yq::RGB3U16)

YQ_TYPE_IMPLEMENT(yq::RGBA4D)
YQ_TYPE_IMPLEMENT(yq::RGBA4F)
YQ_TYPE_IMPLEMENT(yq::RGBA4U8)
YQ_TYPE_IMPLEMENT(yq::RGBA4U16)

//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//  OTHER HELPERS FOR MATH

namespace yq {
    namespace {
        double  magnitude_complexD(const ComplexD& v)
        {
            return std::abs(v);
        }

        double  magnitude_complexF(const ComplexF& v)
        {
            return std::abs(v);
        }



    }
}    
    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

static void reg_general_math () {

    // General order ... all alphabetical
    //
    //      1. properties
    //      2. methods
    //
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Complex Numbers
    
    {
        auto w = writer<ComplexD>();
        w.description("Complex number in double");
        w.property(szReal, &ComplexD::real).setter((void(ComplexD::*)(double)) &ComplexD::real)
            .description(szReal_Complex)
            .alias({szRe, szR});
        w.property(szImaginary, &ComplexD::imag).setter((void(ComplexD::*)(double)) &ComplexD::imag)
            .description(szImaginary_Complex)
            .alias({szImag, szIm, szI});
        w.property(szMagnitude, magnitude_complexD).description(szMagnitude_Complex).alias(szMag);
    }

    {
        auto w = writer<ComplexF>();
        w.description("Complex number in float");
        w.property(szReal, (float (ComplexF::*)() const) &ComplexF::real).setter((void(ComplexF::*)(float)) &ComplexF::real)
            .description(szReal_Complex)
            .alias({ szRe, szR });
        w.property(szImaginary, (float (ComplexF::*)() const) &ComplexF::imag).setter((void(ComplexF::*)(float)) &ComplexF::imag)
            .description(szImaginary_Complex)
            .alias({szImag, szIm, szI});
        w.property(szMagnitude, magnitude_complexF).description(szMagnitude_Complex).alias(szMag);
    }

    {
        auto w = writer<ComplexI>();
        w.description("Complex number in integer");
        w.property(szReal, (int (ComplexI::*)() const) &ComplexI::real).setter((void(ComplexI::*)(int)) &ComplexI::real)
            .description(szReal_Complex)
            .alias({szRe, szR});
        w.property(szImaginary, (int (ComplexI::*)() const) &ComplexI::imag).setter((void(ComplexI::*)(int)) &ComplexI::imag)
            .description(szImaginary_Complex)
            .alias({szImag, szIm, szI});
    }

    {
        auto w = writer<ComplexU>();
        w.description("Complex number in unsigned integer");
        w.property(szReal, (unsigned (ComplexU::*)() const) &ComplexU::real).setter((void(ComplexU::*)(unsigned)) &ComplexU::real)
            .description(szReal_Complex)
            .alias({szRe, szR});
        w.property(szImaginary, (unsigned (ComplexU::*)() const) &ComplexU::imag).setter((void(ComplexU::*)(unsigned)) &ComplexU::imag)
            .description(szImaginary_Complex)
            .alias({szImag, szIm, szI});
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Counters

    {
        auto w   = writer<CountI8>();
        w.description("Counter with 8-bit integer");
        w.property(szCount, &CountI8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountI16>();
        w.description("Counter with 16-bit integer");
        w.property(szCount, &CountI16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountI32>();
        w.description("Counter with 32-bit integer");
        w.property(szCount, &CountI32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountI64>();
        w.description("Counter with 64-bit integer");
        w.property(szCount, &CountI64::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU8>();
        w.description("Counter with 8-bit unsigned integer");
        w.property(szCount, &CountU8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU16>();
        w.description("Counter with 16-bit unsigned integer");
        w.property(szCount, &CountU16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU32>();
        w.description("Counter with 32-bit unsigned integer");
        w.property(szCount, &CountU32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU64>();
        w.description("Counter with 64-bit unsigned integer");
        w.property(szCount, &CountU64::cnt).description(szCount_Count).alias(szCnt);
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Fractions

    {
        auto w  = writer<FractionI>();
        w.description("Fraction using integers");
        w.property(szNumerator, &FractionI::num).description(szNumerator_Fraction).alias({szNum, szN});
        w.property(szDenominator, &FractionI::den).description(szDenominator_Fraction).alias({szDen, szD});
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

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Hi-counters (start at max-value)
    {
        auto w   = writer<HCountI8>();
        w.description("8-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountI16>();
        w.description("16-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountI32>();
        w.description("32-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountI64>();
        w.description("64-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI64::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU8>();
        w.description("8-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU16>();
        w.description("16-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU32>();
        w.description("32-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU64>();
        w.description("64-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU64::cnt).description(szCount_Count).alias(szCnt);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Lo-counters (start at min-value)
    
    {
        auto w   = writer<LCountI8>();
        w.description("8-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<LCountI16>();
        w.description("16-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<LCountI32>();
        w.description("32-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<LCountI64>();
        w.description("64-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI64::cnt).description(szCount_Count).alias(szCnt);
    }



    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Pose

    {
        auto w = writer<Pose3D>();
        w.description("3D pos in double");
        w.property(szOrientation, &Pose3D::orientation).description(szOrientation_Pose).alias(szOri);
        w.property(szPosition, &Pose3D::position).description(szPosition_Pose).alias(szPos);
    }

    {
        auto w = writer<Pose3F>();
        w.description("3D pos in float");
        w.property(szOrientation, &Pose3F::orientation).description(szOrientation_Pose).alias(szOri);
        w.property(szPosition, &Pose3F::position).description(szPosition_Pose).alias(szPos);
    }
    
        
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Range

    {
        auto w  = writer<RangeD>();
        w.description("Range in double");
        w.property(szLow, &RangeD::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeD::hi).description(szHigh_Range).alias({szHi, szH});
    }
    
    {
        auto w  = writer<RangeF>();
        w.description("Range in float");
        w.property(szLow, &RangeF::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeF::hi).description(szHigh_Range).alias({szHi, szH});
    }

    {
        auto w  = writer<RangeI>();
        w.description("Range in integer");
        w.property(szLow, &RangeI::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeI::hi).description(szHigh_Range).alias({szHi, szH});
    }

    {
        auto w  = writer<RangeU>();
        w.description("Range in unsigned integer");
        w.property(szLow, &RangeU::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeU::hi).description(szHigh_Range).alias({szHi, szH});
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  RGB Colors

    {
        auto w   = writer<RGB3D>();
        w.description("RGB color in double");
        w.property(szRed, &RGB3D::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3D::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3D::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3F>();
        w.description("RGB color in float");
        w.property(szRed, &RGB3F::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3F::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3F::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3U8>();
        w.description("RGB color in uint8");
        w.property(szRed, &RGB3U8::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3U8::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3U8::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3U16>();
        w.description("RGB color in uint16");
        w.property(szRed, &RGB3U16::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3U16::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3U16::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGBA4D>();
        w.description("RGBA color in double");
        w.property(szRed, &RGBA4D::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4D::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4D::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4D::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto w   = writer<RGBA4F>();
        w.description("RGBA color in float");
        w.property(szRed, &RGBA4F::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4F::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4F::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4F::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto w   = writer<RGBA4U8>();
        w.description("RGBA color in uint8");
        w.property(szRed, &RGBA4U8::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4U8::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4U8::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4U8::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto w   = writer<RGBA4U16>();
        w.description("RGBA color in uint16");
        w.property(szRed, &RGBA4U16::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4U16::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4U16::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4U16::alpha).description(szAlpha_Color).alias(szA);
    }

}

YQ_INVOKE(reg_general_math();)

#include "Fraction.hxx"

#include "Pose2.hxx"
#include "Pose3.hxx"
#include "Range.hxx"

#include "color/RGB.hxx"
#include "color/RGBA.hxx"

