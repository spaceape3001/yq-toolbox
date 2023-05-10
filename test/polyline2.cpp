////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Polyline2.hpp>
#include <math/vector/Vector2.hpp>

#include <math/shape/Polyline2.hxx>
#include <math/vector/Vector2.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Polyline2D() == Polyline2D() ));
    };

    "add"_test = []{
        Polyline2I      a({ Vector2I(0, 0), Vector2I(1,1), Vector2I(ONE) });
        Vector2I        b(X);
        Polyline2I      c({ Vector2I(1, 0), Vector2I(2,1), Vector2I(2,1) });
        Polyline2I   d   = a + b;
        Polyline2I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
};

int main(){
    return ut::cfg<>.run();
};
