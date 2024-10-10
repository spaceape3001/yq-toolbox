////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/math/utility.hpp>
#include <yq/shape/AxBox2.hpp>
#include <yq/shape/Triangle2.hpp>
#include <yq/vector/Vector2.hpp>

#include <yq/shape/AxBox2.hxx>
#include <yq/shape/Triangle2.hxx>
#include <yq/vector/Vector2.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    Absolute tol{1e-12};

    "zero is zero"_test = []{
        expect( true == (Triangle2D(ZERO) == Triangle2D(ZERO) ));
    };

    "add"_test = []{
        Triangle2I      a( Vector2I(0, 0), Vector2I(1, 1), Vector2I(ONE)); 
        Vector2I        b(X);
        Triangle2I      c( Vector2I(1, 0), Vector2I(2,1), Vector2I(2,1));
        Triangle2I   d   = a + b;
        Triangle2I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
    
    "area"_test = [&]{
        Triangle2D      a( Vector2D(ZERO), Vector2D(0,5), Vector2D(5,5));
        expect(is_close(tol, a.area(), 12.5));
    };
    
    "bounds"_test = []{
        Triangle2I      triA(Vector2I(ZERO), Vector2I(0,5), Vector2I(5,0));
        AxBox2I         bndA0(Vector2I(0,0),Vector2I(5,5));
        AxBox2I         bndA1   = triA.bounds();
        
        Triangle2I      triB(Vector2I(ZERO), Vector2I(12,0), Vector2I(12,5));
        AxBox2I         bndB0(Vector2I(0,0),Vector2I(12,5));
        AxBox2I         bndB1 = triB.bounds();
        
        expect( true == (bndA0 == bndA1));
        expect( true == (bndB0 == bndB1));

        expect( false == (bndA1 == bndB1));
        expect( true  == (bndA1 != bndB1));
    };

    "clockwise"_test = []{
        Triangle2I      triA(Vector2I(ZERO), Vector2I(0,5), Vector2I(5,0));
        Triangle2I      triB(Vector2I(ZERO), Vector2I(12,0), Vector2I(12,5));
        
        expect(true == triA.is_clockwise());
        expect(false == triA.is_ccw());
        expect(false == triB.is_clockwise());
        expect(true  == triB.is_ccw());
    };
    
    "edge length²"_test = []{
        Triangle2I      triA(Vector2I(ZERO), Vector2I(0,5), Vector2I(5,0));
        Triangle2I      triB(Vector2I(ZERO), Vector2I(12,0), Vector2I(12,5));
        
        
        expect(50 == triA.edge_a_length²());
        expect(25 == triA.edge_b_length²());
        expect(25 == triA.edge_c_length²());
    
        expect(25  == triB.edge_a_length²());
        expect(169 == triB.edge_b_length²());
        expect(144 == triB.edge_c_length²());
    };
    
    "perimeter"_test = [&]{
        Triangle2D      triB(Vector2D(ZERO), Vector2D(12,0), Vector2D(12,5));
        expect(true == is_close(tol, triB.perimeter(), 30.));
    };

    return ut::cfg<>.run();
};
