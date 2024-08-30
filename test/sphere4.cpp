////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/shape/Sphere4.hxx>
#include <0/math/vector/Vector4.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    Absolute tol{1e-12};

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

    "bounds"_test = []{
        Sphere4I    sphA(Vector4I(5,6,7,8),2);

        AxBox4I     bndA0(Vector4I(3,4,5,6),Vector4I(7,8,9,10));
        AxBox4I     bndA1   = sphA.bounds();

        Sphere4I    sphB(Vector4I(3,-4, 5,-6), 5);
        AxBox4I     bndB0(Vector4I(-2,-9,0,-11),Vector4I(8,1,10,-1));
        AxBox4I     bndB1   = sphB.bounds();

        expect( true == (bndA0 == bndA1));
        expect( true == (bndB0 == bndB1));

        expect( false == (bndA1 == bndB1));
        expect( true  == (bndA1 != bndB1));
    };
    
    "contains"_test = []{
        Sphere4D    u   = Sphere4D(UNIT);
        Sphere4D    u10 = 10. * u + Vector4D(X, 10.);
        
        expect(true == u10.contains({ 10., 0., 0., 0. }));
        expect(true == u10.contains({  5., 5., 0., 0. }));
        expect(false == u10.contains({ -10., 0., 0., 0. }));
    };
    
    "hypervolume"_test = [&]{
        Sphere4D    sph(Vector4D(4,2,3,5),10.);
        expect( true == is_close(tol, sph.hypervolume(), 49348.02200544679));
    };

    return ut::cfg<>.run();
};
