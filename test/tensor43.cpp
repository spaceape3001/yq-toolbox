////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/vector/Tensor43.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor43U(ZERO) == Tensor43U(ZERO)));
        expect( true == (Tensor43D(ZERO) == Tensor43D(ZERO)));
        expect( true == (Tensor43F(ZERO) == Tensor43F(ZERO)));
        expect( true == (all(Tensor43F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                1,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                3,3,3
            )
        );
        
        //  XX
        expect(
            Tensor43I(
                2,1,1,
                1,1,1,
                1,1,1,
                1,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                4,3,3,
                3,3,3,
                3,3,3,
                3,3,3
            )
        );

        //  XY
        expect(
            Tensor43I(
                1,2,1,
                1,1,1,
                1,1,1,
                1,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,4,3,
                3,3,3,
                3,3,3,
                3,3,3
            )
        );

        //  XZ
        expect(
            Tensor43I(
                1,1,2,
                1,1,1,
                1,1,1,
                1,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,4,
                3,3,3,
                3,3,3,
                3,3,3
            )
        );

        //  YX
        expect(
            Tensor43I(
                1,1,1,
                2,1,1,
                1,1,1,
                1,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,3,
                4,3,3,
                3,3,3,
                3,3,3
            )
        );

        //  YY
        expect(
            Tensor43I(
                1,1,1,
                1,2,1,
                1,1,1,
                1,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,3,
                3,4,3,
                3,3,3,
                3,3,3
            )
        );

        //  YZ
        expect(
            Tensor43I(
                1,1,1,
                1,1,2,
                1,1,1,
                1,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,3,
                3,3,4,
                3,3,3,
                3,3,3
            )
        );

        //  ZX
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                2,1,1,
                1,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,3,
                3,3,3,
                4,3,3,
                3,3,3
            )
        );

        //  ZY
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,2,1,
                1,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,4,3,
                3,3,3
            )
        );

        //  ZZ
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,1,2,
                1,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,3,4,
                3,3,3
            )
        );

        //  WX
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                2,1,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                4,3,3
            )
        );

        //  WY
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                1,2,1
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                3,4,3
            )
        );

        //  WZ
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                1,1,2
            ) + Tensor43I(ALL,2) ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                3,3,4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor43I(
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-1
            )
        );

        // XX
        expect(
            Tensor43I(
                -1,+1,+1,
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -3,-1,-1,
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-1
            )
        );

        // XY
        expect(
            Tensor43I(
                +1,-1,+1,
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-3,-1,
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-1
            )
        );

        // XZ
        expect(
            Tensor43I(
                +1,+1,-1,
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-3,
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-1
            )
        );


        // YX
        expect(
            Tensor43I(
                +1,+1,+1,
                -1,+1,+1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-1,
                -3,-1,-1,
                -1,-1,-1,
                -1,-1,-1
            )
        );

        // YY
        expect(
            Tensor43I(
                +1,+1,+1,
                +1,-1,+1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-1,
                -1,-3,-1,
                -1,-1,-1,
                -1,-1,-1
            )
        );

        // YZ
        expect(
            Tensor43I(
                +1,+1,+1,
                +1,+1,-1,
                +1,+1,+1,
                +1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-1,
                -1,-1,-3,
                -1,-1,-1,
                -1,-1,-1
            )
        );

        // ZX
        expect(
            Tensor43I(
                +1,+1,+1,
                +1,+1,+1,
                -1,+1,+1,
                +1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-1,
                -1,-1,-1,
                -3,-1,-1,
                -1,-1,-1
            )
        );

        // ZY
        expect(
            Tensor43I(
                +1,+1,+1,
                +1,+1,+1,
                +1,-1,+1,
                +1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-1,
                -1,-1,-1,
                -1,-3,-1,
                -1,-1,-1
            )
        );

        // ZZ
        expect(
            Tensor43I(
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,-1,
                +1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-3,
                -1,-1,-1
            )
        );
        
        // WX
        expect(
            Tensor43I(
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,+1,
                -1,+1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-1,
                -3,-1,-1
            )
        );

        // WY
        expect(
            Tensor43I(
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,+1,
                +1,-1,+1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-1,
                -1,-3,-1
            )
        );

        // WZ
        expect(
            Tensor43I(
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,+1,
                +1,+1,-1
            ) - Tensor43I(ALL,2) ==  Tensor43I(
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-1,
                -1,-1,-3
            )
        );

    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                3,3,3
            )
        );
        
        // XX
        expect(
            Tensor43I(
                2,1,1,
                1,1,1,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor43I(
                6,3,3,
                3,3,3,
                3,3,3,
                3,3,3
            )
        );

        // XY
        expect(
            Tensor43I(
                1,2,1,
                1,1,1,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor43I(
                3,6,3,
                3,3,3,
                3,3,3,
                3,3,3
            )
        );

        // XZ
        expect(
            Tensor43I(
                1,1,2,
                1,1,1,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor43I(
                3,3,6,
                3,3,3,
                3,3,3,
                3,3,3
            )
        );

        
        // YX
        expect(
            Tensor43I(
                1,1,1,
                2,1,1,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor43I(
                3,3,3,
                6,3,3,
                3,3,3,
                3,3,3
            )
        );

        // YY
        expect(
            Tensor43I(
                1,1,1,
                1,2,1,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor43I(
                3,3,3,
                3,6,3,
                3,3,3,
                3,3,3
            )
        );

        // YZ
        expect(
            Tensor43I(
                1,1,1,
                1,1,2,
                1,1,1,
                1,1,1
            ) * 3 ==  Tensor43I(
                3,3,3,
                3,3,6,
                3,3,3,
                3,3,3
            )
        );
        
        // ZX
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                2,1,1,
                1,1,1
            ) * 3 ==  Tensor43I(
                3,3,3,
                3,3,3,
                6,3,3,
                3,3,3
            )
        );

        // ZY
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,2,1,
                1,1,1
            ) * 3 ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,6,3,
                3,3,3
            )
        );

        // ZZ
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,1,2,
                1,1,1
            ) * 3 ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,3,6,
                3,3,3
            )
        );

        
        // WX
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                2,1,1
            ) * 3 ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                6,3,3
            )
        );

        // WY
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                1,2,1
            ) * 3 ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                3,6,3
            )
        );

        // WZ
        expect(
            Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                1,1,2
            ) * 3 ==  Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                3,3,6
            )
        );

    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                1,1,1
            )
        );

        // XX
        expect(
            Tensor43I(
                6,3,3,
                3,3,3,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor43I(
                2,1,1,
                1,1,1,
                1,1,1,
                1,1,1
            )
        );

        // XY
        expect(
            Tensor43I(
                3,6,3,
                3,3,3,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor43I(
                1,2,1,
                1,1,1,
                1,1,1,
                1,1,1
            )
        );

        // XZ
        expect(
            Tensor43I(
                3,3,6,
                3,3,3,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor43I(
                1,1,2,
                1,1,1,
                1,1,1,
                1,1,1
            )
        );


        // YX
        expect(
            Tensor43I(
                3,3,3,
                6,3,3,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor43I(
                1,1,1,
                2,1,1,
                1,1,1,
                1,1,1
            )
        );

        // YY
        expect(
            Tensor43I(
                3,3,3,
                3,6,3,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor43I(
                1,1,1,
                1,2,1,
                1,1,1,
                1,1,1
            )
        );

        // YZ
        expect(
            Tensor43I(
                3,3,3,
                3,3,6,
                3,3,3,
                3,3,3
            ) / 3 ==  Tensor43I(
                1,1,1,
                1,1,2,
                1,1,1,
                1,1,1
            )
        );


        // ZX
        expect(
            Tensor43I(
                3,3,3,
                3,3,3,
                6,3,3,
                3,3,3
            ) / 3 ==  Tensor43I(
                1,1,1,
                1,1,1,
                2,1,1,
                1,1,1
            )
        );

        // ZY
        expect(
            Tensor43I(
                3,3,3,
                3,3,3,
                3,6,3,
                3,3,3
            ) / 3 ==  Tensor43I(
                1,1,1,
                1,1,1,
                1,2,1,
                1,1,1
            )
        );

        // ZZ
        expect(
            Tensor43I(
                3,3,3,
                3,3,3,
                3,3,6,
                3,3,3
            ) / 3 ==  Tensor43I(
                1,1,1,
                1,1,1,
                1,1,2,
                1,1,1
            )
        );


        // WX
        expect(
            Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                6,3,3
            ) / 3 ==  Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                2,1,1
            )
        );

        // WY
        expect(
            Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                3,6,3
            ) / 3 ==  Tensor43I(
                1,1,1,
                1,1,1,
                1,1,1,
                1,2,1
            )
        );

        // WZ
        expect(
            Tensor43I(
                3,3,3,
                3,3,3,
                3,3,3,
                3,3,6
            ) / 3 ==  Tensor43I(
                1,1,1,
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

