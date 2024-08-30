////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>

#include <0/math/shape/AxBox2.hpp>
#include <0/math/shape/Circle2.hpp>
#include <0/math/vector/Vector2.hpp>

#include <0/math/shape/AxBox2.hxx>
#include <0/math/shape/Circle2.hxx>
#include <0/math/vector/Vector2.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    Absolute tol{1e-12};

    "zero is zero"_test = []{
        expect(true == (Circle2D(ZERO) == Circle2D(ZERO)));
    };
    
    "valid"_test = []{
        expect(true == Circle2D(Vector2D(ZERO), 1.).valid());
        expect(false == Circle2D(Vector2D(ZERO), -1.).valid());
        expect(true == Circle2D(Vector2D(10.,0), 1.).valid());
        expect(false == Circle2D(Vector2D(10.,0), -1.).valid());
    };
    
    "add"_test = []{
        Circle2I    a( ZERO, 1 );
        Vector2I    b(X);
        Circle2I    c(Vector2I(1,0), 1 );
        
        expect(true == a.valid());
        expect(true == c.valid());
        
        Circle2I    d   = a + b;
        expect(true == (d == c));
    };
    
    "area"_test = [&]{
        Circle2D    cirA(Vector2D(4,2),10.);
        expect( true == is_close(tol, cirA.area(), 314.1592653589793 ));
    };
    
    "bounds"_test = []{
        Circle2I    cirA(Vector2I(5,6),2);

        AxBox2I     bndA0(Vector2I(3,4),Vector2I(7,8));
        AxBox2I     bndA1   = cirA.bounds();

        Circle2I    cirB(Vector2I(3,-4), 5);
        AxBox2I     bndB0(Vector2I(-2,-9),Vector2I(8,1));
        AxBox2I     bndB1   = cirB.bounds();

        expect( true == (bndA0 == bndA1));
        expect( true == (bndB0 == bndB1));

        expect( false == (bndA1 == bndB1));
        expect( true  == (bndA1 != bndB1));
    };
    
    "circumference"_test = [&]{
        Circle2D    cirA(Vector2D(4,2),10.);
        expect( true == is_close(tol, cirA.circumference(), 62.83185307179586 ));
    };
    
    "contains"_test = []{
        Circle2D    u   = Circle2D(UNIT);
        Circle2D    u10 = 10. * u + Vector2D(X, 10.);
        
        expect(true == u10.contains({ 10., 0. }));
        expect(true == u10.contains({  5., 5. }));
        expect(false == u10.contains({ -10., 0. }));
    };
    

    return ut::cfg<>.run();
};
