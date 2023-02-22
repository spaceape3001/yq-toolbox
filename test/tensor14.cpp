////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/Tensor14.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor14U(ZERO) == Tensor14U(ZERO)));
        expect( true == (Tensor14D(ZERO) == Tensor14D(ZERO)));
        expect( true == (Tensor14F(ZERO) == Tensor14F(ZERO)));
        expect( true == (all(Tensor14F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor14I(
                1,1,1,1
            ) + Tensor14I(ALL,2) ==  Tensor14I(
                3,3,3,3
            )
        );
        
        //  XX
        expect(
            Tensor14I(
                2,1,1,1
            ) + Tensor14I(ALL,2) ==  Tensor14I(
                4,3,3,3
            )
        );

        //  XY
        expect(
            Tensor14I(
                1,2,1,1
            ) + Tensor14I(ALL,2) ==  Tensor14I(
                3,4,3,3
            )
        );

        //  XZ
        expect(
            Tensor14I(
                1,1,2,1
            ) + Tensor14I(ALL,2) ==  Tensor14I(
                3,3,4,3
            )
        );

        //  XW
        expect(
            Tensor14I(
                1,1,1,2
            ) + Tensor14I(ALL,2) ==  Tensor14I(
                3,3,3,4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor14I(
                +1,+1,+1,+1
            ) - Tensor14I(ALL,2) ==  Tensor14I(
                -1,-1,-1,-1
            )
        );

        // XX
        expect(
            Tensor14I(
                -1,+1,+1,+1
            ) - Tensor14I(ALL,2) ==  Tensor14I(
                -3,-1,-1,-1
            )
        );

        // XY
        expect(
            Tensor14I(
                +1,-1,+1,+1
            ) - Tensor14I(ALL,2) ==  Tensor14I(
                -1,-3,-1,-1
            )
        );

        // XZ
        expect(
            Tensor14I(
                +1,+1,-1,+1
            ) - Tensor14I(ALL,2) ==  Tensor14I(
                -1,-1,-3,-1
            )
        );

        // XW
        expect(
            Tensor14I(
                +1,+1,+1,-1
            ) - Tensor14I(ALL,2) ==  Tensor14I(
                -1,-1,-1,-3
            )
        );
    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor14I(
                1,1,1,1
            ) * 3 ==  Tensor14I(
                3,3,3,3
            )
        );
        
        // XX
        expect(
            Tensor14I(
                2,1,1,1
            ) * 3 ==  Tensor14I(
                6,3,3,3
            )
        );

        // XY
        expect(
            Tensor14I(
                1,2,1,1
            ) * 3 ==  Tensor14I(
                3,6,3,3
            )
        );

        // XZ
        expect(
            Tensor14I(
                1,1,2,1
            ) * 3 ==  Tensor14I(
                3,3,6,3
            )
        );

        // XW
        expect(
            Tensor14I(
                1,1,1,2
            ) * 3 ==  Tensor14I(
                3,3,3,6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor14I(
                3,3,3,3
            ) / 3 ==  Tensor14I(
                1,1,1,1
            )
        );

        // XX
        expect(
            Tensor14I(
                6,3,3,3
            ) / 3 ==  Tensor14I(
                2,1,1,1
            )
        );

        // XY
        expect(
            Tensor14I(
                3,6,3,3
            ) / 3 ==  Tensor14I(
                1,2,1,1
            )
        );

        // XZ
        expect(
            Tensor14I(
                3,3,6,3
            ) / 3 ==  Tensor14I(
                1,1,2,1
            )
        );

        // XW
        expect(
            Tensor14I(
                3,3,3,6
            ) / 3 ==  Tensor14I(
                1,1,1,2
            )
        );
    };
};

int main(){
    return ut::cfg<>.run();
};

