################################################################################
##
##  YOUR QUILL
##
################################################################################

#   We'll likely add this into core (later)

add_library(yq_lua SHARED
    lua/LuaVM.cpp
    lua/lua.cpp
)

target_include_directories(yq_lua
    PRIVATE 
        ${LUA_INCLUDE_DIR}
)

target_link_libraries(yq_lua 
    PUBLIC
        yq_core
        ${LUA_LIBRARIES}
)

LinkTest(yq_lua)
