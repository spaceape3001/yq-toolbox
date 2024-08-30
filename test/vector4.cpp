////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/vector/Vector4.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    "add 3D int"_test = [](){
        expect( Vector4I{1,1,1,1}+Vector4I{2,2,2,2} == Vector4I{3,3,3,3});
        expect( Vector4I{1,2,1,2}+Vector4I(2,2,2,2) == Vector4I(3,4,3,4));
        expect( Vector4I(1,1,2,3)+Vector4I(1,2,2,1) == Vector4I(2,3,4,4));
        expect( Vector4I(2,1,2,3)+Vector4I(2,2,1,1) == Vector4I(4,3,3,4));
        expect( Vector4I(2,2,2,3)+Vector4I(2,2,1,1) == Vector4I(4,4,3,4));
    };
    
    "subtract 3D int"_test = [](){
        expect( Vector4I(5,5,5,5)-Vector4I(1,1,1,1) == Vector4I(4,4,4,4));
        expect( Vector4I(5,5,5,5)-Vector4I(2,3,1,1) == Vector4I(3,2,4,4));
        expect( Vector4I(5,5,5,5)-Vector4I(3,2,1,1) == Vector4I(2,3,4,4));
        expect( Vector4I(5,5,5,5)-Vector4I(3,2,2,1) == Vector4I(2,3,3,4));
    };
    
    "multiply 3D unsigned"_test = [](){
        expect( Vector4U(1,1,1,1)*5 == Vector4U(5,5,5,5) );
        expect( Vector4U(1,3,2,3)*5 == Vector4U(5,15,10,15) );
        expect( Vector4U(3,1,2,2)*5 == Vector4U(15,5,10,10) );
        expect( 5*Vector4U(1,1,1,1) == Vector4U(5,5,5,5) );
        expect( 5*Vector4U(1,3,2,3) == Vector4U(5,15,10,15) );
        expect( 5*Vector4U(3,1,2,2) == Vector4U(15,5,10,10) );
    };

    "comparison"_test = [](){
        Vector4D    v{1.,2., 3.,4.};
        
        expect( true == ( any(v) < 1.5 ) );
        expect( false == ( any(v) < 0.5 ) );
        expect( true == ( all(v) < 4.5) );
        expect( false  == ( all(v) < 2.5) );
    };

    return ut::cfg<>.run();
};

