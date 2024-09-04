////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/math/utility.hpp>
#include <0/math/shape/Triangle4.hpp>
#include <0/math/vector/Vector4.hpp>
#include <0/math/shape/AxBox4.hpp>

#include <0/math/shape/Triangle4.hxx>
#include <0/math/vector/Vector4.hxx>
#include <0/math/shape/AxBox4.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    Absolute tol{1e-12};

    "zero is zero"_test = []{
        expect( true == (Triangle4D(ZERO) == Triangle4D(ZERO) ));
    };

    "add"_test = []{
        Triangle4I      a( Vector4I(0, 0, 0, 0), Vector4I(1, 1, 0, 0), Vector4I(ONE));
        Vector4I        b(X);
        Triangle4I      c( Vector4I(1, 0, 0, 0), Vector4I(2,1,0,0), Vector4I(2,1,1,1));
        Triangle4I   d   = a + b;
        Triangle4I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
    
    "area"_test = [&]{
        Triangle4D      a( Vector4D(ZERO), Vector4D(3,4,0,0), Vector4D(3,4,0,5));
        expect(is_close(tol, a.area(), 12.5));
    };

    "bounds"_test = []{
        Triangle4I      triA( Vector4I(ZERO), Vector4I(3,4,-2,0), Vector4I(3,4,5,5));
        AxBox4I         bndA0(Vector4I(0,0,-2, 0),Vector4I(3,4,5,5));
        AxBox4I         bndA1   = triA.bounds();
        
        Triangle4I      triB(Vector4I(ZERO), Vector4I(12,0,3,6), Vector4I(12,5,-2,8));
        AxBox4I         bndB0(Vector4I(0,0,-2,0),Vector4I(12,5,3,8));
        AxBox4I         bndB1 = triB.bounds();
        
        expect( true == (bndA0 == bndA1));
        expect( true == (bndB0 == bndB1));

        expect( false == (bndA1 == bndB1));
        expect( true  == (bndA1 != bndB1));
    };

    "edge length²"_test = []{
        Triangle4I      tri( Vector4I(ZERO), Vector4I(3,4,0,0), Vector4I(3,4,5,0));
        expect( 25 == tri.edge_a_length²());
        expect( 50 == tri.edge_b_length²());
        expect( 25 == tri.edge_c_length²());
    };
    
    "perimeter"_test = [&]{
        Triangle4D      tri( Vector4D(ZERO), Vector4D(3,4,0,0), Vector4D(3,4,5,0));
        expect(is_close(tol, tri.perimeter(), 17.07106781186548));
    };

    return ut::cfg<>.run();
};
