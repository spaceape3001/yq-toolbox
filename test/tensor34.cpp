////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq-toolbox/math/tolerance/Absolute.hpp>
#include <yq-toolbox/math/utility.hpp>
#include <yq-toolbox/tensor/Tensor34.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    //Absolute tol{1e-12};

    "zero is zero"_test = []{
        expect( true == (Tensor34U(ZERO) == Tensor34U(ZERO)));
        expect( true == (Tensor34D(ZERO) == Tensor34D(ZERO)));
        expect( true == (Tensor34F(ZERO) == Tensor34F(ZERO)));
        expect( true == (all(Tensor34F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,1,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,3,3,3
            )
        );
        
        //  XX
        expect(
            Tensor34I(
                2,1,1,1,
                1,1,1,1,
                1,1,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                4,3,3,3,
                3,3,3,3,
                3,3,3,3
            )
        );

        //  XY
        expect(
            Tensor34I(
                1,2,1,1,
                1,1,1,1,
                1,1,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,4,3,3,
                3,3,3,3,
                3,3,3,3
            )
        );

        //  XZ
        expect(
            Tensor34I(
                1,1,2,1,
                1,1,1,1,
                1,1,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,4,3,
                3,3,3,3,
                3,3,3,3
            )
        );

        //  XW
        expect(
            Tensor34I(
                1,1,1,2,
                1,1,1,1,
                1,1,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,3,4,
                3,3,3,3,
                3,3,3,3
            )
        );

        //  YX
        expect(
            Tensor34I(
                1,1,1,1,
                2,1,1,1,
                1,1,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,3,3,
                4,3,3,3,
                3,3,3,3
            )
        );

        //  YY
        expect(
            Tensor34I(
                1,1,1,1,
                1,2,1,1,
                1,1,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,3,3,
                3,4,3,3,
                3,3,3,3
            )
        );

        //  YZ
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,2,1,
                1,1,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,3,3,
                3,3,4,3,
                3,3,3,3
            )
        );

        //  YW
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,2,
                1,1,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,3,3,
                3,3,3,4,
                3,3,3,3
            )
        );

        //  ZX
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,1,
                2,1,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,3,3,
                3,3,3,3,
                4,3,3,3
            )
        );

        //  ZY
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,2,1,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,4,3,3
            )
        );

        //  ZZ
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,1,2,1
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,3,4,3
            )
        );

        //  ZW
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,1,1,2
            ) + Tensor34I(ALL,2) ==  Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,3,3,4
            )
        );

    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor34I(
                +1,+1,+1,+1,
                +1,+1,+1,+1,
                +1,+1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-1,-1,
                -1,-1,-1,-1,
                -1,-1,-1,-1
            )
        );

        // XX
        expect(
            Tensor34I(
                -1,+1,+1,+1,
                +1,+1,+1,+1,
                +1,+1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -3,-1,-1,-1,
                -1,-1,-1,-1,
                -1,-1,-1,-1
            )
        );

        // XY
        expect(
            Tensor34I(
                +1,-1,+1,+1,
                +1,+1,+1,+1,
                +1,+1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-3,-1,-1,
                -1,-1,-1,-1,
                -1,-1,-1,-1
            )
        );

        // XZ
        expect(
            Tensor34I(
                +1,+1,-1,+1,
                +1,+1,+1,+1,
                +1,+1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-3,-1,
                -1,-1,-1,-1,
                -1,-1,-1,-1
            )
        );

        // XW
        expect(
            Tensor34I(
                +1,+1,+1,-1,
                +1,+1,+1,+1,
                +1,+1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-1,-3,
                -1,-1,-1,-1,
                -1,-1,-1,-1
            )
        );

        // YX
        expect(
            Tensor34I(
                +1,+1,+1,+1,
                -1,+1,+1,+1,
                +1,+1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-1,-1,
                -3,-1,-1,-1,
                -1,-1,-1,-1
            )
        );

        // YY
        expect(
            Tensor34I(
                +1,+1,+1,+1,
                +1,-1,+1,+1,
                +1,+1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-1,-1,
                -1,-3,-1,-1,
                -1,-1,-1,-1
            )
        );

        // YZ
        expect(
            Tensor34I(
                +1,+1,+1,+1,
                +1,+1,-1,+1,
                +1,+1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-1,-1,
                -1,-1,-3,-1,
                -1,-1,-1,-1
            )
        );

        // YW
        expect(
            Tensor34I(
                +1,+1,+1,+1,
                +1,+1,+1,-1,
                +1,+1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-1,-1,
                -1,-1,-1,-3,
                -1,-1,-1,-1
            )
        );

        // ZX
        expect(
            Tensor34I(
                +1,+1,+1,+1,
                +1,+1,+1,+1,
                -1,+1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-1,-1,
                -1,-1,-1,-1,
                -3,-1,-1,-1
            )
        );

        // ZY
        expect(
            Tensor34I(
                +1,+1,+1,+1,
                +1,+1,+1,+1,
                +1,-1,+1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-1,-1,
                -1,-1,-1,-1,
                -1,-3,-1,-1
            )
        );

        // ZZ
        expect(
            Tensor34I(
                +1,+1,+1,+1,
                +1,+1,+1,+1,
                +1,+1,-1,+1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-1,-1,
                -1,-1,-1,-1,
                -1,-1,-3,-1
            )
        );

        // ZW
        expect(
            Tensor34I(
                +1,+1,+1,+1,
                +1,+1,+1,+1,
                +1,+1,+1,-1
            ) - Tensor34I(ALL,2) ==  Tensor34I(
                -1,-1,-1,-1,
                -1,-1,-1,-1,
                -1,-1,-1,-3
            )
        );
    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,1,1,1
            ) * 3 ==  Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,3,3,3
            )
        );
        
        // XX
        expect(
            Tensor34I(
                2,1,1,1,
                1,1,1,1,
                1,1,1,1
            ) * 3 ==  Tensor34I(
                6,3,3,3,
                3,3,3,3,
                3,3,3,3
            )
        );

        // XY
        expect(
            Tensor34I(
                1,2,1,1,
                1,1,1,1,
                1,1,1,1
            ) * 3 ==  Tensor34I(
                3,6,3,3,
                3,3,3,3,
                3,3,3,3
            )
        );

        // XZ
        expect(
            Tensor34I(
                1,1,2,1,
                1,1,1,1,
                1,1,1,1
            ) * 3 ==  Tensor34I(
                3,3,6,3,
                3,3,3,3,
                3,3,3,3
            )
        );

        // XW
        expect(
            Tensor34I(
                1,1,1,2,
                1,1,1,1,
                1,1,1,1
            ) * 3 ==  Tensor34I(
                3,3,3,6,
                3,3,3,3,
                3,3,3,3
            )
        );

        
        // YX
        expect(
            Tensor34I(
                1,1,1,1,
                2,1,1,1,
                1,1,1,1
            ) * 3 ==  Tensor34I(
                3,3,3,3,
                6,3,3,3,
                3,3,3,3
            )
        );

        // YY
        expect(
            Tensor34I(
                1,1,1,1,
                1,2,1,1,
                1,1,1,1
            ) * 3 ==  Tensor34I(
                3,3,3,3,
                3,6,3,3,
                3,3,3,3
            )
        );

        // YZ
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,2,1,
                1,1,1,1
            ) * 3 ==  Tensor34I(
                3,3,3,3,
                3,3,6,3,
                3,3,3,3
            )
        );

        // YW
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,2,
                1,1,1,1
            ) * 3 ==  Tensor34I(
                3,3,3,3,
                3,3,3,6,
                3,3,3,3
            )
        );

        
        // ZX
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,1,
                2,1,1,1
            ) * 3 ==  Tensor34I(
                3,3,3,3,
                3,3,3,3,
                6,3,3,3
            )
        );

        // ZY
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,2,1,1
            ) * 3 ==  Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,6,3,3
            )
        );

        // ZZ
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,1,2,1
            ) * 3 ==  Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,3,6,3
            )
        );

        // ZW
        expect(
            Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,1,1,2
            ) * 3 ==  Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,3,3,6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,3,3,3
            ) / 3 ==  Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,1,1,1
            )
        );

        // XX
        expect(
            Tensor34I(
                6,3,3,3,
                3,3,3,3,
                3,3,3,3
            ) / 3 ==  Tensor34I(
                2,1,1,1,
                1,1,1,1,
                1,1,1,1
            )
        );

        // XY
        expect(
            Tensor34I(
                3,6,3,3,
                3,3,3,3,
                3,3,3,3
            ) / 3 ==  Tensor34I(
                1,2,1,1,
                1,1,1,1,
                1,1,1,1
            )
        );

        // XZ
        expect(
            Tensor34I(
                3,3,6,3,
                3,3,3,3,
                3,3,3,3
            ) / 3 ==  Tensor34I(
                1,1,2,1,
                1,1,1,1,
                1,1,1,1
            )
        );

        // XW
        expect(
            Tensor34I(
                3,3,3,6,
                3,3,3,3,
                3,3,3,3
            ) / 3 ==  Tensor34I(
                1,1,1,2,
                1,1,1,1,
                1,1,1,1
            )
        );


        // YX
        expect(
            Tensor34I(
                3,3,3,3,
                6,3,3,3,
                3,3,3,3
            ) / 3 ==  Tensor34I(
                1,1,1,1,
                2,1,1,1,
                1,1,1,1
            )
        );

        // YY
        expect(
            Tensor34I(
                3,3,3,3,
                3,6,3,3,
                3,3,3,3
            ) / 3 ==  Tensor34I(
                1,1,1,1,
                1,2,1,1,
                1,1,1,1
            )
        );

        // YZ
        expect(
            Tensor34I(
                3,3,3,3,
                3,3,6,3,
                3,3,3,3
            ) / 3 ==  Tensor34I(
                1,1,1,1,
                1,1,2,1,
                1,1,1,1
            )
        );

        // YW
        expect(
            Tensor34I(
                3,3,3,3,
                3,3,3,6,
                3,3,3,3
            ) / 3 ==  Tensor34I(
                1,1,1,1,
                1,1,1,2,
                1,1,1,1
            )
        );


        // ZX
        expect(
            Tensor34I(
                3,3,3,3,
                3,3,3,3,
                6,3,3,3
            ) / 3 ==  Tensor34I(
                1,1,1,1,
                1,1,1,1,
                2,1,1,1
            )
        );

        // ZY
        expect(
            Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,6,3,3
            ) / 3 ==  Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,2,1,1
            )
        );

        // ZZ
        expect(
            Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,3,6,3
            ) / 3 ==  Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,1,2,1
            )
        );

        // ZW
        expect(
            Tensor34I(
                3,3,3,3,
                3,3,3,3,
                3,3,3,6
            ) / 3 ==  Tensor34I(
                1,1,1,1,
                1,1,1,1,
                1,1,1,2
            )
        );
    };

    return ut::cfg<>.run();
};

