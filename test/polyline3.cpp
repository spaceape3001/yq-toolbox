////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq-toolbox/math/tolerance/Absolute.hpp>
#include <yq-toolbox/math/utility.hpp>
#include <yq-toolbox/shape/Polyline3.hpp>
#include <yq-toolbox/vector/Vector3.hpp>

#include <yq-toolbox/shape/Polyline3.hxx>
#include <yq-toolbox/vector/Vector3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    //Absolute tol{1e-12};
    
    "zero is zero"_test = []{
        expect( true == (Polyline3D() == Polyline3D() ));
    };

    "add"_test = []{
        Polyline3I      a({ Vector3I(0, 0, 0), Vector3I(1,1,0), Vector3I(ONE) });
        Vector3I        b(X);
        Polyline3I      c({ Vector3I(1, 0, 0), Vector3I(2,1,0), Vector3I(2,1,1) });
        Polyline3I   d   = a + b;
        Polyline3I   e = b + a;
        expect(true == (d == c));
        expect(true == (e == c));
    };

    return ut::cfg<>.run();
};
