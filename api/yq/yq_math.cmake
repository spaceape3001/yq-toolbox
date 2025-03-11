################################################################################
##
##  YOUR QUILL
##
################################################################################

option(Feature_GLM "Add GLM Bindings" ON)

if(Build_GLM)
endif()

add_library(yq_math SHARED
    coord/Coord1.cpp
    coord/Coord2.cpp
    coord/Coord3.cpp
    coord/Coord4.cpp
    coord/Coord5.cpp
    coord/Coord6.cpp
    coord/Cylindrical3.cpp
    coord/Geodetic2.cpp
    coord/Geodetic3.cpp
    coord/LatLonAlt.cpp
    coord/LatLon.cpp
    coord/Polar2.cpp

    math/Complex.cpp
    math/Counter.cpp
    math/DimMapper.cpp
    math/Fraction.cpp
    math/glm.cpp
    math/initialize.cpp
    math/Pose2.cpp
    math/Pose3.cpp
    math/Random.cpp
    math/Range.cpp
    math/SimpleSpace.cpp

    shape/AxBox1.cpp
    shape/AxBox2.cpp
    shape/AxBox3.cpp
    shape/AxBox4.cpp
    shape/AxCorners1.cpp
    shape/AxCorners2.cpp
    shape/AxCorners3.cpp
    shape/AxCorners4.cpp
    shape/Circle2.cpp
    shape/Circle3.cpp
    shape/Normal2.cpp
    shape/Normal3.cpp
    shape/Plane3.cpp
    shape/Polygon2.cpp
    shape/Polygon3.cpp
    shape/Polygon4.cpp
    shape/PolygonData.cpp
    shape/Polyline2.cpp
    shape/Polyline3.cpp
    shape/Polyline4.cpp
    shape/PolylineData.cpp
    shape/Quadrilateral2.cpp
    shape/QuadrilateralData.cpp
    shape/Ray2.cpp
    shape/Ray3.cpp
    shape/Ray4.cpp
    shape/Rectangle2.cpp
    shape/Segment1.cpp
    shape/Segment2.cpp
    shape/Segment3.cpp
    shape/Segment4.cpp
    shape/SegmentData.cpp
    shape/Size1.cpp
    shape/Size2.cpp
    shape/Size3.cpp
    shape/Size4.cpp
    shape/Sphere3.cpp
    shape/Sphere4.cpp
    shape/Tetrahedron3.cpp
    shape/TetrahedronData.cpp
    shape/Triangle2.cpp
    shape/Triangle3.cpp
    shape/Triangle4.cpp
    shape/TriangleData.cpp

    tensor/Tensor11.cpp
    tensor/Tensor12.cpp
    tensor/Tensor13.cpp
    tensor/Tensor14.cpp
    tensor/Tensor21.cpp
    tensor/Tensor22.cpp
    tensor/Tensor23.cpp
    tensor/Tensor24.cpp
    tensor/Tensor31.cpp
    tensor/Tensor32.cpp
    tensor/Tensor33.cpp
    tensor/Tensor34.cpp
    tensor/Tensor41.cpp
    tensor/Tensor42.cpp
    tensor/Tensor43.cpp
    tensor/Tensor44.cpp

    unit/Dimension.cpp
    unit/units.cpp

    vector/Bivector2.cpp
    vector/Bivector3.cpp
    vector/Bivector4.cpp
    vector/Multivector1.cpp
    vector/Multivector2.cpp
    vector/Multivector3.cpp
    vector/Multivector4.cpp
    vector/Quadvector4.cpp
    vector/Quaternion3.cpp
    vector/Trivector3.cpp
    vector/Trivector4.cpp
    vector/Vector1.cpp
    vector/Vector2.cpp
    vector/Vector3.cpp
    vector/Vector4.cpp
)

target_link_libraries(yq_math PUBLIC
    yq_core
)

if(Feature_GLM)
    target_compile_definitions(yq_math
        PUBLIC
            #   These have been mixed/scattered, use both
            YQ_FEATURE_GLM=1
            YQ_USE_GLM=1
    )

    target_include_directories(yq_math PUBLIC
        ${glm_INCLUDE_DIR}
    )
endif()

LinkTest(yq_math)

