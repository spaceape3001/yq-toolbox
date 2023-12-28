////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/vector/Tensor21.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor21U(ZERO) == Tensor21U(ZERO)));
        expect( true == (Tensor21D(ZERO) == Tensor21D(ZERO)));
        expect( true == (Tensor21F(ZERO) == Tensor21F(ZERO)));
        expect( true == (all(Tensor21F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor21I(
                1,
                1
            ) + Tensor21I(ALL,2) ==  Tensor21I(
                3,
                3
            )
        );
        
        //  XX
        expect(
            Tensor21I(
                2,
                1
            ) + Tensor21I(ALL,2) ==  Tensor21I(
                4,
                3
            )
        );

        //  YX
        expect(
            Tensor21I(
                1,
                2
            ) + Tensor21I(ALL,2) ==  Tensor21I(
                3,
                4
            )
       );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor21I(
                +1,
                +1
            ) - Tensor21I(ALL,2) ==  Tensor21I(
                -1,
                -1
            )
        );

        // XX
        expect(
            Tensor21I(
                -1,
                +1
            ) - Tensor21I(ALL,2) ==  Tensor21I(
                -3,
                -1
            )
        );

        // YX
        expect(
            Tensor21I(
                +1,
                -1
            ) - Tensor21I(ALL,2) ==  Tensor21I(
                -1,
                -3
            )
        );
    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor21I(
                1,
                1
            ) * 3 ==  Tensor21I(
                3,
                3
            )
        );
        
        // XX
        expect(
            Tensor21I(
                2,
                1
            ) * 3 ==  Tensor21I(
                6,
                3
            )
        );

        // YX
        expect(
            Tensor21I(
                1,
                2
            ) * 3 ==  Tensor21I(
                3,
                6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor21I(
                3,
                3
            ) / 3 ==  Tensor21I(
                1,
                1
            )
        );

        // XX
        expect(
            Tensor21I(
                6,
                3
            ) / 3 ==  Tensor21I(
                2,
                1
            )
        );

        // YX
        expect(
            Tensor21I(
                3,
                6
            ) / 3 ==  Tensor21I(
                1,
                2
            )
        );
    };
};

int main(){
    return ut::cfg<>.run();
};

