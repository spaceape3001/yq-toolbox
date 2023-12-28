////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/basic/Coord1.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

ut::suite tests = []{
    "zero is zero"_test = []{
        expect(true == (Coord1I(ZERO) == Coord1I(ZERO)));
    };
    "add"_test = []{
        Coord1I a(ALL, 1);
        Coord1I b(1);
        Coord1I c   = a + b;
        Coord1I d   = b + a;
        
        expect(true == (c == d));
        expect(true == (c == Coord1I(2)));
    };
};

int main(){
    return ut::cfg<>.run();
};
