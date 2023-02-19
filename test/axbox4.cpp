////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/AxBox4.hxx>
#include <math/Vector4.hxx>
#include <basic/Logging.hpp>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

template <typename T>
static constexpr const AxBox4<T> unitBox(-Vector4<T>(ONE), Vector4<T>(ONE));

static constexpr const AxBox4I stepBox(Vector4I(-1,-2,-3,-4), Vector4I(1,2,3,4));


ut::suite tests = []{
    "zero is zero"_test = []{
        expect( true == (AxBox4D(ZERO) == AxBox4D(ZERO) ));
    };
    
    "valid"_test = []{
        expect( true  == AxBox4D(Vector4D(-1,-1,-1,-1), Vector4D(1,1,1,1)).valid());
        expect( false == AxBox4D(Vector4D(-1,-1,-1, 1), Vector4D(1,1,1,-1)).valid());
        expect( false == AxBox4D(Vector4D(-1,-1,1, -1), Vector4D(1,1,-1,1)).valid());
        expect( true == AxBox4D(SORT, Vector4D(-1,-1,1, -1), Vector4D(1,1,-1,1)).valid());
        expect( false  == AxBox4D(Vector4D(1,1,1,1), Vector4D(-1,-1,-1,-1)).valid());
        expect( true  == AxBox4D(SORT, Vector4D(1,1,1,1), Vector4D(-1,-1,-1,-1)).valid());
    };
    
    "hypervolume"_test = []{
        expect( 16_i == hypervolume(unitBox<int>));
        expect( 32_i == hypervolume(AxBox4I( Vector4I( -2, -1, -1, -1 ), Vector4I( 2, 1, 1, 1 ))));
        expect( 32_i == hypervolume(AxBox4I( Vector4I( -1, -2, -1, -1 ), Vector4I( 1, 2, 1, 1 ))));
        expect( 32_i == hypervolume(AxBox4I( Vector4I( -1, -1, -2, -1 ), Vector4I( 1, 1, 2, 1 ))));
        expect( 32_i == hypervolume(AxBox4I( Vector4I( -1, -1, -1, -2 ), Vector4I( 1, 1, 1, 2 ))));
        expect( 384_i == hypervolume(stepBox));
    };
    
    "add_vector"_test = []{
        
        AxBox4I     a = unitBox<int>;
        Vector4I    b(X);
        AxBox4I     c(Vector4I(0, -1, -1, -1), Vector4I(2,1,1,1));
        
        expect(true == a.valid());
        expect(true == c.valid());
        expect(true == (a+b).valid());
        
        AxBox4I     d   = a + b;
        
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
        expect(true == (unitBox<int> + Vector4I(1,0,0,0) == AxBox4I(Vector4I(0, -1, -1, -1), Vector4I(2, 1, 1, 1))));
        expect(true == (unitBox<int> + Vector4I(0,1,0,0) == AxBox4I(Vector4I(-1, 0, -1, -1), Vector4I(1, 2, 1, 1))));
        expect(true == (unitBox<int> + Vector4I(0,0,1,0) == AxBox4I(Vector4I(-1, -1, 0, -1), Vector4I(1, 1, 2, 1))));
        expect(true == (unitBox<int> + Vector4I(0,0,0,1) == AxBox4I(Vector4I(-1, -1, -1, 0), Vector4I(1, 1, 1, 2))));

        expect(true == (stepBox + Vector4I(1,0,0,0) == AxBox4I(Vector4I(0, -2, -3, -4), Vector4I(2, 2, 3, 4))));
        expect(true == (stepBox + Vector4I(0,1,0,0) == AxBox4I(Vector4I(-1, -1, -3, -4), Vector4I(1, 3, 3, 4))));
        expect(true == (stepBox + Vector4I(0,0,1,0) == AxBox4I(Vector4I(-1, -2, -2, -4), Vector4I(1, 2, 4, 4))));
        expect(true == (stepBox + Vector4I(0,0,0,1) == AxBox4I(Vector4I(-1, -2, -3, -3), Vector4I(1, 2, 3, 5))));
    };
    
    "multiply_scalar"_test = []{
        expect(true == (unitBox<int> * 2 == AxBox4I(Vector4I(-2, -2, -2, -2), Vector4I(2,2,2,2))));
        expect(true == (unitBox<int> * 3 == AxBox4I(Vector4I(-3, -3, -3, -3), Vector4I(3,3,3,3))));
        expect(true == (stepBox * 2 == AxBox4I(Vector4I(-2, -4, -6, -8), Vector4I(2,4,6,8))));
    };
    
    "inflate"_test = []{
        expect(true == (unitBox<int>.inflate(1) == AxBox4I(Vector4I(-2, -2, -2, -2), Vector4I(2, 2, 2, 2))));
        expect(true == (stepBox.inflate(1) == AxBox4I(Vector4I(-2, -3, -4, -5), Vector4I(2, 3, 4, 5))));
    };
    
    "overlap"_test = []{
        expect(true == unitBox<int>.overlaps(stepBox));
        expect(true == stepBox.overlaps(unitBox<int>));
        expect(false == stepBox.overlaps(Vector4I(ALL, 6) + stepBox));
    };
    
    "eclipse box"_test = []{
        expect(true == stepBox.eclipses(unitBox<int>));
        expect(false == unitBox<int>.eclipses(stepBox));
    };
    
    "contains point"_test = []{
        expect(true == unitBox<double>.contains(Vector4D(ZERO)));
        expect(false == unitBox<double>.contains(Vector4D(NAN)));
        
        expect(true == stepBox.contains(stepBox.llll()));
        expect(true == stepBox.contains(stepBox.lllh()));
        expect(true == stepBox.contains(stepBox.llhl()));
        expect(true == stepBox.contains(stepBox.llhh()));
        expect(true == stepBox.contains(stepBox.lhll()));
        expect(true == stepBox.contains(stepBox.lhlh()));
        expect(true == stepBox.contains(stepBox.lhhl()));
        expect(true == stepBox.contains(stepBox.lhhh()));
        expect(true == stepBox.contains(stepBox.hlll()));
        expect(true == stepBox.contains(stepBox.hllh()));
        expect(true == stepBox.contains(stepBox.hlhl()));
        expect(true == stepBox.contains(stepBox.hlhh()));
        expect(true == stepBox.contains(stepBox.hhll()));
        expect(true == stepBox.contains(stepBox.hhlh()));
        expect(true == stepBox.contains(stepBox.hhhl()));
        expect(true == stepBox.contains(stepBox.hhhh()));
        expect(true == stepBox.contains(stepBox.center()));
        expect(false == stepBox.contains({2,0,0,0}));
    };
};

int main(){
    //log_to_std_output();
    return ut::cfg<>.run();
};

