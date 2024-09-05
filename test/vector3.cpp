////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq-toolbox/vector/Vector3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    "add 3D int"_test = [](){
        expect( Vector3I{1,1,1}+Vector3I{2,2,2} == Vector3I{3,3,3});
        expect( Vector3I{1,2,1}+Vector3I(2,2,2) == Vector3I(3,4,3));
        expect( Vector3I(1,1,2)+Vector3I(1,2,2) == Vector3I(2,3,4));
        expect( Vector3I(2,1,2)+Vector3I(2,2,1) == Vector3I(4,3,3));
        expect( Vector3I(2,2,2)+Vector3I(2,2,1) == Vector3I(4,4,3));
    };
    
    "subtract 3D int"_test = [](){
        expect( Vector3I(5,5,5)-Vector3I(1,1,1) == Vector3I(4,4,4));
        expect( Vector3I(5,5,5)-Vector3I(2,3,1) == Vector3I(3,2,4));
        expect( Vector3I(5,5,5)-Vector3I(3,2,1) == Vector3I(2,3,4));
    };
    
    "multiply 3D unsigned"_test = [](){
        expect( Vector3U(1,1,1)*5 == Vector3U(5,5,5) );
        expect( Vector3U(1,3,2)*5 == Vector3U(5,15,10) );
        expect( Vector3U(3,1,2)*5 == Vector3U(15,5,10) );
        expect( 5*Vector3U(1,1,1) == Vector3U(5,5,5) );
        expect( 5*Vector3U(1,3,2) == Vector3U(5,15,10) );
        expect( 5*Vector3U(3,1,2) == Vector3U(15,5,10) );
    };

    "comparison"_test = [](){
        Vector3D    v{1.,2., 3.};
        
        expect( true == ( any(v) < 1.5 ) );
        expect( false == ( any(v) < 0.5 ) );
        expect( true == ( all(v) < 3.5) );
        expect( false  == ( all(v) < 2.5) );
    };

    return ut::cfg<>.run();
};

