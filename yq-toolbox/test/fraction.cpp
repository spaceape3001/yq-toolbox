////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Fraction.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

ut::suite tests = []{
    "add"_test = []{
        expect(FractionI(1,2) + FractionI(1,2) == FractionI(1,1));
        expect(FractionI(1,2) + FractionI(1,4) == FractionI(3,4));
        expect(FractionI(1,3) + FractionI(1,2) == FractionI(5,6));
    };
    
    "subtract"_test = []{
        expect(FractionI(1,2)-FractionI(1,2) == FractionI(0,1));
        expect(FractionI(1,2)-FractionI(1,4) == FractionI(1,4));
        expect(FractionI(1,4)-FractionI(1,2) == FractionI(-1,4));
    };
    
    "multiply"_test = []{
        expect(FractionI(1,2) * FractionI(1,2) == FractionI(1,4));
        expect(FractionI(1,2) * FractionI(1,3) == FractionI(1,6));
    };
    
    "divide"_test = []{
        expect(FractionI(1,2) / FractionI(1,2) == FractionI(1,1));
        expect(FractionI(1,2) / FractionI(1,3) == FractionI(3,2));
    };
};


int main(){
    return ut::cfg<>.run();
}
