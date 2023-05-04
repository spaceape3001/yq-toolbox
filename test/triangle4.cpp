////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Triangle4.hpp>
#include <math/vector/Vector4.hpp>

#include <math/shape/Triangle4.hxx>
#include <math/vector/Vector4.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Triangle4D(ZERO) == Triangle4D(ZERO) ));
    };

    "add"_test = []{
        Triangle4I      a( Vector4I(0, 0, 0, 0), Vector4I(1, 1, 0, 0), Vector4I(ONE));
        Vector4I        b(X);
        Triangle4I      c( Vector4I(1, 0, 0, 0), Vector4I(2,1,0,0), Vector4I(2,1,1,1));
        Triangle4I   d   = a + b;
        Triangle4I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
    
    "area"_test = []{
        Triangle4D      a( Vector4D(ZERO), Vector4D(3,4,0,0), Vector4D(3,4,0,5));
        expect(is_close(tol, a.area(), 12.5));
    };

};

int main(){
    return ut::cfg<>.run();
};
