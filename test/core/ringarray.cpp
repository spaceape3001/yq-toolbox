////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/container/RingArray.hpp>
#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    using ring2  = RingArray<int,2>;
    //using ring5  = RingArray<int,5>;
    //using ring20 = RingArray<int,20>;
    
    "1 in ring2"_test = []{
        ring2   ring({ 3 });
        expect(ring.empty() == false);
        expect(ring.size() == 1);
        expect(ring.full() == false);
        expect(ring[0] == 3);
    };
    
    "6 in ring2"_test = []{
        ring2   ring;

        expect(ring.empty() == true);
        expect(ring.size() == 0);
        expect(ring.full() == false);
        expect(ring.zero() == 4);
        
        ring << 5;
        
        expect(ring.empty() == false);
        expect(ring.size() == 1);
        expect(ring.full() == false);
        expect(ring.zero() == 3);
        expect(ring[0] == 5);
        
        ring << 4;
        
        expect(ring.size() == 2);
        expect(ring.full() == true);
        expect(ring.zero() == 2);
        expect(ring[0] == 4);
        expect(ring[1] == 5);
        
        ring << 3;
        
        expect(ring.size() == 2);
        expect(ring.full() == true);
        expect(ring.zero() == 1);
        expect(ring[0] == 3);
        expect(ring[1] == 4);

        ring << 2;
        
        expect(ring.size() == 2);
        expect(ring.full() == true);
        expect(ring.zero() == 0);
        expect(ring[0] == 2);
        expect(ring[1] == 3);

        ring << 1;
        
        expect(ring.size() == 2);
        expect(ring.full() == true);
        expect(ring.zero() == 1);
        expect(ring[0] == 1);
        expect(ring[1] == 2);

        ring << 0;
        
        expect(ring.size() == 2);
        expect(ring.full() == true);
        expect(ring.zero() == 0);
        expect(ring[0] == 0);
        expect(ring[1] == 1);
    };
    
    return ut::cfg<>.run();
}
