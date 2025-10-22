////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/coord/ecef/ECEFPosition.hpp>
#include <yq/core/Logging.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/vector/Vector3.hxx>

namespace ut = boost::ut;

using namespace ut;
using namespace yq;

    
int main()
{
    log_to_std_output();
    Meta::freeze();

    Absolute    tol(1e-3_m);

    "addition"_test = [&](){
        static const struct {
            unit::Kilometer ax, ay, az;
            unit::Kilometer bx, by, bz;
        } kCases[] = {
            { 1000., 2000., 3000., 9000., 8000., 7000. },
            { 1000., -2000., 3000., 9000., 8000., 7000. },
            { 1000., 2000., -3000., 9000., 8000., 7000. },
            { 1000., 2000., 3000., -9000., -8000., -7000. }
        };
        
        for(auto& k : kCases){
            ECEFPosition a( k.ax, k.ay, k.az  );
            ECEFPosition b( k.bx, k.by, k.bz  );
            unit::Meter3D c( k.ax+k.bx, k.ay+k.by, k.az+k.bz );
            unit::Meter3D d = a + b;
            
            expect(true == is_close(tol, d, c));
        }
    };


    "subtraction"_test = [&](){
        static const struct {
            unit::Kilometer ax, ay, az;
            unit::Kilometer bx, by, bz;
        } kCases[] = {
            { 1000., 2000., 3000., 9000., 8000., 7000. },
            { 1000., -2000., 3000., 9000., 8000., 7000. },
            { 1000., 2000., -3000., 9000., 8000., 7000. },
            { 1000., 2000., 3000., -9000., -8000., -7000. }
        };
        
        for(auto& k : kCases){
            ECEFPosition a( k.ax, k.ay, k.az  );
            ECEFPosition b( k.bx, k.by, k.bz  );
            unit::Meter3D c( k.ax-k.bx, k.ay-k.by, k.az-k.bz );
            unit::Meter3D d = a-b;
            
            expect(true == is_close(tol, d, c));
        }
    };


    return ut::cfg<>.run();
}

    
