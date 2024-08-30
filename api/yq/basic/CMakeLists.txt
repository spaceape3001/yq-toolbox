project(yqbasic)

find_package(Log4cpp REQUIRED)
find_package(TBB REQUIRED)

add_library(${PROJECT_NAME} SHARED
    128-bit.hpp
    AutoReset.hpp
    BinaryBucket.hpp
    Comma.hpp
    Concat.hpp
    Created.hpp
    DbgRel.hpp
    DelayInit.hpp
    DelayInit.cpp
    ErrorDB.hpp
    ErrorDB.cpp
    errors.hpp
    Expect.hpp
    Flags.hpp
    FowlerNollVo.hpp
    Future.hpp
    Future.cpp
    Guarded.hpp
    IntRange.hpp
    Iter32.hpp
    IterUtf8.hpp
    IterUtf8.cpp
    IterW.hpp
    MD5.hpp
    MD5.cpp
    MinMaxDef.hpp
    Mutable.hpp
    Random.hpp
    Random.cpp
    Ref.hpp
    Ref.cpp
    Result.hpp
    Revision.hpp
    Revision.cpp
    Signal.hpp
    SizeTimestamp.hpp
    Stack.hpp
    StringLiteral.hpp
    ThreadId.hpp
    ThreadId.cpp
    UniqueID.hpp
    UniqueID.cpp
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${TOOLBOX_API_DIR}
        ${TBB_INCLUDE_DIR}
        ${LOG4CPP_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC yqconfig yqtrait)
