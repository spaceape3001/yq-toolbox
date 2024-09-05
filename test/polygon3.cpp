////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq-toolbox/math/tolerance/Absolute.hpp>
#include <yq-toolbox/math/utility.hpp>
#include <yq-toolbox/shape/Polygon3.hpp>
#include <yq-toolbox/vector/Vector3.hpp>

#include <yq-toolbox/shape/Polygon3.hxx>
#include <yq-toolbox/vector/Vector3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    //Absolute tol{1e-12};

    "zero is zero"_test = []{
        expect( true == (Polygon3D() == Polygon3D() ));
    };

    "add"_test = []{
        Polygon3I      a({ Vector3I(0, 0, 0), Vector3I(1,1,0), Vector3I(ONE) });
        Vector3I        b(X);
        Polygon3I      c({ Vector3I(1, 0, 0), Vector3I(2,1,0), Vector3I(2,1,1) });
        Polygon3I   d   = a + b;
        Polygon3I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };

    return ut::cfg<>.run();
};
