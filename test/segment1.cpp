////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/shape/Segment1.hpp>
#include <0/math/vector/Vector1.hpp>

#include <0/math/shape/Segment1.hxx>
#include <0/math/vector/Vector1.hxx>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Segment1D(ZERO) == Segment1D(ZERO) ));
    };

    "add"_test = []{
        Segment1I       a( Vector1I(ALL,-1), Vector1I(ALL,1));
        Vector1I        b(X);
        Segment1I       c( Vector1I(0), Vector1I(2));
        Segment1I   d   = a + b;
        Segment1I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };
    
    "length²"_test = []{
        Segment1I       a( Vector1I(ALL,-1), Vector1I(ALL,1));
        expect(4 == a.length²());
    };

};

int main(){
    return ut::cfg<>.run();
};
