////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Triangle2.hpp>
#include <math/vector/Vector2.hpp>

#include <math/shape/Triangle2.hxx>
#include <math/vector/Vector2.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Triangle2D(ZERO) == Triangle2D(ZERO) ));
    };

    "add"_test = []{
        Triangle2I      a( Vector2I(0, 0), Vector2I(1, 1), Vector2I(ONE));
        Vector2I        b(X);
        Triangle2I      c( Vector2I(1, 0), Vector2I(2,1), Vector2I(2,1));
        Triangle2I   d   = a + b;
        Triangle2I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
    
    "area"_test = []{
        Triangle2D      a( Vector2D(ZERO), Vector2D(0,5), Vector2D(5,5));
        expect(is_close(tol, a.area(), 12.5));
    };

};

int main(){
    return ut::cfg<>.run();
};
