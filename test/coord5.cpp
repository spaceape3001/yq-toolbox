////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/basic/Coord5.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    "zero is zero"_test = []{
        expect(true == (Coord5I(ZERO) == Coord5I(ZERO)));
    };
    "add"_test = []{
        Coord5I a(ALL, 1);
        Coord5I b(1,2,3,4,5);
        Coord5I c   = a + b;
        Coord5I d   = b + a;
        
        expect(true == (c == d));
        expect(true == (c == Coord5I(2,3,4,5,6)));
    };

    return ut::cfg<>.run();
};
