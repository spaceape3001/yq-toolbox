////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/basic/Coord4.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

ut::suite tests = []{
    "zero is zero"_test = []{
        expect(true == (Coord4I(ZERO) == Coord4I(ZERO)));
    };
    "add"_test = []{
        Coord4I a(ALL, 1);
        Coord4I b(1,2,3,4);
        Coord4I c   = a + b;
        Coord4I d   = b + a;
        
        expect(true == (c == d));
        expect(true == (c == Coord4I(2,3,4,5)));
    };
};

int main(){
    return ut::cfg<>.run();
};
