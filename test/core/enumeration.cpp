////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/core/Enumeration.hpp>
#include <yq/core/Result.hpp>
#include <yq/core/Enumeration.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

enum class Color {
    Black,
    Red,
    Orange,
    Yellow,
    Green,
    Cyan,
    Blue,
    Violet,
    White
};

YQ_ENUMERATION_IMPLEMENT(Color)

int main()
{
    "Names"_test = [](){
        expect( key_of(Color::Black) == "Black" );
        expect( key_of(Color::Red) == "Red" );
        expect( key_of(Color::Orange) == "Orange" );
        expect( key_of(Color::Yellow) == "Yellow" );
        expect( key_of(Color::Green) == "Green" );
        expect( key_of(Color::Cyan) == "Cyan" );
        expect( key_of(Color::Blue) == "Blue" );
        expect( key_of(Color::Violet) == "Violet" );
        expect( key_of(Color::White) == "White" );

        expect( key_of(Color::Red) != "Black" );
        expect( key_of(Color::Orange) != "Red" );
        expect( key_of(Color::Yellow) != "Orange" );
        expect( key_of(Color::Green) != "Yellow" );
        expect( key_of(Color::Cyan) != "Green" );
        expect( key_of(Color::Blue) != "Cyan" );
        expect( key_of(Color::Violet) != "Blue" );
        expect( key_of(Color::White) != "Violet" );
        expect( key_of(Color::Black) != "White" );
    };

    "Values"_test = [](){
    
        auto& em = enumeration<Color>();
        Result<Color>   x;
        
        x   = em.value_of("Black");
        expect(x.good);
        expect(x.value == Color::Black);
    };

    return ut::cfg<>.run();
}


