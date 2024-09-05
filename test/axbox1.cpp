////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq-toolbox/shape/AxBox1.hxx>
#include <yq-toolbox/vector/Vector1.hxx>
#include <yq-toolbox/basic/Logging.hpp>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

template <typename T>
static constexpr const AxBox1<T> unitBox(-Vector1<T>(ONE), Vector1<T>(ONE));

int main()
{
    "zero is zero"_test = []{
        expect( true == (AxBox1D(ZERO) == AxBox1D(ZERO) ));
    };
    
    "valid"_test = []{
        expect( true  == AxBox1D(Vector1D(-1), Vector1D(1)).valid());
        expect( false == AxBox1D(Vector1D(1), Vector1D(-1)).valid());
        expect( true == AxBox1D(SORT, Vector1D(1), Vector1D(-1)).valid());
        expect( false  == AxBox1D(Vector1D(ONE), -Vector1D(ONE)).valid());
        expect( true  == AxBox1D(SORT, Vector1D(ONE), -Vector1D(ONE)).valid());
    };
    
    "length"_test = []{
        expect( 2_i == length(unitBox<int>));
        expect( 4_i == length(AxBox1I( Vector1I( -2 ), Vector1I( 2 ))));
    };
    
    "add_vector"_test = []{
        
        AxBox1I     a = unitBox<int>;
        Vector1I    b(X);
        AxBox1I     c(Vector1I(0), Vector1I(2));
        
        expect(true == a.valid());
        expect(true == c.valid());
        expect(true == (a+b).valid());
        
        AxBox1I     d   = a + b;
        
        #if 0
        yInfo() 
            << "snapshot:\n"
            << "a is " << a << '\n'
            << "b is " << b << '\n'
            << "c is " << c << '\n'
            << "d is " << d << '\n'
        ;
        #endif
  
        expect(true == (c == d));
        expect(true == (unitBox<int> + Vector1I(1) == AxBox1I(Vector1I(0), Vector1I(2))));
    };
    
    "multiply_scalar"_test = []{
        expect(true == (unitBox<int> * 2 == AxBox1I(Vector1I(-2), Vector1I(2))));
        expect(true == (unitBox<int> * 3 == AxBox1I(Vector1I(-3), Vector1I(3))));
    };
    
    "inflate"_test = []{
        expect(true == (unitBox<int>.inflate(1) == AxBox1I(Vector1I(-2), Vector1I(2))));
    };
    
    "overlap"_test = []{
        expect(true == unitBox<int>.overlaps(unitBox<int>+Vector1I(1)));
    };
    
    "eclipse box"_test = []{
        AxBox1I         c   = unitBox<int>.inflate(2);
    
        expect(false == unitBox<int>.eclipses(unitBox<int>+Vector1I(1)));
        expect(true == c.eclipses(unitBox<int>));
    };
    
    "contains point"_test = []{
        expect(true == unitBox<double>.contains(Vector1D(ZERO)));
        expect(false == unitBox<double>.contains(Vector1D(NAN)));
        
        expect(true == unitBox<int>.contains(unitBox<int>.l()));
        expect(true == unitBox<int>.contains(unitBox<int>.h()));
        expect(true == unitBox<int>.contains(unitBox<int>.center()));
        expect(false == unitBox<int>.contains({2}));
    };

    //log_to_std_output();
    return ut::cfg<>.run();
};

