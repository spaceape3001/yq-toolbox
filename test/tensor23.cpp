////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/vector/Tensor23.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor23U(ZERO) == Tensor23U(ZERO)));
        expect( true == (Tensor23D(ZERO) == Tensor23D(ZERO)));
        expect( true == (Tensor23F(ZERO) == Tensor23F(ZERO)));
        expect( true == (all(Tensor23F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor23I(
                1,1,1,
                1,1,1
            ) + Tensor23I(ALL,2) ==  Tensor23I(
                3,3,3,
                3,3,3
            )
        );
        
        //  XX
        expect(
            Tensor23I(
                2,1,1,
                1,1,1
            ) + Tensor23I(ALL,2) ==  Tensor23I(
                4,3,3,
                3,3,3
            )
        );

        //  XY
        expect(
            Tensor23I(
                1,2,1,
                1,1,1
            ) + Tensor23I(ALL,2) ==  Tensor23I(
                3,4,3,
                3,3,3
            )
        );

        //  XZ
        expect(
            Tensor23I(
                1,1,2,
                1,1,1
            ) + Tensor23I(ALL,2) ==  Tensor23I(
                3,3,4,
                3,3,3
            )
        );

        //  YX
        expect(
            Tensor23I(
                1,1,1,
                2,1,1
            ) + Tensor23I(ALL,2) ==  Tensor23I(
                3,3,3,
                4,3,3
            )
        );

        //  YY
        expect(
            Tensor23I(
                1,1,1,
                1,2,1
            ) + Tensor23I(ALL,2) ==  Tensor23I(
                3,3,3,
                3,4,3
            )
        );

        //  YZ
        expect(
            Tensor23I(
                1,1,1,
                1,1,2
            ) + Tensor23I(ALL,2) ==  Tensor23I(
                3,3,3,
                3,3,4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor23I(
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor23I(ALL,2) ==  Tensor23I(
                -1,-1,-1,
                -1,-1,-1
            )
        );

        // XX
        expect(
            Tensor23I(
                -1,+1,+1,
                +1,+1,+1
            ) - Tensor23I(ALL,2) ==  Tensor23I(
                -3,-1,-1,
                -1,-1,-1
            )
        );

        // XY
        expect(
            Tensor23I(
                +1,-1,+1,
                +1,+1,+1
            ) - Tensor23I(ALL,2) ==  Tensor23I(
                -1,-3,-1,
                -1,-1,-1
            )
        );

        // XZ
        expect(
            Tensor23I(
                +1,+1,-1,
                +1,+1,+1
            ) - Tensor23I(ALL,2) ==  Tensor23I(
                -1,-1,-3,
                -1,-1,-1
            )
        );


        // YX
        expect(
            Tensor23I(
                +1,+1,+1,
                -1,+1,+1
            ) - Tensor23I(ALL,2) ==  Tensor23I(
                -1,-1,-1,
                -3,-1,-1
            )
        );

        // YY
        expect(
            Tensor23I(
                +1,+1,+1,
                +1,-1,+1
            ) - Tensor23I(ALL,2) ==  Tensor23I(
                -1,-1,-1,
                -1,-3,-1
            )
        );

        // YZ
        expect(
            Tensor23I(
                +1,+1,+1,
                +1,+1,-1
            ) - Tensor23I(ALL,2) ==  Tensor23I(
                -1,-1,-1,
                -1,-1,-3
            )
        );
    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor23I(
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor23I(
                3,3,3,
                3,3,3
            )
        );
        
        // XX
        expect(
            Tensor23I(
                2,1,1,
                1,1,1
            ) * 3 ==  Tensor23I(
                6,3,3,
                3,3,3
            )
        );

        // XY
        expect(
            Tensor23I(
                1,2,1,
                1,1,1
            ) * 3 ==  Tensor23I(
                3,6,3,
                3,3,3
            )
        );

        // XZ
        expect(
            Tensor23I(
                1,1,2,
                1,1,1
            ) * 3 ==  Tensor23I(
                3,3,6,
                3,3,3
            )
        );

        
        // YX
        expect(
            Tensor23I(
                1,1,1,
                2,1,1
            ) * 3 ==  Tensor23I(
                3,3,3,
                6,3,3
            )
        );

        // YY
        expect(
            Tensor23I(
                1,1,1,
                1,2,1
            ) * 3 ==  Tensor23I(
                3,3,3,
                3,6,3
            )
        );

        // YZ
        expect(
            Tensor23I(
                1,1,1,
                1,1,2
            ) * 3 ==  Tensor23I(
                3,3,3,
                3,3,6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor23I(
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor23I(
                1,1,1,
                1,1,1
            )
        );

        // XX
        expect(
            Tensor23I(
                6,3,3,
                3,3,3
            ) / 3 ==  Tensor23I(
                2,1,1,
                1,1,1
            )
        );

        // XY
        expect(
            Tensor23I(
                3,6,3,
                3,3,3
            ) / 3 ==  Tensor23I(
                1,2,1,
                1,1,1
            )
        );

        // XZ
        expect(
            Tensor23I(
                3,3,6,
                3,3,3
            ) / 3 ==  Tensor23I(
                1,1,2,
                1,1,1
            )
        );


        // YX
        expect(
            Tensor23I(
                3,3,3,
                6,3,3
            ) / 3 ==  Tensor23I(
                1,1,1,
                2,1,1
            )
        );

        // YY
        expect(
            Tensor23I(
                3,3,3,
                3,6,3
            ) / 3 ==  Tensor23I(
                1,1,1,
                1,2,1
            )
        );

        // YZ
        expect(
            Tensor23I(
                3,3,3,
                3,3,6
            ) / 3 ==  Tensor23I(
                1,1,1,
                1,1,2
            )
        );
    };
};

int main(){
    return ut::cfg<>.run();
};

