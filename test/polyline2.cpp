////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/math/utility.hpp>
#include <0/math/shape/Polyline2.hpp>
#include <0/math/vector/Vector2.hpp>

#include <0/math/shape/Polyline2.hxx>
#include <0/math/vector/Vector2.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    //Absolute tol{1e-12};

    "zero is zero"_test = []{
        expect( true == (Polyline2D() == Polyline2D() ));
    };

    "add"_test = []{
        Polyline2I      a({ Vector2I(0, 0), Vector2I(1,0), Vector2I(ONE) });
        Vector2I        b(X);
        Polyline2I      c({ Vector2I(1, 0), Vector2I(2,0), Vector2I(2,1) });
        Polyline2I   d  = a + b;
        Polyline2I   e  = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
        expect(true == (e == d));
    };

    return ut::cfg<>.run();
};
