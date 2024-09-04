////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/math/utility.hpp>
#include <0/math/shape/Polyline4.hpp>
#include <0/math/vector/Vector4.hpp>

#include <0/math/shape/Polyline4.hxx>
#include <0/math/vector/Vector4.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    //Absolute tol{1e-12};

    "zero is zero"_test = []{
        expect( true == (Polyline4D() == Polyline4D() ));
    };

    "add"_test = []{
        Polyline4I      a({ Vector4I(0, 0, 0, 0), Vector4I(1, 1, 0, 0), Vector4I(ONE) });
        Vector4I        b(X);
        Polyline4I      c({ Vector4I(1, 0, 0, 0), Vector4I(2,1,0,0), Vector4I(2,1,1,1) });
        Polyline4I   d   = a + b;
        Polyline4I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };

    return ut::cfg<>.run();
};
