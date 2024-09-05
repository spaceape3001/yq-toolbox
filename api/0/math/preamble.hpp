////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>
#include <yq-toolbox/coord/forward.hpp>
#include <yq-toolbox/io/StreamOps.hpp>
#include <yq-toolbox/math/algorithm.hpp>
#include <yq-toolbox/math/initialize.hpp>
#include <yq-toolbox/math/Sign.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>
#include <yq-toolbox/trait/always_false.hpp>
#include <yq-toolbox/trait/has_abs.hpp>
#include <yq-toolbox/trait/has_copysign.hpp>
#include <yq-toolbox/trait/has_half.hpp>
#include <yq-toolbox/trait/has_identity.hpp>
#include <yq-toolbox/trait/has_is_finite.hpp>
#include <yq-toolbox/trait/has_nan.hpp>
#include <yq-toolbox/trait/has_one.hpp>
#include <yq-toolbox/trait/has_sqrt.hpp>
#include <yq-toolbox/trait/has_zero.hpp>
#include <yq-toolbox/trait/ieee754.hpp>
#include <yq-toolbox/trait/integer.hpp>
#include <yq-toolbox/trait/is_arithmetic.hpp>
#include <yq-toolbox/trait/is_basic_float.hpp>
#include <yq-toolbox/trait/is_floating_point.hpp>
#include <yq-toolbox/trait/is_integral.hpp>
#include <yq-toolbox/trait/numbers.hpp>
#include <yq-toolbox/trait/product.hpp>
#include <yq-toolbox/trait/quotient.hpp>
#include <yq-toolbox/typedef/axbox1.hpp>
#include <yq-toolbox/typedef/axbox2.hpp>
#include <yq-toolbox/typedef/axbox3.hpp>
#include <yq-toolbox/typedef/axbox4.hpp>
#include <yq-toolbox/typedef/bivector2.hpp>
#include <yq-toolbox/typedef/bivector3.hpp>
#include <yq-toolbox/typedef/bivector4.hpp>
#include <yq-toolbox/typedef/circle2.hpp>
#include <yq-toolbox/typedef/complex.hpp>
#include <yq-toolbox/typedef/counter.hpp>
#include <yq-toolbox/typedef/hsl.hpp>
#include <yq-toolbox/typedef/hsv.hpp>
#include <yq-toolbox/typedef/multivector1.hpp>
#include <yq-toolbox/typedef/multivector2.hpp>
#include <yq-toolbox/typedef/multivector3.hpp>
#include <yq-toolbox/typedef/multivector4.hpp>
#include <yq-toolbox/typedef/normal2.hpp>
#include <yq-toolbox/typedef/normal3.hpp>
#include <yq-toolbox/typedef/plane3.hpp>
#include <yq-toolbox/typedef/polygon2.hpp>
#include <yq-toolbox/typedef/polygon3.hpp>
#include <yq-toolbox/typedef/polygon4.hpp>
#include <yq-toolbox/typedef/polyline2.hpp>
#include <yq-toolbox/typedef/polyline3.hpp>
#include <yq-toolbox/typedef/polyline4.hpp>
#include <yq-toolbox/typedef/pose2.hpp>
#include <yq-toolbox/typedef/pose3.hpp>
#include <yq-toolbox/typedef/quadvector4.hpp>
#include <yq-toolbox/typedef/quaternion3.hpp>
#include <yq-toolbox/typedef/range.hpp>
#include <yq-toolbox/typedef/ray2.hpp>
#include <yq-toolbox/typedef/ray3.hpp>
#include <yq-toolbox/typedef/ray4.hpp>
#include <yq-toolbox/typedef/rectangle2.hpp>
#include <yq-toolbox/typedef/rgb.hpp>
#include <yq-toolbox/typedef/rgba.hpp>
#include <yq-toolbox/typedef/quadrilateral2.hpp>
#include <yq-toolbox/typedef/segment1.hpp>
#include <yq-toolbox/typedef/segment2.hpp>
#include <yq-toolbox/typedef/segment3.hpp>
#include <yq-toolbox/typedef/segment4.hpp>
#include <yq-toolbox/typedef/size1.hpp>
#include <yq-toolbox/typedef/size2.hpp>
#include <yq-toolbox/typedef/size3.hpp>
#include <yq-toolbox/typedef/size4.hpp>
#include <yq-toolbox/typedef/sphere3.hpp>
#include <yq-toolbox/typedef/sphere4.hpp>
#include <yq-toolbox/typedef/tensor11.hpp>
#include <yq-toolbox/typedef/tensor12.hpp>
#include <yq-toolbox/typedef/tensor13.hpp>
#include <yq-toolbox/typedef/tensor14.hpp>
#include <yq-toolbox/typedef/tensor21.hpp>
#include <yq-toolbox/typedef/tensor22.hpp>
#include <yq-toolbox/typedef/tensor23.hpp>
#include <yq-toolbox/typedef/tensor24.hpp>
#include <yq-toolbox/typedef/tensor31.hpp>
#include <yq-toolbox/typedef/tensor32.hpp>
#include <yq-toolbox/typedef/tensor33.hpp>
#include <yq-toolbox/typedef/tensor34.hpp>
#include <yq-toolbox/typedef/tensor41.hpp>
#include <yq-toolbox/typedef/tensor42.hpp>
#include <yq-toolbox/typedef/tensor43.hpp>
#include <yq-toolbox/typedef/tensor44.hpp>
#include <yq-toolbox/typedef/tetrahedron3.hpp>
#include <yq-toolbox/typedef/triangle2.hpp>
#include <yq-toolbox/typedef/triangle3.hpp>
#include <yq-toolbox/typedef/triangle4.hpp>
#include <yq-toolbox/typedef/trivector3.hpp>
#include <yq-toolbox/typedef/trivector4.hpp>
#include <yq-toolbox/typedef/vector1.hpp>
#include <yq-toolbox/typedef/vector2.hpp>
#include <yq-toolbox/typedef/vector3.hpp>
#include <yq-toolbox/typedef/vector4.hpp>

