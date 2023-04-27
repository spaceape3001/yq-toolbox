////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/shape/Size3.hxx>
#include <math/vector/Vector3.hxx>
#include <basic/Logging.hpp>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

template <typename T>
static constexpr const Size3<T> unitBox(ONE);

ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (Size3I(ZERO) == Size3I(ZERO) ));
    };
    
    "area"_test = []{
        expect( 1_i == volume(unitBox<int>));
        expect( 8_i == volume(Size3I( 2, 2, 2 )));
    };
    
    
    "multiply_scalar"_test = []{
        expect(true == (unitBox<int> * 2 == Size3I(2,2,2)));
        expect(true == (unitBox<int> * 3 == Size3I(3,3,3)));
    };
    
};

int main(){
    //log_to_std_output();
    return ut::cfg<>.run();
};

