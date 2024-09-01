////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <0/math/shape/Size4.hxx>
#include <0/math/vector/Vector4.hxx>
#include <yq/basic/Logging.hpp>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

template <typename T>
static constexpr const Size4<T> unitBox(ONE);

int main()
{
    "zero is zero"_test = []{
        expect( true == (Size4I(ZERO) == Size4I(ZERO) ));
    };
    
    "area"_test = []{
        expect( 1_i == hypervolume(unitBox<int>));
        expect( 16_i == hypervolume(Size4I( 2, 2, 2, 2 )));
    };
    
    
    "multiply_scalar"_test = []{
        expect(true == (unitBox<int> * 2 == Size4I(2,2,2,2)));
        expect(true == (unitBox<int> * 4 == Size4I(4,4,4,4)));
    };
    

    //log_to_std_output();
    return ut::cfg<>.run();
};

