////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/shape/Segment2.hpp>
#include <0/math/vector/Vector2.hpp>

#include <0/math/shape/Segment2.hxx>
#include <0/math/vector/Vector2.hxx>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Segment2D(ZERO) == Segment2D(ZERO) ));
    };

    "add"_test = []{
        Segment2I       a( Vector2I(ALL,-1), Vector2I(ALL,1));
        Vector2I        b(X);
        Segment2I       c( Vector2I(0,-1), Vector2I(2,1));
        Segment2I   d   = a + b;
        Segment2I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
    
    "length²"_test = []{
        Segment2I       a( Vector2I(ALL,-1), Vector2I(ALL,1));
        expect(8 == a.length²());
    };

};

int main(){
    return ut::cfg<>.run();
};
