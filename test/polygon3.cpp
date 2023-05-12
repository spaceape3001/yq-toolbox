////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Polygon3.hpp>
#include <math/vector/Vector3.hpp>

#include <math/shape/Polygon3.hxx>
#include <math/vector/Vector3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Polygon3D() == Polygon3D() ));
    };

    "add"_test = []{
        Polygon3I      a({ Vector3I(0, 0, 0), Vector3I(1,1,0), Vector3I(ONE) });
        Vector3I        b(X);
        Polygon3I      c({ Vector3I(1, 0, 0), Vector3I(2,1,0), Vector3I(2,1,1) });
        Polygon3I   d   = a + b;
        Polygon3I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
};

int main(){
    return ut::cfg<>.run();
};
