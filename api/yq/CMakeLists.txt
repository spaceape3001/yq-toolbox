project(yqtoolbox2)

option(Feature_GLM "Add GLM Bindings" ON)

if(Feature_GLM)
    find_package(glm REQUIRED)
endif()

find_package(Log4cpp REQUIRED)
find_package(TBB REQUIRED)
find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)

#   This is a testing file, excluded from GIT, used for quick test compilation 
#   of code before sliding it into the appropriate spot of the build.
#   (ie.  prototyping goes here, but do not commit/push test.cpp.)
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test.cpp)
    set(core_test_source ./test.cpp)
endif()

add_library(${PROJECT_NAME} SHARED
    ${core_test_source}

    errors.hpp
    keywords.hpp

    basic/128-bit.hpp
    basic/AutoReset.hpp
    basic/BinaryBucket.hpp
    basic/Concat.hpp
    basic/Created.hpp
    basic/DbgRel.hpp
    basic/DelayInit.hpp
    basic/DelayInit.cpp
    basic/ErrorDB.hpp
    basic/ErrorDB.cpp
    basic/Expect.hpp
    basic/Flags.hpp
    basic/FowlerNollVo.hpp
    basic/Future.hpp
    basic/Future.cpp
    basic/Guarded.hpp
    basic/IntRange.hpp
    basic/MD5.hpp
    basic/MD5.cpp
    basic/MinMaxDef.hpp
    basic/Mutable.hpp
    basic/Random.hpp
    basic/Random.cpp
    basic/Ref.hpp
    basic/Ref.cpp
    basic/Result.hpp
    basic/Revision.hpp
    basic/Revision.cpp
    basic/Signal.hpp
    basic/SizeTimestamp.hpp
    basic/StringLiteral.hpp
    basic/ThreadId.hpp
    basic/ThreadId.cpp
    basic/UniqueID.hpp
    basic/UniqueID.cpp

    config/json.hpp
    config/json_fwd.hpp
    config/string.hpp
    config/xml.hpp
    config/xml_fwd.hpp
    
    container/Array.hpp
    container/ArrayX.hpp
    container/BasicBuffer.hpp
    container/BitArray.hpp
    container/ByteArray.hpp
    container/ByteArray.cpp
    container/Deque.hpp
    container/Hash.hpp
    container/HashListImpl.hxx
    container/HashMapImpl.hxx
    container/HashVectorImpl.hxx
    container/List.hpp
    container/ListSetImpl.hxx
    container/ListVectorImpl.hxx
    container/Map.hpp
    container/MapListImpl.hxx
    container/MapVectorImpl.hxx
    container/MultiMap.hpp
    container/MultiMapVectorImpl.hxx
    container/Set.hpp
    container/SetVectorImpl.hxx
    container/Stack.hpp
    container/Vector.hpp
    
    container/initlist_utils.hpp
    container/map_utils.hpp
    container/reverse.hpp
    container/set_utils.hpp
    container/vector_utils.hpp
    container/container.cpp
    
    coord/Coord1.hpp
    coord/Coord1.hxx
    coord/Coord1.cpp
    coord/Coord2.hpp
    coord/Coord2.hxx
    coord/Coord2.cpp
    coord/Coord3.hpp
    coord/Coord3.hxx
    coord/Coord3.cpp
    coord/Coord4.hpp
    coord/Coord4.hxx
    coord/Coord4.cpp
    coord/Coord5.hpp
    coord/Coord5.hxx
    coord/Coord5.cpp
    coord/Coord6.hpp
    coord/Coord6.hxx
    coord/Coord6.cpp
    coord/forward.hpp
    
    io/FixedBuffer.hpp
    io/Stream.hpp
    io/Stream.cpp
    
    io/stream/Bytes.hpp
    io/stream/Bytes.cpp
    io/stream/File.hpp
    io/stream/File.cpp
    io/stream/First.hpp
    io/stream/First.cpp
    io/stream/LineCol.hpp
    io/stream/LineCol.cpp
    io/stream/QBytes.hpp
    io/stream/StdError.hpp
    io/stream/StdError.cpp
    io/stream/StdOutput.hpp
    io/stream/StdOutput.cpp
    io/stream/StdStream.hpp
    io/stream/StdStream.cpp
    io/stream/Text.hpp
    io/stream/Text.cpp

    math/AllComponents.hpp
    math/AnyComponents.hpp
    math/Data1.hpp
    math/Data2.hpp
    math/Data3.hpp
    math/Data4.hpp
    math/gcd.hpp
    math/glm.hpp
    math/glm_types.hpp
    math/integer.hpp
    
    math/template/fraction.hpp
    math/template/gcd.hpp
    
    math/tolerance/Absolute.hpp
    math/tolerance/Relative.hpp
    
    math/unit/declare.hpp
    math/unit/dims.hpp
    
    text/Comma.hpp
    text/IgCase.hpp
    text/Iter32.hpp
    text/IterUtf8.hpp
    text/IterUtf8.cpp
    text/IterW.hpp
    text/MaybeCase.hpp
    text/RevIgCase.hpp

    trait/always_false.hpp
    trait/always_true.hpp
    trait/argument_type.hpp
    trait/can_add.hpp
    trait/can_affirm.hpp
    trait/can_divide.hpp
    trait/can_multiply.hpp
    trait/can_negate.hpp
    trait/can_subtract.hpp
    trait/can_two_add.hpp
    trait/can_two_divide.hpp
    trait/can_two_multiply.hpp
    trait/can_two_subtract.hpp
    trait/function_arguments.hpp
    trait/has_abs.hpp
    trait/has_addition.hpp
    trait/has_copysign.hpp
    trait/has_equality.hpp
    trait/has_half.hpp
    trait/has_identity.hpp
    trait/has_inequality.hpp
    trait/has_is_finite.hpp
    trait/has_less.hpp
    trait/has_nan.hpp
    trait/has_one.hpp
    trait/has_sqrt.hpp
    trait/has_subtraction.hpp
    trait/has_zero.hpp
    trait/ieee754.hpp
    trait/indices.hpp
    trait/integer.hpp
    trait/is_arithmetic.hpp
    trait/is_floating_point.hpp
    trait/is_integral.hpp
    trait/is_stdarray.hpp
    trait/is_stdspan.hpp
    trait/is_stdvector.hpp
    trait/is_template.hpp
    trait/not_copyable.hpp
    trait/not_moveable.hpp
    trait/return_type.hpp
    trait/sink.hpp
    trait/weak.hpp
)

