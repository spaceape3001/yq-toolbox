////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/vector/Tensor31.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor31U(ZERO) == Tensor31U(ZERO)));
        expect( true == (Tensor31D(ZERO) == Tensor31D(ZERO)));
        expect( true == (Tensor31F(ZERO) == Tensor31F(ZERO)));
        expect( true == (all(Tensor31F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor31I(
                1,
                1,
                1
            ) + Tensor31I(ALL,2) ==  Tensor31I(
                3,
                3,
                3
            )
        );
        
        //  XX
        expect(
            Tensor31I(
                2,
                1,
                1
            ) + Tensor31I(ALL,2) ==  Tensor31I(
                4,
                3,
                3
            )
        );

        //  YX
        expect(
            Tensor31I(
                1,
                2,
                1
            ) + Tensor31I(ALL,2) ==  Tensor31I(
                3,
                4,
                3
            )
        );


        //  ZX
        expect(
            Tensor31I(
                1,
                1,
                2
            ) + Tensor31I(ALL,2) ==  Tensor31I(
                3,
                3,
                4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor31I(
                +1,
                +1,
                +1
            ) - Tensor31I(ALL,2) ==  Tensor31I(
                -1,
                -1,
                -1
            )
        );

        // XX
        expect(
            Tensor31I(
                -1,
                +1,
                +1
            ) - Tensor31I(ALL,2) ==  Tensor31I(
                -3,
                -1,
                -1
            )
        );

        // YX
        expect(
            Tensor31I(
                +1,
                -1,
                +1
            ) - Tensor31I(ALL,2) ==  Tensor31I(
                -1,
                -3,
                -1
            )
        );

        // ZX
        expect(
            Tensor31I(
                +1,
                +1,
                -1
            ) - Tensor31I(ALL,2) ==  Tensor31I(
                -1,
                -1,
                -3
            )
        );

    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor31I(
                1,
                1,
                1
            ) * 3 ==  Tensor31I(
                3,
                3,
                3
            )
        );
        
        // XX
        expect(
            Tensor31I(
                2,
                1,
                1
            ) * 3 ==  Tensor31I(
                6,
                3,
                3
            )
        );

        // YX
        expect(
            Tensor31I(
                1,
                2,
                1
            ) * 3 ==  Tensor31I(
                3,
                6,
                3
            )
        );
        
        // ZX
        expect(
            Tensor31I(
                1,
                1,
                2
            ) * 3 ==  Tensor31I(
                3,
                3,
                6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor31I(
                3,
                3,
                3
            ) / 3 ==  Tensor31I(
                1,
                1,
                1
            )
        );

        // XX
        expect(
            Tensor31I(
                6,
                3,
                3
            ) / 3 ==  Tensor31I(
                2,
                1,
                1
            )
        );

        // YX
        expect(
            Tensor31I(
                3,
                6,
                3
            ) / 3 ==  Tensor31I(
                1,
                2,
                1
            )
        );

        // ZX
        expect(
            Tensor31I(
                3,
                3,
                6
            ) / 3 ==  Tensor31I(
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

