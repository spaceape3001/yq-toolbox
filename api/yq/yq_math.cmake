################################################################################
##
##  YOUR QUILL
##
################################################################################

option(Feature_GLM "Add GLM Bindings" ON)

if(Build_GLM)
endif()

add_library(yq_math SHARED
    coord/coord.cpp
    math/math.cpp
    math/Random.cpp
    shape/shape.cpp
    tensor/tensor.cpp
    unit/Dimension.cpp
    unit/units.cpp
    vector/vector.cpp
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

