////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/basic/Coord2.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

ut::suite tests = []{
    "zero is zero"_test = []{
        expect(true == (Coord2I(ZERO) == Coord2I(ZERO)));
    };
    "add"_test = []{
        Coord2I a(ALL, 1);
        Coord2I b(1,2);
        Coord2I c   = a + b;
        Coord2I d   = b + a;
        
        expect(true == (c == d));
        expect(true == (c == Coord2I(2,3)));
    };
};

int main(){
    return ut::cfg<>.run();
};