#include <yq-toolbox/unit/dims.hpp>
#include <yq-toolbox/unit/declare.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>
#include <utility>

    /*
        GLM can be a heavy-weight library, so make it OPTIONAL, enabled via 
        cmake configuration *OR* by a consumer that needs it.  Note, if 
        it's being used, make sure the GLM library's include path is part
        of your target's include directories.
    */
#ifndef YQ_USE_GLM
    #ifdef YQ_FEATURE_GLM
        #define YQ_USE_GLM 1
    #endif
#endif

#ifdef YQ_USE_GLM
    #include <glm/glm.hpp>
#endif

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //      MACROS
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#ifdef PI
#undef PI
#endif



namespace yq {
    
    
        //  Some types/constants to work the constructors in magical ways :)
    
    
    template <typename> struct PolygonData;
    template <typename> struct PolylineData;
    template <typename> struct QuadrilateralData;
    template <typename> struct SegmentData;
    template <typename> struct TetrahedronData;
    template <typename> struct TriangleData;

    template <typename> struct Absolute;
    template <typename> struct AllComponents;
    template <typename> struct AnyComponents;
    template <typename> struct AxCorners1;
    template <typename> struct AxCorners2;
    template <typename> struct AxCorners3;
    template <typename> struct AxCorners4;
    template <typename> struct Data1;
    template <typename> struct Data2;
    template <typename> struct Data3;
    template <typename> struct Data4;
    template <typename> struct ElemComponents;
    
    //  ------------------------------------------------
    //  Miscellaneous
    
    struct SimpleSpace;
    

    //! Call this if math isn't getting startup-initialized 

    
    
    struct Side;
}

#ifdef NAN
    // Get RID of the old C macro!
    #undef NAN
#endif


