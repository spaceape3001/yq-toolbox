project(yqconfig)

if(Feature_GLM)
    find_package(glm REQUIRED)
endif()

add_library(${PROJECT_NAME} INTERFACE
    keywords.hpp
    json.hpp
    json_fwd.hpp
)

target_link_libraries(${PROJECT_NAME} INTERFACE
    json
)

if(Feature_GLM)
    target_include_directories(${PROJECT_NAME} INTERFACE
        ${glm_INCLUDE_DIR}
    )
endif()
