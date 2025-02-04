////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/units.hpp>
#include <yq/core/Logging.hpp>

#include <yq/math/tolerance/Absolute.hpp>
#include <yq/vector/Quaternion3.hpp>
#include <yq/vector/Quaternion3.hxx>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

int main()
{
    Absolute tol(1e-5);
    log_to_std_output();
    
    "identity"_test = [&](){
        expect(true == is_close(tol, Quaternion3D(IDENTITY), 1., 0., 0., 0.));
    };
    
    "hpr"_test = [&](){
        //Quaternion3D Q( HPR, 30._deg, 0._deg, 0._deg);
        //yInfo() << "Q... " << Q;
    
        // YAW/HEADING
        expect(true == is_close(tol, Quaternion3D(HPR,  0._deg, 0._deg, 0._deg), 1., 0., 0., 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 30._deg, 0._deg, 0._deg), 0.9659258, 0., 0., 0.25881904));
        expect(true == is_close(tol, Quaternion3D(HPR, 45._deg, 0._deg, 0._deg), 0.92387953, 0., 0., 0.38268343));
        expect(true == is_close(tol, Quaternion3D(HPR, 60._deg, 0._deg, 0._deg), 0.8660254, 0., 0., 0.5));
        expect(true == is_close(tol, Quaternion3D(HPR, 120._deg, 0._deg, 0._deg), 0.5, 0., 0., 0.8660254038));
        expect(true == is_close(tol, Quaternion3D(HPR, -30._deg, 0._deg, 0._deg), 0.9659258, 0., 0., -0.25881904));
        expect(true == is_close(tol, Quaternion3D(HPR, -45._deg, 0._deg, 0._deg), 0.92387953, 0., 0., -0.38268343));
        expect(true == is_close(tol, Quaternion3D(HPR, -60._deg, 0._deg, 0._deg), 0.8660254, 0., 0., -0.5));
        expect(true == is_close(tol, Quaternion3D(HPR, -120._deg, 0._deg, 0._deg), 0.5, 0., 0., -0.8660254038));
        
        //  PITCH
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, 30._deg, 0._deg), 0.9659258, 0., 0.25881904, 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, 45._deg, 0._deg), 0.92387953, 0.,  0.38268343, 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, 60._deg, 0._deg), 0.8660254, 0., 0.5, 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, -30._deg, 0._deg), 0.9659258, 0., -0.25881904, 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, -45._deg, 0._deg), 0.92387953, 0.,  -0.38268343, 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, -60._deg, 0._deg), 0.8660254, 0., -0.5, 0.));

        //  ROLL
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, 0._deg, 30._deg), 0.9659258, 0.25881904, 0., 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, 0._deg, 45._deg), 0.92387953, 0.38268343, 0., 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, 0._deg, 60._deg), 0.8660254, 0.5, 0., 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, 0._deg, -30._deg), 0.9659258, -0.25881904, 0., 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, 0._deg, -45._deg), 0.92387953, -0.38268343, 0., 0.));
        expect(true == is_close(tol, Quaternion3D(HPR, 0._deg, 0._deg, -60._deg), 0.8660254, -0.5, 0., 0.));
        
        //  COMBINATIONS
        expect(true == is_close(tol, Quaternion3D(HPR, 30._deg, 30._deg, 0._deg), 0.93301270, -.06698789, 0.25, 0.25 ));
        expect(true == is_close(tol, Quaternion3D(HPR, 30._deg, 30._deg, 60._deg), 0.8415063510, 0.4084936491, 0.3415063509, 0.0915063509 ));
    };
    
    "rotorX"_test = [&](){
        expect(true == is_close(tol, Quaternion3D(CCW, X, 0._deg), 1., 0., 0., 0.));
        expect(true == is_close(tol, Quaternion3D(CCW, X, 30._deg), 0.9659258, 0.25881904, 0., 0.));
        expect(true == is_close(tol, Quaternion3D(CCW, X, 60._deg), 0.8660254, 0.5, 0., 0.));
        expect(true == is_close(tol, Quaternion3D(CCW, X, -30._deg), 0.9659258, -0.25881904, 0., 0.));
        expect(true == is_close(tol, Quaternion3D(CCW, X, -60._deg), 0.8660254, -0.5, 0., 0.));
    };
    
    "rotorY"_test = [&](){
        expect(true == is_close(tol, Quaternion3D(CCW, Y, 0._deg), 1., 0., 0., 0.));
        expect(true == is_close(tol, Quaternion3D(CCW, Y, 30._deg), 0.9659258, 0., 0.25881904, 0.));
        expect(true == is_close(tol, Quaternion3D(CCW, Y, 60._deg), 0.8660254, 0., 0.5, 0.));
        expect(true == is_close(tol, Quaternion3D(CCW, Y, -30._deg), 0.9659258, 0., -0.25881904, 0.));
        expect(true == is_close(tol, Quaternion3D(CCW, Y, -60._deg), 0.8660254, 0., -0.5, 0.));
    };
    
    "rotorZ"_test = [&](){
        expect(true == is_close(tol, Quaternion3D(CCW, Z, 0._deg), 1., 0., 0., 0.));
        expect(true == is_close(tol, Quaternion3D(CCW, Z, 30._deg), 0.9659258, 0., 0., 0.25881904));
        expect(true == is_close(tol, Quaternion3D(CCW, Z, 60._deg), 0.8660254, 0., 0., 0.5));
        expect(true == is_close(tol, Quaternion3D(CCW, Z, 120._deg), 0.5, 0., 0., 0.8660254038));
        expect(true == is_close(tol, Quaternion3D(CCW, Z, -30._deg), 0.9659258, 0., 0., -0.25881904));
        expect(true == is_close(tol, Quaternion3D(CCW, Z, -60._deg), 0.8660254, 0., 0., -0.5));
        expect(true == is_close(tol, Quaternion3D(CCW, Z, -120._deg), 0.5, 0., 0., -0.8660254038));
    };
    
    return ut::cfg<>.run();
}
