////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Vector2.hpp>
#include <math/vector_math.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

ut::suite tests = []{
    "add 2D int"_test = [](){
        expect( Vector2I{1,1}+Vector2I{2,2} == Vector2I{3,3});
        expect( Vector2I{1,2}+Vector2I(2,2) == Vector2I(3,4));
        expect( Vector2I(1,1)+Vector2I(1,2) == Vector2I(2,3));
        expect( Vector2I(2,1)+Vector2I(2,2) == Vector2I(4,3));
        expect( Vector2I(2,2)+Vector2I(2,2) == Vector2I(4,4));
    };
    
    "subtract 2D int"_test = [](){
        expect( Vector2I(5,5)-Vector2I(1,1) == Vector2I(4,4));
        expect( Vector2I(5,5)-Vector2I(2,3) == Vector2I(3,2));
        expect( Vector2I(5,5)-Vector2I(3,2) == Vector2I(2,3));
    };
    
    "multiply 2D unsigned"_test = [](){
        expect( Vector2U(1,1)*5 == Vector2U(5,5) );
        expect( Vector2U(1,3)*5 == Vector2U(5,15) );
        expect( Vector2U(3,1)*5 == Vector2U(15,5) );
        expect( 5*Vector2U(1,1) == Vector2U(5,5) );
        expect( 5*Vector2U(1,3) == Vector2U(5,15) );
        expect( 5*Vector2U(3,1) == Vector2U(15,5) );
    };
};

int main(){
    return ut::cfg<>.run();
};

