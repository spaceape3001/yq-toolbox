////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/math/utility.hpp>
#include <yq/vector/Tensor22.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    //Absolute tol{1e-12};

    "zero is zero"_test = []{
        expect( true == (Tensor22U(ZERO) == Tensor22U(ZERO)));
        expect( true == (Tensor22D(ZERO) == Tensor22D(ZERO)));
        expect( true == (Tensor22F(ZERO) == Tensor22F(ZERO)));
        expect( true == (all(Tensor22F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor22I(
                1,1,
                1,1
            ) + Tensor22I(ALL,2) ==  Tensor22I(
                3,3,
                3,3
            )
        );
        
        //  XX
        expect(
            Tensor22I(
                2,1,
                1,1
            ) + Tensor22I(ALL,2) ==  Tensor22I(
                4,3,
                3,3
            )
        );

        //  XY
        expect(
            Tensor22I(
                1,2,
                1,1
            ) + Tensor22I(ALL,2) ==  Tensor22I(
                3,4,
                3,3
            )
        );

        //  YX
        expect(
            Tensor22I(
                1,1,
                2,1
            ) + Tensor22I(ALL,2) ==  Tensor22I(
                3,3,
                4,3
            )
        );

        //  YY
        expect(
            Tensor22I(
                1,1,
                1,2
            ) + Tensor22I(ALL,2) ==  Tensor22I(
                3,3,
                3,4
            )
        );

    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor22I(
                +1,+1,
                +1,+1
            ) - Tensor22I(ALL,2) ==  Tensor22I(
                -1,-1,
                -1,-1
            )
        );

        // XX
        expect(
            Tensor22I(
                -1,+1,
                +1,+1
            ) - Tensor22I(ALL,2) ==  Tensor22I(
                -3,-1,
                -1,-1
            )
        );

        // XY
        expect(
            Tensor22I(
                +1,-1,
                +1,+1
            ) - Tensor22I(ALL,2) ==  Tensor22I(
                -1,-3,
                -1,-1
            )
        );


        // YX
        expect(
            Tensor22I(
                +1,+1,
                -1,+1
            ) - Tensor22I(ALL,2) ==  Tensor22I(
                -1,-1,
                -3,-1
            )
        );

        // YY
        expect(
            Tensor22I(
                +1,+1,
                +1,-1
            ) - Tensor22I(ALL,2) ==  Tensor22I(
                -1,-1,
                -1,-3
            )
        );
    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor22I(
                1,1,
                1,1
            ) * 3 ==  Tensor22I(
                3,3,
                3,3
            )
        );
        
        // XX
        expect(
            Tensor22I(
                2,1,
                1,1
            ) * 3 ==  Tensor22I(
                6,3,
                3,3
            )
        );

        // XY
        expect(
            Tensor22I(
                1,2,
                1,1
            ) * 3 ==  Tensor22I(
                3,6,
                3,3
            )
        );

        
        // YX
        expect(
            Tensor22I(
                1,1,
                2,1
            ) * 3 ==  Tensor22I(
                3,3,
                6,3
            )
        );

        // YY
        expect(
            Tensor22I(
                1,1,
                1,2
            ) * 3 ==  Tensor22I(
                3,3,
                3,6
            )
        );

    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor22I(
                3,3,
                3,3
            ) / 3 ==  Tensor22I(
                1,1,
                1,1
            )
        );

        // XX
        expect(
            Tensor22I(
                6,3,
                3,3
            ) / 3 ==  Tensor22I(
                2,1,
                1,1
            )
        );

        // XY
        expect(
            Tensor22I(
                3,6,
                3,3
            ) / 3 ==  Tensor22I(
                1,2,
                1,1
            )
        );


        // YX
        expect(
            Tensor22I(
                3,3,
                6,3
            ) / 3 ==  Tensor22I(
                1,1,
                2,1
            )
        );

        // YY
        expect(
            Tensor22I(
                3,3,
                3,6
            ) / 3 ==  Tensor22I(
                1,1,
                1,2
            )
        );


    };

    return ut::cfg<>.run();
};

