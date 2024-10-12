################################################################################
##
##  YOUR QUILL
##
################################################################################

add_executable(wiz 
    main.cpp 
)

# target_include_directories(wiz PRIVATE ${TOOLBOX_API_DIR})
target_compile_definitions(wiz PUBLIC
        "-DYQ_API_DIR=\"${TOOLBOX_API_DIR}\"" 
)
target_link_libraries(wiz PUBLIC yq_text)
