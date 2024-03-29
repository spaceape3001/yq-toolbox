////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/vector/Tensor41.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor41U(ZERO) == Tensor41U(ZERO)));
        expect( true == (Tensor41D(ZERO) == Tensor41D(ZERO)));
        expect( true == (Tensor41F(ZERO) == Tensor41F(ZERO)));
        expect( true == (all(Tensor41F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor41I(
                1,
                1,
                1,
                1
            ) + Tensor41I(ALL,2) ==  Tensor41I(
                3,
                3,
                3,
                3
            )
        );
        
        //  XX
        expect(
            Tensor41I(
                2,
                1,
                1,
                1
            ) + Tensor41I(ALL,2) ==  Tensor41I(
                4,
                3,
                3,
                3
            )
        );

        //  YX
        expect(
            Tensor41I(
                1,
                2,
                1,
                1
            ) + Tensor41I(ALL,2) ==  Tensor41I(
                3,
                4,
                3,
                3
            )
        );


        //  ZX
        expect(
            Tensor41I(
                1,
                1,
                2,
                1
            ) + Tensor41I(ALL,2) ==  Tensor41I(
                3,
                3,
                4,
                3
            )
        );

        //  WX
        expect(
            Tensor41I(
                1,
                1,
                1,
                2
            ) + Tensor41I(ALL,2) ==  Tensor41I(
                3,
                3,
                3,
                4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor41I(
                +1,
                +1,
                +1,
                +1
            ) - Tensor41I(ALL,2) ==  Tensor41I(
                -1,
                -1,
                -1,
                -1
            )
        );

        // XX
        expect(
            Tensor41I(
                -1,
                +1,
                +1,
                +1
            ) - Tensor41I(ALL,2) ==  Tensor41I(
                -3,
                -1,
                -1,
                -1
            )
        );

        // YX
        expect(
            Tensor41I(
                +1,
                -1,
                +1,
                +1
            ) - Tensor41I(ALL,2) ==  Tensor41I(
                -1,
                -3,
                -1,
                -1
            )
        );

        // ZX
        expect(
            Tensor41I(
                +1,
                +1,
                -1,
                +1
            ) - Tensor41I(ALL,2) ==  Tensor41I(
                -1,
                -1,
                -3,
                -1
            )
        );

        // WX
        expect(
            Tensor41I(
                +1,
                +1,
                +1,
                -1
            ) - Tensor41I(ALL,2) ==  Tensor41I(
                -1,
                -1,
                -1,
                -3
            )
        );

    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor41I(
                1,
                1,
                1,
                1
            ) * 3 ==  Tensor41I(
                3,
                3,
                3,
                3
            )
        );
        
        // XX
        expect(
            Tensor41I(
                2,
                1,
                1,
                1
            ) * 3 ==  Tensor41I(
                6,
                3,
                3,
                3
            )
        );

        // YX
        expect(
            Tensor41I(
                1,
                2,
                1,
                1
            ) * 3 ==  Tensor41I(
                3,
                6,
                3,
                3
            )
        );
        
        // ZX
        expect(
            Tensor41I(
                1,
                1,
                2,
                1
            ) * 3 ==  Tensor41I(
                3,
                3,
                6,
                3
            )
        );

        // WX
        expect(
            Tensor41I(
                1,
                1,
                1,
                2
            ) * 3 ==  Tensor41I(
                3,
                3,
                3,
                6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor41I(
                3,
                3,
                3,
                3
            ) / 3 ==  Tensor41I(
                1,
                1,
                1,
                1
            )
        );

        // XX
        expect(
            Tensor41I(
                6,
                3,
                3,
                3
            ) / 3 ==  Tensor41I(
                2,
                1,
                1,
                1
            )
        );

        // YX
        expect(
            Tensor41I(
                3,
                6,
                3,
                3
            ) / 3 ==  Tensor41I(
                1,
                2,
                1,
                1
            )
        );

        // ZX
        expect(
            Tensor41I(
                3,
                3,
                6,
                3
            ) / 3 ==  Tensor41I(
                1,
                1,
                2,
                1
            )
        );

        // WX
        expect(
            Tensor41I(
                3,
                3,
                3,
                6
            ) / 3 ==  Tensor41I(
                1,
                1,
                1,
                2
            )
        );

    };
};

int main(){
    return ut::cfg<>.run();
};

