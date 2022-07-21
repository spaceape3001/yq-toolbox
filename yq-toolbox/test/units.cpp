////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <math/Absolute.hpp>
#include <math/Units.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

Absolute tol{1e-12};

ut::suite tests = []{
    "add_meters"_test = []{
        expect( true == is_close(tol, 1_m + 1_m, 2_m));
        expect( true == is_close(tol, 1_m + 2_m, 3_m));
        expect( true == is_close(tol, 2_m + 1_m, 3_m));
    };
    
    "add_meter_foot"_test = []{
        expect( true == is_close(tol, 1_m + 1_ft, 1.3048_m));
        expect( true == is_close(tol, 1_ft + 1_m, 1.3048_m));
    };
    
    "divide_joule_second"_test = []{
        expect( true == is_close(tol, 25._J/5._s, 5_W));
        expect( true == is_close(tol, 5._J/25._s, 0.2_W));
    };
    
    "multiply_newtown_meter"_test = []{
        expect( true == is_close(tol, 1_N*1_m, 1._J));
        expect( true == is_close(tol, 1_N*2_m, 2._J));
        expect( true == is_close(tol, 2_N*1_m, 2._J));
        expect( true == is_close(tol, 2_N*2_m, 4._J));
    };
    
    "subtract_hertz"_test = []{
        expect( true == is_close(tol, 1_Hz - 1_Hz, 0_Hz ));
        expect( true == is_close(tol, 3_Hz - 1_Hz, 2_Hz ));
    };

    "subtract_kilohertz_hertz"_test = []{
        expect( true == is_close(tol, 1_kHz - 1_Hz, 999_Hz ));
        expect( true == is_close(tol, 3_kHz - 1_Hz, 2999_Hz ));
    };
};

int main(){
    return ut::cfg<>.run();
};

