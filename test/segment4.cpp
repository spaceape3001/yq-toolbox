////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/utility.hpp>
#include <math/shape/Segment4.hpp>
#include <math/vector/Vector4.hpp>

#include <math/shape/Segment4.hxx>
#include <math/vector/Vector4.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Segment4D(ZERO) == Segment4D(ZERO) ));
    };

    "add"_test = []{
        Segment4I       a( Vector4I(ALL,-1), Vector4I(ALL,1));
        Vector4I        b(X);
        Segment4I       c( Vector4I(0,-1,-1,-1), Vector4I(2,1,1,1));
        Segment4I   d   = a + b;
        Segment4I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
    
    "length²"_test = []{
        Segment4I       a( Vector4I(ALL,-1), Vector4I(ALL,1));
        expect(16 == a.length²());
    };

};

int main(){
    return ut::cfg<>.run();
};
