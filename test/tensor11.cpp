////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/Tensor11.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor11U(ZERO) == Tensor11U(ZERO)));
        expect( true == (Tensor11D(ZERO) == Tensor11D(ZERO)));
        expect( true == (Tensor11F(ZERO) == Tensor11F(ZERO)));
        expect( true == (all(Tensor11F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor11I(
                1
            ) + Tensor11I(ALL,2) ==  Tensor11I(
                3
            )
        );
        
        //  XX
        expect(
            Tensor11I(
                2
            ) + Tensor11I(ALL,2) ==  Tensor11I(
                4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor11I(
                +1
            ) - Tensor11I(ALL,2) ==  Tensor11I(
                -1
            )
        );

        // XX
        expect(
            Tensor11I(
                -1
            ) - Tensor11I(ALL,2) ==  Tensor11I(
                -3
            )
        );
    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor11I(
                1
            ) * 3 ==  Tensor11I(
                3
            )
        );
        
        // XX
        expect(
            Tensor11I(
                2
            ) * 3 ==  Tensor11I(
                6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor11I(
                3
            ) / 3 ==  Tensor11I(
                1
            )
        );

        // XX
        expect(
            Tensor11I(
                6
            ) / 3 ==  Tensor11I(
                2
            )
        );
    };
};

int main(){
    return ut::cfg<>.run();
};

