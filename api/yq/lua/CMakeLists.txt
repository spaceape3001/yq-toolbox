################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_lualua SHARED
    LuaVM.cpp
    lua.cpp
    metaobject.cpp
)

target_include_directories(yq_lualua
    PUBLIC
        ${LUA_INCLUDE_DIR}
)

target_link_libraries(yq_lualua 
    PUBLIC
        yq_core
        ${LUA_LIBRARIES}
)

LinkTest(yq_lua)
