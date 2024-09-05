////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq-toolbox/math/tolerance/Absolute.hpp>
#include <yq-toolbox/math/utility.hpp>
#include <yq-toolbox/shape/Segment3.hpp>
#include <yq-toolbox/vector/Vector3.hpp>

#include <yq-toolbox/shape/Segment3.hxx>
#include <yq-toolbox/vector/Vector3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    //Absolute tol{1e-12};

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

    return ut::cfg<>.run();
};
