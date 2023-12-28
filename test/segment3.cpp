////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/shape/Segment3.hpp>
#include <0/math/vector/Vector3.hpp>

#include <0/math/shape/Segment3.hxx>
#include <0/math/vector/Vector3.hxx>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Segment3D(ZERO) == Segment3D(ZERO) ));
    };

    "add"_test = []{
        Segment3I       a( Vector3I(ALL,-1), Vector3I(ALL,1));
        Vector3I        b(X);
        Segment3I       c( Vector3I(0,-1,-1), Vector3I(2,1,1));
        Segment3I   d   = a + b;
        Segment3I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
    
    "length²"_test = []{
        Segment3I       a( Vector3I(ALL,-1), Vector3I(ALL,1));
        expect(12 == a.length²());
    };

};

int main(){
    return ut::cfg<>.run();
};
