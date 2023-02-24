////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/Tensor12.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor12U(ZERO) == Tensor12U(ZERO)));
        expect( true == (Tensor12D(ZERO) == Tensor12D(ZERO)));
        expect( true == (Tensor12F(ZERO) == Tensor12F(ZERO)));
        expect( true == (all(Tensor12F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor12I(
                1,1
            ) + Tensor12I(ALL,2) ==  Tensor12I(
                3,3
            )
        );
        
        //  XX
        expect(
            Tensor12I(
                2,1
            ) + Tensor12I(ALL,2) ==  Tensor12I(
                4,3
            )
        );

        //  XY
        expect(
            Tensor12I(
                1,2
            ) + Tensor12I(ALL,2) ==  Tensor12I(
                3,4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor12I(
                +1,+1
            ) - Tensor12I(ALL,2) ==  Tensor12I(
                -1,-1
            )
        );

        // XX
        expect(
            Tensor12I(
                -1,+1
            ) - Tensor12I(ALL,2) ==  Tensor12I(
                -3,-1
            )
        );

        // XY
        expect(
            Tensor12I(
                +1,-1
            ) - Tensor12I(ALL,2) ==  Tensor12I(
                -1,-3
            )
        );

    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor12I(
                1,1
            ) * 3 ==  Tensor12I(
                3,3
            )
        );
        
        // XX
        expect(
            Tensor12I(
                2,1
            ) * 3 ==  Tensor12I(
                6,3
            )
        );

        // XY
        expect(
            Tensor12I(
                1,2
            ) * 3 ==  Tensor12I(
                3,6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor12I(
                3,3
            ) / 3 ==  Tensor12I(
                1,1
            )
        );

        // XX
        expect(
            Tensor12I(
                6,3
            ) / 3 ==  Tensor12I(
                2,1
            )
        );

        // XY
        expect(
            Tensor12I(
                3,6
            ) / 3 ==  Tensor12I(
                1,2
            )
        );
    };
};

int main(){
    return ut::cfg<>.run();
};

