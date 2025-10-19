////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/units.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/vector/Vector3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    Meta::freeze();
    Absolute tol{1e-12_m};
    Absolute tol²{1e-12_m²};

    "addition"_test = [&](){
        static const struct {
            unit::Meter ax, ay, az;
            unit::Meter bx, by, bz;
        } kCases[] = {
            { 1., 2., 3., 9., 8., 7. },
            { 1., -2., 3., 9., 8., 7. },
            { 1., 2., -3., 9., 8., 7. },
            { 1., 2., 3., -9., -8., -7. }
        };
        
        for(auto& k : kCases){
            unit::Meter3D a( k.ax, k.ay, k.az  );
            unit::Meter3D b( k.bx, k.by, k.bz  );
            unit::Meter3D c( k.ax+k.bx, k.ay+k.by, k.az+k.bz );
            unit::Meter3D d = a + b;
            
            expect(true == is_close(tol, d, c));
        }
    
        
    };

    "subtraction"_test = [&](){
        static const struct {
            unit::Meter ax, ay, az;
            unit::Meter bx, by, bz;
        } kCases[] = {
            { 1., 2., 3., 9., 8., 7. },
            { 1., -2., 3., 9., 8., 7. },
            { 1., 2., -3., 9., 8., 7. },
            { 1., 2., 3., -9., -8., -7. }
        };
        
        for(auto& k : kCases){
            unit::Meter3D a( k.ax, k.ay, k.az  );
            unit::Meter3D b( k.bx, k.by, k.bz  );
            unit::Meter3D c( k.ax-k.bx, k.ay-k.by, k.az-k.bz );
            unit::Meter3D d = a-b;
            
            expect(true == is_close(tol, d, c));
        }
    };

    "dot"_test = [&](){
        static const struct {
            unit::Meter ax, ay, az;
            unit::Meter bx, by, bz;
        } kCases[] = {
            { 1., 2., 3., 9., 8., 7. },
            { 1., -2., 3., 9., 8., 7. },
            { 1., 2., -3., 9., 8., 7. },
            { 1., 2., 3., -9., -8., -7. }
        };
        
        for(auto& k : kCases){
            unit::Meter3D a( k.ax, k.ay, k.az  );
            unit::Meter3D b( k.bx, k.by, k.bz  );
            unit::Meter²  c = k.ax*k.bx+k.ay*k.by+k.az*k.bz;
            unit::Meter²  d = a DOT b;
            
            expect(true == is_close(tol², d, c));
        }
    };

    return ut::cfg<>.run();
}
