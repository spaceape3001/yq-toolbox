////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/units.hpp>
#include <yq/core/Logging.hpp>

#include <yq/math/tolerance/Absolute.hpp>
#include <yq/vector/Spinor2.hpp>
#include <yq/tensor/Tensor22.hpp>
#include <yq/vector/Spinor2.hxx>
#include <yq/tensor/Tensor22.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    Absolute tol(1e-5);
    log_to_std_output();
    
    "identity"_test = [&](){
        expect(true == is_close(tol, Spinor2D(IDENTITY), 1., 0.));
    };
    
    "hpr"_test = [&](){
        //Spinor2D Q( HPR, 30._deg, 0._deg, 0._deg);
        //yInfo() << "Q... " << Q;
    
        // YAW/HEADING
        expect(true == is_close(tol, Spinor2D(HPR,  0._deg), 1., 0.));
        expect(true == is_close(tol, Spinor2D(HPR, 30._deg), 0.9659258, -0.25881904));
        expect(true == is_close(tol, Spinor2D(HPR, 45._deg), 0.92387953, -0.38268343));
        expect(true == is_close(tol, Spinor2D(HPR, 60._deg), 0.8660254, -0.5));
        expect(true == is_close(tol, Spinor2D(HPR, 120._deg), 0.5, -0.8660254038));
        expect(true == is_close(tol, Spinor2D(HPR, -30._deg), 0.9659258, 0.25881904));
        expect(true == is_close(tol, Spinor2D(HPR, -45._deg), 0.92387953, 0.38268343));
        expect(true == is_close(tol, Spinor2D(HPR, -60._deg), 0.8660254,  0.5));
        expect(true == is_close(tol, Spinor2D(HPR, -120._deg), 0.5, 0.8660254038));
    };
    
    "rotorX"_test = [&](){
        expect(true == is_close(tol, Spinor2D(CCW, 0._deg), 1., 0.));
        expect(true == is_close(tol, Spinor2D(CCW, 30._deg), 0.9659258, 0.25881904));
        expect(true == is_close(tol, Spinor2D(CCW, 60._deg), 0.8660254, 0.5));
        expect(true == is_close(tol, Spinor2D(CCW, -30._deg), 0.9659258, -0.25881904));
        expect(true == is_close(tol, Spinor2D(CCW, -60._deg), 0.8660254, -0.5));
    };
    
    "Angles"_test = [&](){
        expect(true == is_close(tol, unit::Degree(Spinor2D(CCW, 30._deg).angle(CCW)), 30. ));
        expect(true == is_close(tol, unit::Degree(Spinor2D(CCW, 60._deg).angle(CCW)), 60. ));
        expect(true == is_close(tol, unit::Degree(Spinor2D(CCW, -30._deg).angle(CCW)), -30. ));
        expect(true == is_close(tol, unit::Degree(Spinor2D(CCW, -60._deg).angle(CCW)), -60. ));
    };
    
    #if 0
        //   disabling....
    "Equivalency"_test = [&](){
        Spinor2D   s(CCW, 30_deg);
        
        yInfo() << "start with " << s;
        
        Tensor22D   t22(s);
        
        yInfo() << "becomes " << t22;
        
        Spinor2D    s22(t22);
        
        yInfo() << "returns as " << s22;
    
        expect(true == is_close(tol, s22, s));
    };
    #endif
    
    return ut::cfg<>.run();
}
