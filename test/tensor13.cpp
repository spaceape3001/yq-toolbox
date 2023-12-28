////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/vector/Tensor13.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Tensor13U(ZERO) == Tensor13U(ZERO)));
        expect( true == (Tensor13D(ZERO) == Tensor13D(ZERO)));
        expect( true == (Tensor13F(ZERO) == Tensor13F(ZERO)));
        expect( true == (all(Tensor13F(ZERO)) == 0.f));
    };
    
    "addition"_test = []{

        // Uniform
        expect(
            Tensor13I(
                1,1,1
            ) + Tensor13I(ALL,2) ==  Tensor13I(
                3,3,3
            )
        );
        
        //  XX
        expect(
            Tensor13I(
                2,1,1
            ) + Tensor13I(ALL,2) ==  Tensor13I(
                4,3,3
            )
        );

        //  XY
        expect(
            Tensor13I(
                1,2,1
            ) + Tensor13I(ALL,2) ==  Tensor13I(
                3,4,3
            )
        );

        //  XZ
        expect(
            Tensor13I(
                1,1,2
            ) + Tensor13I(ALL,2) ==  Tensor13I(
                3,3,4
            )
        );
    };

    "subtraction"_test = []{

        // Uniform
        expect(
            Tensor13I(
                +1,+1,+1
            ) - Tensor13I(ALL,2) ==  Tensor13I(
                -1,-1,-1
            )
        );

        // XX
        expect(
            Tensor13I(
                -1,+1,+1
            ) - Tensor13I(ALL,2) ==  Tensor13I(
                -3,-1,-1
            )
        );

        // XY
        expect(
            Tensor13I(
                +1,-1,+1
            ) - Tensor13I(ALL,2) ==  Tensor13I(
                -1,-3,-1
            )
        );

        // XZ
        expect(
            Tensor13I(
                +1,+1,-1
            ) - Tensor13I(ALL,2) ==  Tensor13I(
                -1,-1,-3
            )
        );
    };
    
    "Multiply-int"_test = []{
        // uniform
        expect(
            Tensor13I(
                1,1,1
            ) * 3 ==  Tensor13I(
                3,3,3
            )
        );
        
        // XX
        expect(
            Tensor13I(
                2,1,1
            ) * 3 ==  Tensor13I(
                6,3,3
            )
        );

        // XY
        expect(
            Tensor13I(
                1,2,1
            ) * 3 ==  Tensor13I(
                3,6,3
            )
        );

        // XZ
        expect(
            Tensor13I(
                1,1,2
            ) * 3 ==  Tensor13I(
                3,3,6
            )
        );
    };
    
    "Divide-int"_test = []{
        // uniform
        expect(
            Tensor13I(
                3,3,3
            ) / 3 ==  Tensor13I(
                1,1,1
            )
        );

        // XX
        expect(
            Tensor13I(
                6,3,3
            ) / 3 ==  Tensor13I(
                2,1,1
            )
        );

        // XY
        expect(
            Tensor13I(
                3,6,3
            ) / 3 ==  Tensor13I(
                1,2,1
            )
        );

        // XZ
        expect(
            Tensor13I(
                3,3,6
            ) / 3 ==  Tensor13I(
                1,1,2
            )
        );

    };
};

int main(){
    return ut::cfg<>.run();
};

