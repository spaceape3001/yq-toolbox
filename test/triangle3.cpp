////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/shape/AxBox3.hpp>
#include <0/math/shape/Triangle3.hpp>
#include <0/math/vector/Vector3.hpp>

#include <0/math/shape/AxBox3.hxx>
#include <0/math/shape/Triangle3.hxx>
#include <0/math/vector/Vector3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Triangle3D(ZERO) == Triangle3D(ZERO) ));
    };

    "add"_test = []{
        Triangle3I      a( Vector3I(0, 0, 0), Vector3I(1, 1, 0), Vector3I(ONE));
        Vector3I        b(X);
        Triangle3I      c( Vector3I(1, 0, 0), Vector3I(2,1,0), Vector3I(2,1,1));
        Triangle3I   d   = a + b;
        Triangle3I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
    
    "area"_test = []{
        Triangle3D      a( Vector3D(ZERO), Vector3D(3,4,0), Vector3D(3,4,5));
        expect(is_close(tol, a.area(), 12.5));
    };

    "bounds"_test = []{
        Triangle3I      triA(Vector3I(ZERO), Vector3I(0,0,5), Vector3I(5,5,0));
        AxBox3I         bndA0(Vector3I(0,0,0),Vector3I(5,5,5));
        AxBox3I         bndA1   = triA.bounds();
        
        Triangle3I      triB(Vector3I(ZERO), Vector3I(12,0,3), Vector3I(12,5,-2));
        AxBox3I         bndB0(Vector3I(0,0,-2),Vector3I(12,5,3));
        AxBox3I         bndB1 = triB.bounds();
        
        expect( true == (bndA0 == bndA1));
        expect( true == (bndB0 == bndB1));

        expect( false == (bndA1 == bndB1));
        expect( true  == (bndA1 != bndB1));
    };

    "edge length²"_test = []{
        Triangle3I      tri( Vector3I(ZERO), Vector3I(3,4,0), Vector3I(3,4,5));
        expect( 25 == tri.edge_a_length²());
        expect( 50 == tri.edge_b_length²());
        expect( 25 == tri.edge_c_length²());
    };
    
    "perimeter"_test = []{
        Triangle3D      tri( Vector3D(ZERO), Vector3D(3,4,0), Vector3D(3,4,5));
        expect(is_close(tol, tri.perimeter(), 17.07106781186548));
    };

};

int main(){
    return ut::cfg<>.run();
};
