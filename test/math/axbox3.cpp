////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/shape/AxBox3.hxx>
#include <yq/vector/Vector3.hxx>
#include <yq/core/Logging.hpp>

#include <iostream>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

template <typename T>
static constexpr const AxBox3<T> unitBox(-Vector3<T>(ONE), Vector3<T>(ONE));

static constexpr const AxBox3I stepBox(Vector3I(-1,-2,-3), Vector3I(1,2,3));

#ifdef NAN
#undef NAN
#endif

int main()
{
    "zero is zero"_test = []{
        expect( true == (AxBox3D(ZERO) == AxBox3D(ZERO) ));
    };
    
    "valid"_test = []{
        expect( true  == AxBox3D(Vector3D(-1,-1,-1), Vector3D(1,1,1)).valid());
        expect( false == AxBox3D(Vector3D(-1,-1, 1), Vector3D(1,1,-1)).valid());
        expect( true == AxBox3D(SORT, Vector3D(-1,-1,1), Vector3D(1,1,-1)).valid());
        expect( false  == AxBox3D(Vector3D(ONE), -Vector3D(ONE)).valid());
        expect( true  == AxBox3D(SORT, Vector3D(ONE), -Vector3D(ONE)).valid());
    };
    
    "volume"_test = []{
        expect( 8_i == volume(unitBox<int>));
        expect( 16_i == volume(AxBox3I( Vector3I( -2, -1, -1 ), Vector3I( 2, 1, 1 ))));
        expect( 16_i == volume(AxBox3I( Vector3I( -1, -2, -1 ), Vector3I( 1, 2, 1 ))));
        expect( 16_i == volume(AxBox3I( Vector3I( -1, -1, -2 ), Vector3I( 1, 1, 2 ))));
        expect( 48_i == volume(stepBox));
    };
    
    "surface area"_test = []{
        expect( 24_i == surface_area(unitBox<int>));
        expect( 88_i == surface_area(stepBox));
    };
    
    "add_vector"_test = []{
        
        AxBox3I     a = unitBox<int>;
        Vector3I    b(X);
        AxBox3I     c(Vector3I(0, -1, -1), Vector3I(2,1,1));
        
        expect(true == a.valid());
        expect(true == c.valid());
        expect(true == (a+b).valid());
        
        AxBox3I     d   = a + b;
        
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
        expect(true == (unitBox<int> + Vector3I(1,0,0) == AxBox3I(Vector3I(0, -1, -1), Vector3I(2, 1, 1))));
        expect(true == (unitBox<int> + Vector3I(0,1,0) == AxBox3I(Vector3I(-1, 0, -1), Vector3I(1, 2, 1))));
        expect(true == (unitBox<int> + Vector3I(0,0,1) == AxBox3I(Vector3I(-1, -1, 0), Vector3I(1, 1, 2))));

        expect(true == (stepBox + Vector3I(1,0,0) == AxBox3I(Vector3I(0, -2, -3), Vector3I(2, 2, 3))));
        expect(true == (stepBox + Vector3I(0,1,0) == AxBox3I(Vector3I(-1, -1, -3), Vector3I(1, 3, 3))));
        expect(true == (stepBox + Vector3I(0,0,1) == AxBox3I(Vector3I(-1, -2, -2), Vector3I(1, 2, 4))));
    };
    
    "multiply_scalar"_test = []{
        expect(true == (unitBox<int> * 2 == AxBox3I(Vector3I(-2, -2, -2), Vector3I(2,2,2))));
        expect(true == (unitBox<int> * 3 == AxBox3I(Vector3I(-3, -3, -3), Vector3I(3,3,3))));
        expect(true == (stepBox * 2 == AxBox3I(Vector3I(-2, -4, -6), Vector3I(2,4,6))));
    };
    
    "inflate"_test = []{
        expect(true == (unitBox<int>.inflate(1) == AxBox3I(Vector3I(-2, -2, -2), Vector3I(2, 2, 2))));
        expect(true == (stepBox.inflate(1) == AxBox3I(Vector3I(-2, -3, -4), Vector3I(2, 3, 4))));
    };
    
    "overlap"_test = []{
        expect(true == unitBox<int>.overlaps(stepBox));
        expect(true == stepBox.overlaps(unitBox<int>));
        expect(false == stepBox.overlaps(Vector3I(ALL, 6) + stepBox));
    };
    
    "eclipse box"_test = []{
        expect(true == stepBox.eclipses(unitBox<int>));
        expect(false == unitBox<int>.eclipses(stepBox));
    };
    
    "contains point"_test = []{
        expect(true == unitBox<double>.contains(Vector3D(ZERO)));
        expect(false == unitBox<double>.contains(Vector3D(NAN)));
        
        expect(true == stepBox.contains(stepBox.lll()));
        expect(true == stepBox.contains(stepBox.llh()));
        expect(true == stepBox.contains(stepBox.lhl()));
        expect(true == stepBox.contains(stepBox.lhh()));
        expect(true == stepBox.contains(stepBox.hll()));
        expect(true == stepBox.contains(stepBox.hlh()));
        expect(true == stepBox.contains(stepBox.hhl()));
        expect(true == stepBox.contains(stepBox.hhh()));
        expect(true == stepBox.contains(stepBox.center()));
        expect(false == stepBox.contains({2,0,0}));
    };

    //log_to_std_output();
    return ut::cfg<>.run();
};