##########################
##  COMPILER DEFINITIONS

target_compile_definitions(${PROJECT_NAME}
    PRIVATE 
        YQ__CORE__OVERRIDE 
)

if(Feature_GLM)
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
            YQ_FEATURE_GLM=1
    )
endif()

##########################
##  INCLUDE DIRECTORIES

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${TOOLBOX_BIN_DIR}
        ${TOOLBOX_API_DIR}
        ${TBB_INCLUDE_DIR}
        ${LOG4CPP_INCLUDE_DIR}
        ${SQLite3_INCLUDE_DIRS}
)

if(Feature_GLM)
    target_include_directories(${PROJECT_NAME} INTERFACE
        ${glm_INCLUDE_DIR}
    )
endif()


##########################
##  OTHER LIBRARIES

target_link_libraries(${PROJECT_NAME} PUBLIC 
    ${LOG4CPP_LIBRARIES} 
    ${TBB_LIBRARIES}
    ${CURL_LIBRARIES}
    ${SQLite3_LIBRARY}

    json
    RapidXml
    tbbmalloc_proxy

     PRIVATE
        pstreams
)

IF(GCC)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            stdc++fs
            stdc++exp
    )
ENDIF()

##########################
##  LINK TEST

LinkTest(${PROJECT_NAME})

