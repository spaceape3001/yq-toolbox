////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>
#include <yq/coord/forward.hpp>
#include <yq/io/StreamOps.hpp>
#include <yq/math/Sign.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/always_false.hpp>
#include <yq/trait/has_abs.hpp>
#include <yq/trait/has_copysign.hpp>
#include <yq/trait/has_half.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_sqrt.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/ieee754.hpp>
#include <yq/trait/integer.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/is_basic_float.hpp>
#include <yq/trait/is_floating_point.hpp>
#include <yq/trait/is_integral.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/typedef/axbox1.hpp>
#include <yq/typedef/axbox2.hpp>
#include <yq/typedef/axbox3.hpp>
#include <yq/typedef/axbox4.hpp>
#include <yq/typedef/bivector2.hpp>
#include <yq/typedef/bivector3.hpp>
#include <yq/typedef/bivector4.hpp>
#include <yq/typedef/circle2.hpp>
#include <yq/typedef/complex.hpp>
#include <yq/typedef/counter.hpp>
#include <yq/typedef/hsl.hpp>
#include <yq/typedef/hsv.hpp>
#include <yq/typedef/multivector1.hpp>
#include <yq/typedef/multivector2.hpp>
#include <yq/typedef/multivector3.hpp>
#include <yq/typedef/multivector4.hpp>
#include <yq/typedef/normal2.hpp>
#include <yq/typedef/normal3.hpp>
#include <yq/typedef/plane3.hpp>
#include <yq/typedef/polygon2.hpp>
#include <yq/typedef/polygon3.hpp>
#include <yq/typedef/polygon4.hpp>
#include <yq/typedef/polyline2.hpp>
#include <yq/typedef/polyline3.hpp>
#include <yq/typedef/polyline4.hpp>
#include <yq/typedef/pose2.hpp>
#include <yq/typedef/pose3.hpp>
#include <yq/typedef/quadvector4.hpp>
#include <yq/typedef/quaternion3.hpp>
#include <yq/typedef/range.hpp>
#include <yq/typedef/ray2.hpp>
#include <yq/typedef/ray3.hpp>
#include <yq/typedef/ray4.hpp>
#include <yq/typedef/rectangle2.hpp>
#include <yq/typedef/rgb.hpp>
#include <yq/typedef/rgba.hpp>
#include <yq/typedef/quadrilateral2.hpp>
#include <yq/typedef/segment1.hpp>
#include <yq/typedef/segment2.hpp>
#include <yq/typedef/segment3.hpp>
#include <yq/typedef/segment4.hpp>
#include <yq/typedef/size1.hpp>
#include <yq/typedef/size2.hpp>
#include <yq/typedef/size3.hpp>
#include <yq/typedef/size4.hpp>
#include <yq/typedef/sphere3.hpp>
#include <yq/typedef/sphere4.hpp>
#include <yq/typedef/tensor11.hpp>
#include <yq/typedef/tensor12.hpp>
#include <yq/typedef/tensor13.hpp>
#include <yq/typedef/tensor14.hpp>
#include <yq/typedef/tensor21.hpp>
#include <yq/typedef/tensor22.hpp>
#include <yq/typedef/tensor23.hpp>
#include <yq/typedef/tensor24.hpp>
#include <yq/typedef/tensor31.hpp>
#include <yq/typedef/tensor32.hpp>
#include <yq/typedef/tensor33.hpp>
#include <yq/typedef/tensor34.hpp>
#include <yq/typedef/tensor41.hpp>
#include <yq/typedef/tensor42.hpp>
#include <yq/typedef/tensor43.hpp>
#include <yq/typedef/tensor44.hpp>
#include <yq/typedef/tetrahedron3.hpp>
#include <yq/typedef/triangle2.hpp>
#include <yq/typedef/triangle3.hpp>
#include <yq/typedef/triangle4.hpp>
#include <yq/typedef/trivector3.hpp>
#include <yq/typedef/trivector4.hpp>
#include <yq/typedef/vector1.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/typedef/vector3.hpp>
#include <yq/typedef/vector4.hpp>

#include <yq/math/unit/dims.hpp>
#include <yq/math/unit/declare.hpp>

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
    template <typename> struct UV;
    template <typename> struct UVW;
    
    //  ------------------------------------------------
    //  Miscellaneous
    
    struct SimpleSpace;
    


    //! Call this if math isn't getting startup-initialized 
    void        initialize_math();

    using std::max;
    using std::min;
    using std::abs;
    
    
    
    struct Side;
}

#ifdef NAN
    // Get RID of the old C macro!
    #undef NAN
#endif


