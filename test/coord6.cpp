////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <basic/Coord6.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

ut::suite tests = []{
    "zero is zero"_test = []{
        expect(true == (Coord6I(ZERO) == Coord6I(ZERO)));
    };
    "add"_test = []{
        Coord6I a(ALL, 1);
        Coord6I b(1,2,3,4,5,6);
        Coord6I c   = a + b;
        Coord6I d   = b + a;
        
        expect(true == (c == d));
        expect(true == (c == Coord6I(2,3,4,5,6,7)));
    };
};

int main(){
    return ut::cfg<>.run();
};
