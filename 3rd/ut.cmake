if(NOT TARGET BoostUT)
    set(ut_dir ${CMAKE_CURRENT_LIST_DIR}/ut)
    add_library(BoostUT INTERFACE)
    target_sources(BoostUT INTERFACE
        ${ut_dir}/include/boost/ut.hpp
    )
    target_include_directories(BoostUT INTERFACE ${ut_dir}/include)
endif()

