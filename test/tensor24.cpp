////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq-toolbox/math/tolerance/Absolute.hpp>
#include <yq-toolbox/math/utility.hpp>
#include <yq-toolbox/tensor/Tensor24.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    //Absolute tol{1e-12};

    "zero is zero"_test = []{
        expect( true == (Tensor24U(ZERO) == Tensor24U(ZERO)));
        expect( true == (Tensor24D(ZERO) == Tensor24D(ZERO)));
        expect( true == (Tensor24F(ZERO) == Tensor24F(ZERO)));
        expect( true == (all(Tensor24F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor24I(
                1,1,1,1,
                1,1,1,1
            ) + Tensor24I(ALL,2) ==  Tensor24I(
                3,3,3,3,
                3,3,3,3
            )
        );
        
        //  XX
        expect(
            Tensor24I(
                2,1,1,1,
                1,1,1,1
            ) + Tensor24I(ALL,2) ==  Tensor24I(
                4,3,3,3,
                3,3,3,3
            )
        );

        //  XY
        expect(
            Tensor24I(
                1,2,1,1,
                1,1,1,1
            ) + Tensor24I(ALL,2) ==  Tensor24I(
                3,4,3,3,
                3,3,3,3
            )
        );

        //  XZ
        expect(
            Tensor24I(
                1,1,2,1,
                1,1,1,1
            ) + Tensor24I(ALL,2) ==  Tensor24I(
                3,3,4,3,
                3,3,3,3
            )
        );

        //  XW
        expect(
            Tensor24I(
                1,1,1,2,
                1,1,1,1
            ) + Tensor24I(ALL,2) ==  Tensor24I(
                3,3,3,4,
                3,3,3,3
            )
        );

        //  YX
        expect(
            Tensor24I(
                1,1,1,1,
                2,1,1,1
            ) + Tensor24I(ALL,2) ==  Tensor24I(
                3,3,3,3,
                4,3,3,3
            )
        );

        //  YY
        expect(
            Tensor24I(
                1,1,1,1,
                1,2,1,1
            ) + Tensor24I(ALL,2) ==  Tensor24I(
                3,3,3,3,
                3,4,3,3
            )
        );

        //  YZ
        expect(
            Tensor24I(
                1,1,1,1,
                1,1,2,1
            ) + Tensor24I(ALL,2) ==  Tensor24I(
                3,3,3,3,
                3,3,4,3
            )
        );

        //  YW
        expect(
            Tensor24I(
                1,1,1,1,
                1,1,1,2
            ) + Tensor24I(ALL,2) ==  Tensor24I(
                3,3,3,3,
                3,3,3,4
            )
        );

    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor24I(
                +1,+1,+1,+1,
                +1,+1,+1,+1
            ) - Tensor24I(ALL,2) ==  Tensor24I(
                -1,-1,-1,-1,
                -1,-1,-1,-1
            )
        );

        // XX
        expect(
            Tensor24I(
                -1,+1,+1,+1,
                +1,+1,+1,+1
            ) - Tensor24I(ALL,2) ==  Tensor24I(
                -3,-1,-1,-1,
                -1,-1,-1,-1
            )
        );

        // XY
        expect(
            Tensor24I(
                +1,-1,+1,+1,
                +1,+1,+1,+1
            ) - Tensor24I(ALL,2) ==  Tensor24I(
                -1,-3,-1,-1,
                -1,-1,-1,-1
            )
        );

        // XZ
        expect(
            Tensor24I(
                +1,+1,-1,+1,
                +1,+1,+1,+1
            ) - Tensor24I(ALL,2) ==  Tensor24I(
                -1,-1,-3,-1,
                -1,-1,-1,-1
            )
        );

        // XW
        expect(
            Tensor24I(
                +1,+1,+1,-1,
                +1,+1,+1,+1
            ) - Tensor24I(ALL,2) ==  Tensor24I(
                -1,-1,-1,-3,
                -1,-1,-1,-1
            )
        );

        // YX
        expect(
            Tensor24I(
                +1,+1,+1,+1,
                -1,+1,+1,+1
            ) - Tensor24I(ALL,2) ==  Tensor24I(
                -1,-1,-1,-1,
                -3,-1,-1,-1
            )
        );

        // YY
        expect(
            Tensor24I(
                +1,+1,+1,+1,
                +1,-1,+1,+1
            ) - Tensor24I(ALL,2) ==  Tensor24I(
                -1,-1,-1,-1,
                -1,-3,-1,-1
            )
        );

        // YZ
        expect(
            Tensor24I(
                +1,+1,+1,+1,
                +1,+1,-1,+1
            ) - Tensor24I(ALL,2) ==  Tensor24I(
                -1,-1,-1,-1,
                -1,-1,-3,-1
            )
        );

        // YW
        expect(
            Tensor24I(
                +1,+1,+1,+1,
                +1,+1,+1,-1
            ) - Tensor24I(ALL,2) ==  Tensor24I(
                -1,-1,-1,-1,
                -1,-1,-1,-3
            )
        );
    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor24I(
                1,1,1,1,
                1,1,1,1
            ) * 3 ==  Tensor24I(
                3,3,3,3,
                3,3,3,3
            )
        );
        
        // XX
        expect(
            Tensor24I(
                2,1,1,1,
                1,1,1,1
            ) * 3 ==  Tensor24I(
                6,3,3,3,
                3,3,3,3
            )
        );

        // XY
        expect(
            Tensor24I(
                1,2,1,1,
                1,1,1,1
            ) * 3 ==  Tensor24I(
                3,6,3,3,
                3,3,3,3
            )
        );

        // XZ
        expect(
            Tensor24I(
                1,1,2,1,
                1,1,1,1
            ) * 3 ==  Tensor24I(
                3,3,6,3,
                3,3,3,3
            )
        );

        // XW
        expect(
            Tensor24I(
                1,1,1,2,
                1,1,1,1
            ) * 3 ==  Tensor24I(
                3,3,3,6,
                3,3,3,3
            )
        );

        
        // YX
        expect(
            Tensor24I(
                1,1,1,1,
                2,1,1,1
            ) * 3 ==  Tensor24I(
                3,3,3,3,
                6,3,3,3
            )
        );

        // YY
        expect(
            Tensor24I(
                1,1,1,1,
                1,2,1,1
            ) * 3 ==  Tensor24I(
                3,3,3,3,
                3,6,3,3
            )
        );

        // YZ
        expect(
            Tensor24I(
                1,1,1,1,
                1,1,2,1
            ) * 3 ==  Tensor24I(
                3,3,3,3,
                3,3,6,3
            )
        );

        // YW
        expect(
            Tensor24I(
                1,1,1,1,
                1,1,1,2
            ) * 3 ==  Tensor24I(
                3,3,3,3,
                3,3,3,6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor24I(
                3,3,3,3,
                3,3,3,3
            ) / 3 ==  Tensor24I(
                1,1,1,1,
                1,1,1,1
            )
        );

        // XX
        expect(
            Tensor24I(
                6,3,3,3,
                3,3,3,3
            ) / 3 ==  Tensor24I(
                2,1,1,1,
                1,1,1,1
            )
        );

        // XY
        expect(
            Tensor24I(
                3,6,3,3,
                3,3,3,3
            ) / 3 ==  Tensor24I(
                1,2,1,1,
                1,1,1,1
            )
        );

        // XZ
        expect(
            Tensor24I(
                3,3,6,3,
                3,3,3,3
            ) / 3 ==  Tensor24I(
                1,1,2,1,
                1,1,1,1
            )
        );

        // XW
        expect(
            Tensor24I(
                3,3,3,6,
                3,3,3,3
            ) / 3 ==  Tensor24I(
                1,1,1,2,
                1,1,1,1
            )
        );


        // YX
        expect(
            Tensor24I(
                3,3,3,3,
                6,3,3,3
            ) / 3 ==  Tensor24I(
                1,1,1,1,
                2,1,1,1
            )
        );

        // YY
        expect(
            Tensor24I(
                3,3,3,3,
                3,6,3,3
            ) / 3 ==  Tensor24I(
                1,1,1,1,
                1,2,1,1
            )
        );

        // YZ
        expect(
            Tensor24I(
                3,3,3,3,
                3,3,6,3
            ) / 3 ==  Tensor24I(
                1,1,1,1,
                1,1,2,1
            )
        );

        // YW
        expect(
            Tensor24I(
                3,3,3,3,
                3,3,3,6
            ) / 3 ==  Tensor24I(
                1,1,1,1,
                1,1,1,2
            )
        );

    };

    return ut::cfg<>.run();
};

