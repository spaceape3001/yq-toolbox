////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/shape/Size1.hxx>
#include <0/math/vector/Vector1.hxx>
#include <yq/basic/Logging.hpp>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

template <typename T>
static constexpr const Size1<T> unitBox(ONE);

int main()
{
    "zero is zero"_test = []{
        expect( true == (Size1I(ZERO) == Size1I(ZERO) ));
    };
    
    "length"_test = []{
        expect( 1_i == length(unitBox<int>));
        expect( 2_i == length(Size1I( 2 )));
    };
    
    
    "multiply_scalar"_test = []{
        expect(true == (unitBox<int> * 2 == Size1I(2)));
        expect(true == (unitBox<int> * 3 == Size1I(3)));
    };
    
    //log_to_std_output();
    return ut::cfg<>.run();
};

