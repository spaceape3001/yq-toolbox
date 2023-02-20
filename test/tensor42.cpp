////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/Tensor42.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor42U(ZERO) == Tensor42U(ZERO)));
        expect( true == (Tensor42D(ZERO) == Tensor42D(ZERO)));
        expect( true == (Tensor42F(ZERO) == Tensor42F(ZERO)));
        expect( true == (all(Tensor42F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor42I(
                1,1,
                1,1,
                1,1,
                1,1
            ) + Tensor42I(ALL,2) ==  Tensor42I(
                3,3,
                3,3,
                3,3,
                3,3
            )
        );
        
        //  XX
        expect(
            Tensor42I(
                2,1,
                1,1,
                1,1,
                1,1
            ) + Tensor42I(ALL,2) ==  Tensor42I(
                4,3,
                3,3,
                3,3,
                3,3
            )
        );

        //  XY
        expect(
            Tensor42I(
                1,2,
                1,1,
                1,1,
                1,1
            ) + Tensor42I(ALL,2) ==  Tensor42I(
                3,4,
                3,3,
                3,3,
                3,3
            )
        );

        //  YX
        expect(
            Tensor42I(
                1,1,
                2,1,
                1,1,
                1,1
            ) + Tensor42I(ALL,2) ==  Tensor42I(
                3,3,
                4,3,
                3,3,
                3,3
            )
        );

        //  YY
        expect(
            Tensor42I(
                1,1,
                1,2,
                1,1,
                1,1
            ) + Tensor42I(ALL,2) ==  Tensor42I(
                3,3,
                3,4,
                3,3,
                3,3
            )
        );

        //  ZX
        expect(
            Tensor42I(
                1,1,
                1,1,
                2,1,
                1,1
            ) + Tensor42I(ALL,2) ==  Tensor42I(
                3,3,
                3,3,
                4,3,
                3,3
            )
        );

        //  ZY
        expect(
            Tensor42I(
                1,1,
                1,1,
                1,2,
                1,1
            ) + Tensor42I(ALL,2) ==  Tensor42I(
                3,3,
                3,3,
                3,4,
                3,3
            )
        );

        //  WX
        expect(
            Tensor42I(
                1,1,
                1,1,
                1,1,
                2,1
            ) + Tensor42I(ALL,2) ==  Tensor42I(
                3,3,
                3,3,
                3,3,
                4,3
            )
        );

        //  WY
        expect(
            Tensor42I(
                1,1,
                1,1,
                1,1,
                1,2
            ) + Tensor42I(ALL,2) ==  Tensor42I(
                3,3,
                3,3,
                3,3,
                3,4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor42I(
                +1,+1,
                +1,+1,
                +1,+1,
                +1,+1
            ) - Tensor42I(ALL,2) ==  Tensor42I(
                -1,-1,
                -1,-1,
                -1,-1,
                -1,-1
            )
        );

        // XX
        expect(
            Tensor42I(
                -1,+1,
                +1,+1,
                +1,+1,
                +1,+1
            ) - Tensor42I(ALL,2) ==  Tensor42I(
                -3,-1,
                -1,-1,
                -1,-1,
                -1,-1
            )
        );

        // XY
        expect(
            Tensor42I(
                +1,-1,
                +1,+1,
                +1,+1,
                +1,+1
            ) - Tensor42I(ALL,2) ==  Tensor42I(
                -1,-3,
                -1,-1,
                -1,-1,
                -1,-1
            )
        );


        // YX
        expect(
            Tensor42I(
                +1,+1,
                -1,+1,
                +1,+1,
                +1,+1
            ) - Tensor42I(ALL,2) ==  Tensor42I(
                -1,-1,
                -3,-1,
                -1,-1,
                -1,-1
            )
        );

        // YY
        expect(
            Tensor42I(
                +1,+1,
                +1,-1,
                +1,+1,
                +1,+1
            ) - Tensor42I(ALL,2) ==  Tensor42I(
                -1,-1,
                -1,-3,
                -1,-1,
                -1,-1
            )
        );

        // ZX
        expect(
            Tensor42I(
                +1,+1,
                +1,+1,
                -1,+1,
                +1,+1
            ) - Tensor42I(ALL,2) ==  Tensor42I(
                -1,-1,
                -1,-1,
                -3,-1,
                -1,-1
            )
        );

        // ZY
        expect(
            Tensor42I(
                +1,+1,
                +1,+1,
                +1,-1,
                +1,+1
            ) - Tensor42I(ALL,2) ==  Tensor42I(
                -1,-1,
                -1,-1,
                -1,-3,
                -1,-1
            )
        );
        
        // WX
        expect(
            Tensor42I(
                +1,+1,
                +1,+1,
                +1,+1,
                -1,+1
            ) - Tensor42I(ALL,2) ==  Tensor42I(
                -1,-1,
                -1,-1,
                -1,-1,
                -3,-1
            )
        );

        // WY
        expect(
            Tensor42I(
                +1,+1,
                +1,+1,
                +1,+1,
                +1,-1
            ) - Tensor42I(ALL,2) ==  Tensor42I(
                -1,-1,
                -1,-1,
                -1,-1,
                -1,-3
            )
        );

    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor42I(
                1,1,
                1,1,
                1,1,
                1,1
            ) * 3 ==  Tensor42I(
                3,3,
                3,3,
                3,3,
                3,3
            )
        );
        
        // XX
        expect(
            Tensor42I(
                2,1,
                1,1,
                1,1,
                1,1
            ) * 3 ==  Tensor42I(
                6,3,
                3,3,
                3,3,
                3,3
            )
        );

        // XY
        expect(
            Tensor42I(
                1,2,
                1,1,
                1,1,
                1,1
            ) * 3 ==  Tensor42I(
                3,6,
                3,3,
                3,3,
                3,3
            )
        );

        
        // YX
        expect(
            Tensor42I(
                1,1,
                2,1,
                1,1,
                1,1
            ) * 3 ==  Tensor42I(
                3,3,
                6,3,
                3,3,
                3,3
            )
        );

        // YY
        expect(
            Tensor42I(
                1,1,
                1,2,
                1,1,
                1,1
            ) * 3 ==  Tensor42I(
                3,3,
                3,6,
                3,3,
                3,3
            )
        );
        
        // ZX
        expect(
            Tensor42I(
                1,1,
                1,1,
                2,1,
                1,1
            ) * 3 ==  Tensor42I(
                3,3,
                3,3,
                6,3,
                3,3
            )
        );

        // ZY
        expect(
            Tensor42I(
                1,1,
                1,1,
                1,2,
                1,1
            ) * 3 ==  Tensor42I(
                3,3,
                3,3,
                3,6,
                3,3
            )
        );

        
        // WX
        expect(
            Tensor42I(
                1,1,
                1,1,
                1,1,
                2,1
            ) * 3 ==  Tensor42I(
                3,3,
                3,3,
                3,3,
                6,3
            )
        );

        // WY
        expect(
            Tensor42I(
                1,1,
                1,1,
                1,1,
                1,2
            ) * 3 ==  Tensor42I(
                3,3,
                3,3,
                3,3,
                3,6
            )
        );

    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor42I(
                3,3,
                3,3,
                3,3,
                3,3
            ) / 3 ==  Tensor42I(
                1,1,
                1,1,
                1,1,
                1,1
            )
        );

        // XX
        expect(
            Tensor42I(
                6,3,
                3,3,
                3,3,
                3,3
            ) / 3 ==  Tensor42I(
                2,1,
                1,1,
                1,1,
                1,1
            )
        );

        // XY
        expect(
            Tensor42I(
                3,6,
                3,3,
                3,3,
                3,3
            ) / 3 ==  Tensor42I(
                1,2,
                1,1,
                1,1,
                1,1
            )
        );


        // YX
        expect(
            Tensor42I(
                3,3,
                6,3,
                3,3,
                3,3
            ) / 3 ==  Tensor42I(
                1,1,
                2,1,
                1,1,
                1,1
            )
        );

        // YY
        expect(
            Tensor42I(
                3,3,
                3,6,
                3,3,
                3,3
            ) / 3 ==  Tensor42I(
                1,1,
                1,2,
                1,1,
                1,1
            )
        );

        // ZX
        expect(
            Tensor42I(
                3,3,
                3,3,
                6,3,
                3,3
            ) / 3 ==  Tensor42I(
                1,1,
                1,1,
                2,1,
                1,1
            )
        );

        // ZY
        expect(
            Tensor42I(
                3,3,
                3,3,
                3,6,
                3,3
            ) / 3 ==  Tensor42I(
                1,1,
                1,1,
                1,2,
                1,1
            )
        );

        // WX
        expect(
            Tensor42I(
                3,3,
                3,3,
                3,3,
                6,3
            ) / 3 ==  Tensor42I(
                1,1,
                1,1,
                1,1,
                2,1
            )
        );

        // WY
        expect(
            Tensor42I(
                3,3,
                3,3,
                3,3,
                3,6
            ) / 3 ==  Tensor42I(
                1,1,
                1,1,
                1,1,
                1,2
            )
        );

    };
};

int main(){
    return ut::cfg<>.run();
};

