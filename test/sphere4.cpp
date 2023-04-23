////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Sphere4.hxx>
#include <math/vector/Vector4.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect(true == (Sphere4D(ZERO) == Sphere4D(ZERO)));
    };
    
    "valid"_test = []{
        expect(true == Sphere4D(Vector4D(ZERO), 1.).valid());
        expect(false == Sphere4D(Vector4D(ZERO), -1.).valid());
        expect(true == Sphere4D(Vector4D(X, 10.), 1.).valid());
        expect(false == Sphere4D(Vector4D(X, 10.), -1.).valid());
    };
    
    "add"_test = []{
        Sphere4I    a( ZERO, 1 );
        Vector4I    b(X);
        Sphere4I    c(Vector4I(X), 1 );
        
        expect(true == a.valid());
        expect(true == c.valid());
        
        Sphere4I    d   = a + b;
        expect(true == (d == c));
    };
    
    "contains"_test = []{
        Sphere4D    u   = Sphere4D(UNIT);
        Sphere4D    u10 = 10. * u + Vector4D(X, 10.);
        
        
        expect(true == u10.contains({ 10., 0., 0., 0. }));
        expect(true == u10.contains({  5., 5., 0., 0. }));
        expect(false == u10.contains({ -10., 0., 0., 0. }));
    };
    
};

int main(){
    return ut::cfg<>.run();
};
