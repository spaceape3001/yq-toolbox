////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/Absolute.hpp>
#include <0/math/utility.hpp>
#include <0/math/shape/Segment4.hpp>
#include <0/math/vector/Vector4.hpp>

#include <0/math/shape/Segment4.hxx>
#include <0/math/vector/Vector4.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    //Absolute tol{1e-12};

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

    return ut::cfg<>.run();
};
