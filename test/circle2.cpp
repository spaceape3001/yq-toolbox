////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Circle2.hxx>
#include <math/vector/Vector2.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
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
    
    "contains"_test = []{
        Circle2D    u   = Circle2D(UNIT);
        Circle2D    u10 = 10. * u + Vector2D(X, 10.);
        
        
        expect(true == u10.contains({ 10., 0. }));
        expect(true == u10.contains({  5., 5. }));
        expect(false == u10.contains({ -10., 0. }));
    };
    
};

int main(){
    return ut::cfg<>.run();
};
