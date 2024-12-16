################################################################################
##
##  YOUR QUILL
##
################################################################################


add_library(yq_sql SHARED
    sql/SqlError.cpp
    sql/SqlLite.cpp
    sql/SqlStatement.cpp
    sql/SqlUtils.cpp
)

target_link_libraries(yq_sql 
    PUBLIC
        yq_core
        ${SQLite3_LIBRARY}

    PRIVATE
        yq_file
)

target_include_directories(yq_sql
    PUBLIC 
        ${SQLite3_INCLUDE_DIRS}
)


LinkTest(yq_sql)

