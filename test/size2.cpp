////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq-toolbox/shape/Size2.hxx>
#include <yq-toolbox/vector/Vector2.hxx>
#include <yq-toolbox/basic/Logging.hpp>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

template <typename T>
static constexpr const Size2<T> unitBox(ONE);

int main()
{
    "zero is zero"_test = []{
        expect( true == (Size2I(ZERO) == Size2I(ZERO) ));
    };
    
    "area"_test = []{
        expect( 1_i == area(unitBox<int>));
        expect( 4_i == area(Size2I( 2, 2 )));
    };
    
    
    "multiply_scalar"_test = []{
        expect(true == (unitBox<int> * 2 == Size2I(2,2)));
        expect(true == (unitBox<int> * 3 == Size2I(3,3)));
    };
    
    //log_to_std_output();
    return ut::cfg<>.run();
};

