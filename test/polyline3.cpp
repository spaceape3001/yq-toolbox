////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Polyline3.hpp>
#include <math/vector/Vector3.hpp>

#include <math/shape/Polyline3.hxx>
#include <math/vector/Vector3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Polyline3D() == Polyline3D() ));
    };

    "add"_test = []{
        Polyline3I      a({ Vector3I(0, 0, 0), Vector3I(1,1,0), Vector3I(ONE) });
        Vector3I        b(X);
        Polyline3I      c({ Vector3I(1, 0, 0), Vector3I(2,1,0), Vector3I(2,1,1) });
        Polyline3I   d   = a + b;
        Polyline3I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
};

int main(){
    return ut::cfg<>.run();
};
