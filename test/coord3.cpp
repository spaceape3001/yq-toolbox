////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/basic/Coord3.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    "zero is zero"_test = []{
        expect(true == (Coord3I(ZERO) == Coord3I(ZERO)));
    };
    "add"_test = []{
        Coord3I a(ALL, 1);
        Coord3I b(1,2,3);
        Coord3I c   = a + b;
        Coord3I d   = b + a;
        
        expect(true == (c == d));
        expect(true == (c == Coord3I(2,3,4)));
    };

    return ut::cfg<>.run();
};
