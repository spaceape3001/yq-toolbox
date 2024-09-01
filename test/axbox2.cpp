////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>

#include <0/math/shape/AxBox2.hpp>
#include <0/math/shape/Circle2.hpp>
#include <yq/basic/Logging.hpp>

#include <0/math/shape/AxBox2.hxx>
#include <0/math/vector/Vector2.hxx>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

template <typename T>
static constexpr const AxBox2<T> unitBox(-Vector2<T>(ONE), Vector2<T>(ONE));

static constexpr const AxBox2I stepBox(Vector2I(-1,-2), Vector2I(1,2));

int main()
{
    "zero is zero"_test = []{
        expect( true == (AxBox2D(ZERO) == AxBox2D(ZERO) ));
    };
    
    "valid"_test = []{
        expect( true  == AxBox2D(Vector2D(-1,-1), Vector2D(1,1)).valid());
        expect( false == AxBox2D(Vector2D(-1,1), Vector2D(1,-1)).valid());
        expect( true == AxBox2D(SORT, Vector2D(-1,1), Vector2D(1,-1)).valid());
        expect( false  == AxBox2D(Vector2D(ONE), -Vector2D(ONE)).valid());
        expect( true  == AxBox2D(SORT, Vector2D(ONE), -Vector2D(ONE)).valid());
    };
    
    "area"_test = []{
        expect( 4_i == area(unitBox<int>));
        expect( 8_i == area(AxBox2I( Vector2I( -2, -1 ), Vector2I( 2, 1 ))));
        expect( 8_i == area(AxBox2I( Vector2I( -1, -2 ), Vector2I( 1, 2 ))));
        expect( 8_i == area(stepBox));
    };
    
    "perimeter"_test = []{
        expect( 8_i == perimeter(unitBox<int>));
        expect( 12_i == perimeter(stepBox));
    };
    
    "add_vector"_test = []{
        
        AxBox2I     a = unitBox<int>;
        Vector2I    b(X);
        AxBox2I     c(Vector2I(0, -1), Vector2I(2,1));
        
        expect(true == a.valid());
        expect(true == c.valid());
        expect(true == (a+b).valid());
        
        AxBox2I     d   = a + b;
        
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
        expect(true == (unitBox<int> + Vector2I(1,0) == AxBox2I(Vector2I(0, -1), Vector2I(2, 1))));
        expect(true == (unitBox<int> + Vector2I(0,1) == AxBox2I(Vector2I(-1, 0), Vector2I(1, 2))));

        expect(true == (stepBox + Vector2I(1,0) == AxBox2I(Vector2I(0, -2), Vector2I(2, 2))));
        expect(true == (stepBox + Vector2I(0,1) == AxBox2I(Vector2I(-1, -1), Vector2I(1, 3))));
    };
    
    "multiply_scalar"_test = []{
        expect(true == (unitBox<int> * 2 == AxBox2I(Vector2I(-2, -2), Vector2I(2,2))));
        expect(true == (unitBox<int> * 3 == AxBox2I(Vector2I(-3, -3), Vector2I(3,3))));
        expect(true == (stepBox * 2 == AxBox2I(Vector2I(-2, -4), Vector2I(2,4))));
    };
    
    "inflate"_test = []{
        expect(true == (unitBox<int>.inflate(1) == AxBox2I(Vector2I(-2, -2), Vector2I(2, 2))));
        expect(true == (stepBox.inflate(1) == AxBox2I(Vector2I(-2, -3), Vector2I(2, 3))));
    };
    
    "overlap"_test = []{
        expect(true == unitBox<int>.overlaps(stepBox));
        expect(true == stepBox.overlaps(unitBox<int>));
        expect(false == stepBox.overlaps(Vector2I(ALL, 6) + stepBox));
    };
    
    "eclipse box"_test = []{
        expect(true == stepBox.eclipses(unitBox<int>));
        expect(false == unitBox<int>.eclipses(stepBox));
    };
    
    "contains point"_test = []{
        expect(true == unitBox<double>.contains(Vector2D(ZERO)));
        expect(false == unitBox<double>.contains(Vector2D(NAN)));
        
        expect(true == stepBox.contains(stepBox.ll()));
        expect(true == stepBox.contains(stepBox.lh()));
        expect(true == stepBox.contains(stepBox.hl()));
        expect(true == stepBox.contains(stepBox.hh()));
        expect(true == stepBox.contains(stepBox.center()));
        expect(false == stepBox.contains({2,0}));
    };
    
    "incircle"_test = []{
        expect(true == (unitBox<int>.incircle() == Circle2<int>(Vector2I(ZERO), 1)));
        expect(true == (stepBox.incircle() == Circle2<int>(Vector2I(ZERO), 1)));
    };

    //log_to_std_output();
    return ut::cfg<>.run();
};

