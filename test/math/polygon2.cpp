////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/math/utility.hpp>
#include <yq/shape/Polygon2.hpp>
#include <yq/vector/Vector2.hpp>

#include <yq/shape/Polygon2.hxx>
#include <yq/vector/Vector2.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    //Absolute tol{1e-12};

    "zero is zero"_test = []{
        expect( true == (Polygon2D() == Polygon2D() ));
    };

    "add"_test = []{
        Polygon2I      a({ Vector2I(0, 0), Vector2I(1,0), Vector2I(ONE) });
        Vector2I        b(X);
        Polygon2I      c({ Vector2I(1, 0), Vector2I(2,0), Vector2I(2,1) });
        Polygon2I   d  = a + b;
        Polygon2I   e  = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
        expect(true == (e == d));
    };

    return ut::cfg<>.run();
};
