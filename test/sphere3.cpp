////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/math/utility.hpp>

#include <yq/shape/AxBox3.hpp>
#include <yq/shape/Sphere3.hpp>
#include <yq/vector/Vector3.hpp>

#include <yq/shape/AxBox3.hxx>
#include <yq/shape/Sphere3.hxx>
#include <yq/vector/Vector3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    Absolute tol{1e-12};

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
    
    
    "bounds"_test = []{
        Sphere3I    sphA(Vector3I(5,6,7),2);

        AxBox3I     bndA0(Vector3I(3,4,5),Vector3I(7,8,9));
        AxBox3I     bndA1   = sphA.bounds();

        Sphere3I    sphB(Vector3I(3,-4, 5), 5);
        AxBox3I     bndB0(Vector3I(-2,-9,0),Vector3I(8,1,10));
        AxBox3I     bndB1   = sphB.bounds();

        expect( true == (bndA0 == bndA1));
        expect( true == (bndB0 == bndB1));

        expect( false == (bndA1 == bndB1));
        expect( true  == (bndA1 != bndB1));
    };
    
    "contains"_test = []{
        Sphere3D    u   = Sphere3D(UNIT);
        Sphere3D    u10 = 10. * u + Vector3D(X, 10.);
        
        
        expect(true == u10.contains({ 10., 0., 0. }));
        expect(true == u10.contains({  5., 5., 0. }));
        expect(false == u10.contains({ -10., 0., 0. }));
    };
    
    "surface_area"_test = [&]{
        Sphere3D    sph(Vector3D(4,2,3),10.);
        expect( true == is_close(tol, sph.surface_area(), 1256.637061435917 ));
    };
    
    "volume"_test = [&]{
        Sphere3D    sph(Vector3D(4,2,3),10.);
        expect( true == is_close(tol, sph.volume(), 4188.790204786391));
    };

    return ut::cfg<>.run();
};
