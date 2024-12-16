////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Complex.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

using namespace yq;

namespace yq {
    double  magnitude_complexD(const ComplexD& v)
    {
        return std::abs(v);
    }

    double  magnitude_complexF(const ComplexF& v)
    {
        return std::abs(v);
    }
}    

YQ_TYPE_IMPLEMENT(yq::ComplexD)
YQ_TYPE_IMPLEMENT(yq::ComplexF)
YQ_TYPE_IMPLEMENT(yq::ComplexI)
YQ_TYPE_IMPLEMENT(yq::ComplexU)


static void reg_complex_math () {
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
}

YQ_INVOKE(reg_complex_math();)

