////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/vector/Tensor32.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor32U(ZERO) == Tensor32U(ZERO)));
        expect( true == (Tensor32D(ZERO) == Tensor32D(ZERO)));
        expect( true == (Tensor32F(ZERO) == Tensor32F(ZERO)));
        expect( true == (all(Tensor32F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor32I(
                1,1,
                1,1,
                1,1
            ) + Tensor32I(ALL,2) ==  Tensor32I(
                3,3,
                3,3,
                3,3
            )
        );
        
        //  XX
        expect(
            Tensor32I(
                2,1,
                1,1,
                1,1
            ) + Tensor32I(ALL,2) ==  Tensor32I(
                4,3,
                3,3,
                3,3
            )
        );

        //  XY
        expect(
            Tensor32I(
                1,2,
                1,1,
                1,1
            ) + Tensor32I(ALL,2) ==  Tensor32I(
                3,4,
                3,3,
                3,3
            )
        );

        //  YX
        expect(
            Tensor32I(
                1,1,
                2,1,
                1,1
            ) + Tensor32I(ALL,2) ==  Tensor32I(
                3,3,
                4,3,
                3,3
            )
        );

        //  YY
        expect(
            Tensor32I(
                1,1,
                1,2,
                1,1
            ) + Tensor32I(ALL,2) ==  Tensor32I(
                3,3,
                3,4,
                3,3
            )
        );

        //  ZX
        expect(
            Tensor32I(
                1,1,
                1,1,
                2,1
            ) + Tensor32I(ALL,2) ==  Tensor32I(
                3,3,
                3,3,
                4,3
            )
        );

        //  ZY
        expect(
            Tensor32I(
                1,1,
                1,1,
                1,2
            ) + Tensor32I(ALL,2) ==  Tensor32I(
                3,3,
                3,3,
                3,4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor32I(
                +1,+1,
                +1,+1,
                +1,+1
            ) - Tensor32I(ALL,2) ==  Tensor32I(
                -1,-1,
                -1,-1,
                -1,-1
            )
        );

        // XX
        expect(
            Tensor32I(
                -1,+1,
                +1,+1,
                +1,+1
            ) - Tensor32I(ALL,2) ==  Tensor32I(
                -3,-1,
                -1,-1,
                -1,-1
            )
        );

        // XY
        expect(
            Tensor32I(
                +1,-1,
                +1,+1,
                +1,+1
            ) - Tensor32I(ALL,2) ==  Tensor32I(
                -1,-3,
                -1,-1,
                -1,-1
            )
        );


        // YX
        expect(
            Tensor32I(
                +1,+1,
                -1,+1,
                +1,+1
            ) - Tensor32I(ALL,2) ==  Tensor32I(
                -1,-1,
                -3,-1,
                -1,-1
            )
        );

        // YY
        expect(
            Tensor32I(
                +1,+1,
                +1,-1,
                +1,+1
            ) - Tensor32I(ALL,2) ==  Tensor32I(
                -1,-1,
                -1,-3,
                -1,-1
            )
        );

        // ZX
        expect(
            Tensor32I(
                +1,+1,
                +1,+1,
                -1,+1
            ) - Tensor32I(ALL,2) ==  Tensor32I(
                -1,-1,
                -1,-1,
                -3,-1
            )
        );

        // ZY
        expect(
            Tensor32I(
                +1,+1,
                +1,+1,
                +1,-1
            ) - Tensor32I(ALL,2) ==  Tensor32I(
                -1,-1,
                -1,-1,
                -1,-3
            )
        );
    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor32I(
                1,1,
                1,1,
                1,1
            ) * 3 ==  Tensor32I(
                3,3,
                3,3,
                3,3
            )
        );
        
        // XX
        expect(
            Tensor32I(
                2,1,
                1,1,
                1,1
            ) * 3 ==  Tensor32I(
                6,3,
                3,3,
                3,3
            )
        );

        // XY
        expect(
            Tensor32I(
                1,2,
                1,1,
                1,1
            ) * 3 ==  Tensor32I(
                3,6,
                3,3,
                3,3
            )
        );

        
        // YX
        expect(
            Tensor32I(
                1,1,
                2,1,
                1,1
            ) * 3 ==  Tensor32I(
                3,3,
                6,3,
                3,3
            )
        );

        // YY
        expect(
            Tensor32I(
                1,1,
                1,2,
                1,1
            ) * 3 ==  Tensor32I(
                3,3,
                3,6,
                3,3
            )
        );
        
        // ZX
        expect(
            Tensor32I(
                1,1,
                1,1,
                2,1
            ) * 3 ==  Tensor32I(
                3,3,
                3,3,
                6,3
            )
        );

        // ZY
        expect(
            Tensor32I(
                1,1,
                1,1,
                1,2
            ) * 3 ==  Tensor32I(
                3,3,
                3,3,
                3,6
            )
        );

    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor32I(
                3,3,
                3,3,
                3,3
            ) / 3 ==  Tensor32I(
                1,1,
                1,1,
                1,1
            )
        );

        // XX
        expect(
            Tensor32I(
                6,3,
                3,3,
                3,3
            ) / 3 ==  Tensor32I(
                2,1,
                1,1,
                1,1
            )
        );

        // XY
        expect(
            Tensor32I(
                3,6,
                3,3,
                3,3
            ) / 3 ==  Tensor32I(
                1,2,
                1,1,
                1,1
            )
        );


        // YX
        expect(
            Tensor32I(
                3,3,
                6,3,
                3,3
            ) / 3 ==  Tensor32I(
                1,1,
                2,1,
                1,1
            )
        );

        // YY
        expect(
            Tensor32I(
                3,3,
                3,6,
                3,3
            ) / 3 ==  Tensor32I(
                1,1,
                1,2,
                1,1
            )
        );

        // ZX
        expect(
            Tensor32I(
                3,3,
                3,3,
                6,3
            ) / 3 ==  Tensor32I(
                1,1,
                1,1,
                2,1
            )
        );

        // ZY
        expect(
            Tensor32I(
                3,3,
                3,3,
                3,6
            ) / 3 ==  Tensor32I(
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

