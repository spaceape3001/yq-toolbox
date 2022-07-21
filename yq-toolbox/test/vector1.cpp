////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Vector1.hpp>
#include <math/vector_math.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

ut::suite tests = []{
    "add 1D int"_test = [](){
        expect( Vector1I{1}+Vector1I{1} == Vector1I{2});
        expect( Vector1I{1}+Vector1I(3) == Vector1I(4));
        expect( Vector1I(1)+Vector1I(2) == Vector1I(3));
        expect( Vector1I(2)+Vector1I(5) == Vector1I(7));
        expect( Vector1I(2)+Vector1I(2) == Vector1I(4));
    };
    
    "subtract 1D int"_test = [](){
        expect( Vector1I(5)-Vector1I(1) == Vector1I(4));
        expect( Vector1I(5)-Vector1I(2) == Vector1I(3));
        expect( Vector1I(5)-Vector1I(3) == Vector1I(2));
    };
    
    "multiply 1D unsigned"_test = [](){
        expect( Vector1U(1)*5 == Vector1U(5) );
        expect( Vector1U(3)*5 == Vector1U(15) );
        expect( Vector1U(4)*5 == Vector1U(20) );
        expect( 5*Vector1U(1) == Vector1U(5) );
        expect( 5*Vector1U(3) == Vector1U(15) );
        expect( 5*Vector1U(4) == Vector1U(20) );
    };
};

int main(){
    return ut::cfg<>.run();
};

