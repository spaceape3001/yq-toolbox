////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/Tensor33.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor33U(ZERO) == Tensor33U(ZERO)));
        expect( true == (Tensor33D(ZERO) == Tensor33D(ZERO)));
        expect( true == (Tensor33F(ZERO) == Tensor33F(ZERO)));
        expect( true == (all(Tensor33F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor33I(
                1,1,1,
                1,1,1,
                1,1,1
            ) + Tensor33I(ALL,2) ==  Tensor33I(
                3,3,3,
                3,3,3,
                3,3,3
            )
        );
        
        //  XX
        expect(
            Tensor33I(
                2,1,1,
                1,1,1,
                1,1,1
            ) + Tensor33I(ALL,2) ==  Tensor33I(
                4,3,3,
                3,3,3,
                3,3,3
            )
        );

        //  XY
        expect(
            Tensor33I(
                1,2,1,
                1,1,1,
                1,1,1
            ) + Tensor33I(ALL,2) ==  Tensor33I(
                3,4,3,
                3,3,3,
                3,3,3
            )
        );

        //  XZ
        expect(
            Tensor33I(
                1,1,2,
                1,1,1,
                1,1,1
            ) + Tensor33I(ALL,2) ==  Tensor33I(
                3,3,4,
                3,3,3,
                3,3,3
            )
        );

        //  YX
        expect(
            Tensor33I(
                1,1,1,
                2,1,1,
                1,1,1
            ) + Tensor33I(ALL,2) ==  Tensor33I(
                3,3,3,
                4,3,3,
                3,3,3
            )
        );

        //  YY
        expect(
            Tensor33I(
                1,1,1,
                1,2,1,
                1,1,1
            ) + Tensor33I(ALL,2) ==  Tensor33I(
                3,3,3,
                3,4,3,
                3,3,3
            )
        );

        //  YZ
        expect(
            Tensor33I(
                1,1,1,
                1,1,2,
                1,1,1
            ) + Tensor33I(ALL,2) ==  Tensor33I(
                3,3,3,
                3,3,4,
                3,3,3
            )
        );

        //  ZX
        expect(
            Tensor33I(
                1,1,1,
                1,1,1,
                2,1,1
            ) + Tensor33I(ALL,2) ==  Tensor33I(
                3,3,3,
                3,3,3,
                4,3,3
            )
        );

        //  ZY
        expect(
            Tensor33I(
                1,1,1,
                1,1,1,
                1,2,1
            ) + Tensor33I(ALL,2) ==  Tensor33I(
                3,3,3,
                3,3,3,
                3,4,3
            )
        );

        //  ZZ
        expect(
            Tensor33I(
                1,1,1,
                1,1,1,
                1,1,2
            ) + Tensor33I(ALL,2) ==  Tensor33I(
                3,3,3,
                3,3,3,
                3,3,4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor33I(
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor33I(ALL,2) ==  Tensor33I(
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-1
            )
        );

        // XX
        expect(
            Tensor33I(
                -1,+1,+1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor33I(ALL,2) ==  Tensor33I(
                -3,-1,-1,
                -1,-1,-1,
                -1,-1,-1
            )
        );

        // XY
        expect(
            Tensor33I(
                +1,-1,+1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor33I(ALL,2) ==  Tensor33I(
                -1,-3,-1,
                -1,-1,-1,
                -1,-1,-1
            )
        );

        // XZ
        expect(
            Tensor33I(
                +1,+1,-1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor33I(ALL,2) ==  Tensor33I(
                -1,-1,-3,
                -1,-1,-1,
                -1,-1,-1
            )
        );


        // YX
        expect(
            Tensor33I(
                +1,+1,+1,
                -1,+1,+1,
                +1,+1,+1
            ) - Tensor33I(ALL,2) ==  Tensor33I(
                -1,-1,-1,
                -3,-1,-1,
                -1,-1,-1
            )
        );

        // YY
        expect(
            Tensor33I(
                +1,+1,+1,
                +1,-1,+1,
                +1,+1,+1
            ) - Tensor33I(ALL,2) ==  Tensor33I(
                -1,-1,-1,
                -1,-3,-1,
                -1,-1,-1
            )
        );

        // YZ
        expect(
            Tensor33I(
                +1,+1,+1,
                +1,+1,-1,
                +1,+1,+1
            ) - Tensor33I(ALL,2) ==  Tensor33I(
                -1,-1,-1,
                -1,-1,-3,
                -1,-1,-1
            )
        );

        // ZX
        expect(
            Tensor33I(
                +1,+1,+1,
                +1,+1,+1,
                -1,+1,+1
            ) - Tensor33I(ALL,2) ==  Tensor33I(
                -1,-1,-1,
                -1,-1,-1,
                -3,-1,-1
            )
        );

        // ZY
        expect(
            Tensor33I(
                +1,+1,+1,
                +1,+1,+1,
                +1,-1,+1
            ) - Tensor33I(ALL,2) ==  Tensor33I(
                -1,-1,-1,
                -1,-1,-1,
                -1,-3,-1
            )
        );

        // ZZ
        expect(
            Tensor33I(
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,-1
            ) - Tensor33I(ALL,2) ==  Tensor33I(
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-3
            )
        );
        
    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor33I(
                1,1,1,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor33I(
                3,3,3,
                3,3,3,
                3,3,3
            )
        );
        
        // XX
        expect(
            Tensor33I(
                2,1,1,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor33I(
                6,3,3,
                3,3,3,
                3,3,3
            )
        );

        // XY
        expect(
            Tensor33I(
                1,2,1,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor33I(
                3,6,3,
                3,3,3,
                3,3,3
            )
        );

        // XZ
        expect(
            Tensor33I(
                1,1,2,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor33I(
                3,3,6,
                3,3,3,
                3,3,3
            )
        );

        
        // YX
        expect(
            Tensor33I(
                1,1,1,
                2,1,1,
                1,1,1
            ) * 3 ==  Tensor33I(
                3,3,3,
                6,3,3,
                3,3,3
            )
        );

        // YY
        expect(
            Tensor33I(
                1,1,1,
                1,2,1,
                1,1,1
            ) * 3 ==  Tensor33I(
                3,3,3,
                3,6,3,
                3,3,3
            )
        );

        // YZ
        expect(
            Tensor33I(
                1,1,1,
                1,1,2,
                1,1,1
            ) * 3 ==  Tensor33I(
                3,3,3,
                3,3,6,
                3,3,3
            )
        );
        
        // ZX
        expect(
            Tensor33I(
                1,1,1,
                1,1,1,
                2,1,1
            ) * 3 ==  Tensor33I(
                3,3,3,
                3,3,3,
                6,3,3
            )
        );

        // ZY
        expect(
            Tensor33I(
                1,1,1,
                1,1,1,
                1,2,1
            ) * 3 ==  Tensor33I(
                3,3,3,
                3,3,3,
                3,6,3
            )
        );

        // ZZ
        expect(
            Tensor33I(
                1,1,1,
                1,1,1,
                1,1,2
            ) * 3 ==  Tensor33I(
                3,3,3,
                3,3,3,
                3,3,6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor33I(
                3,3,3,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor33I(
                1,1,1,
                1,1,1,
                1,1,1
            )
        );

        // XX
        expect(
            Tensor33I(
                6,3,3,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor33I(
                2,1,1,
                1,1,1,
                1,1,1
            )
        );

        // XY
        expect(
            Tensor33I(
                3,6,3,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor33I(
                1,2,1,
                1,1,1,
                1,1,1
            )
        );

        // XZ
        expect(
            Tensor33I(
                3,3,6,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor33I(
                1,1,2,
                1,1,1,
                1,1,1
            )
        );


        // YX
        expect(
            Tensor33I(
                3,3,3,
                6,3,3,
                3,3,3
            ) / 3 ==  Tensor33I(
                1,1,1,
                2,1,1,
                1,1,1
            )
        );

        // YY
        expect(
            Tensor33I(
                3,3,3,
                3,6,3,
                3,3,3
            ) / 3 ==  Tensor33I(
                1,1,1,
                1,2,1,
                1,1,1
            )
        );

        // YZ
        expect(
            Tensor33I(
                3,3,3,
                3,3,6,
                3,3,3
            ) / 3 ==  Tensor33I(
                1,1,1,
                1,1,2,
                1,1,1
            )
        );


        // ZX
        expect(
            Tensor33I(
                3,3,3,
                3,3,3,
                6,3,3
            ) / 3 ==  Tensor33I(
                1,1,1,
                1,1,1,
                2,1,1
            )
        );

        // ZY
        expect(
            Tensor33I(
                3,3,3,
                3,3,3,
                3,6,3
            ) / 3 ==  Tensor33I(
                1,1,1,
                1,1,1,
                1,2,1
            )
        );

        // ZZ
        expect(
            Tensor33I(
                3,3,3,
                3,3,3,
                3,3,6
            ) / 3 ==  Tensor33I(
                1,1,1,
                1,1,1,
                1,1,2
            )
        );
    };
};

int main(){
    return ut::cfg<>.run();
};

