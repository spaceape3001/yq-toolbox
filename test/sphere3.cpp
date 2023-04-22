////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Sphere3.hxx>
#include <math/vector/Vector3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect(true == (Sphere3D(ZERO) == Sphere3D(ZERO)));
    };
    
    "valid"_test = []{
        expect(true == Sphere3D(Vector3D(ZERO), 1.).valid());
        expect(false == Sphere3D(Vector3D(ZERO), -1.).valid());
        expect(true == Sphere3D(Vector3D(10.,0., 0.), 1.).valid());
        expect(false == Sphere3D(Vector3D(10.,0, 0.), -1.).valid());
    };
    
    "add"_test = []{
        Sphere3I    a( ZERO, 1 );
        Vector3I    b(X);
        Sphere3I    c(Vector3I(1,0,0), 1 );
        
        expect(true == a.valid());
        expect(true == c.valid());
        
        Sphere3I    d   = a + b;
        expect(true == (d == c));
    };
    
    "contains"_test = []{
        Sphere3D    u   = Sphere3D(UNIT);
        Sphere3D    u10 = 10. * u + Vector3D(X, 10.);
        
        
        expect(true == u10.contains({ 10., 0., 0. }));
        expect(true == u10.contains({  5., 5., 0. }));
        expect(false == u10.contains({ -10., 0., 0. }));
    };
    
};

int main(){
    return ut::cfg<>.run();
};
