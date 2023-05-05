////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Triangle3.hpp>
#include <math/vector/Vector3.hpp>

#include <math/shape/Triangle3.hxx>
#include <math/vector/Vector3.hxx>

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
        Triangle3D      a( Vector3D(ZERO), Vector3D(3,3,0), Vector3D(3,3,5));
        expect(is_close(tol, a.area(), 12.5));
    };

};

int main(){
    return ut::cfg<>.run();
};
