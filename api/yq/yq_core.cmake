################################################################################
##
##  YOUR QUILL
##
################################################################################

find_package(Log4cpp REQUIRED)
find_package(TBB REQUIRED)

add_library(yq_core SHARED
    strings.cpp

    container/ByteArray.cpp

    core/Any.cpp
    core/BasicApp.cpp
    core/Cleanup.cpp
    core/DelayInit.cpp
    core/Enum.cpp
    core/ErrorDB.cpp
    core/Flag.cpp
    core/Future.cpp
    core/Global.cpp
    core/Logging.cpp
    core/Memory.cpp
    core/MetaObject.cpp
    core/Object.cpp
    core/Ref.cpp
    core/Revision.cpp
    core/Stream.cpp
    core/StreamOps.cpp
    core/ThreadId.cpp
    core/Tristate.cpp
    core/UniqueID.cpp
    
    hash/MD5.cpp

    meta/AnyArgHelper.cpp
    meta/ArgMeta.cpp
    meta/CompoundMeta.cpp
    meta/ConstructorMeta.cpp
    meta/Generator.cpp
    meta/GlobalMeta.cpp
    meta/Meta.cpp
    meta/MetaWriter.cpp
    meta/MethodMeta.cpp
    meta/ObjectMeta.cpp
    meta/OperatorMeta.cpp
    meta/PropertyMeta.cpp
    meta/PropGetter.cpp
    meta/PropSetter.cpp
    meta/StdTypes.cpp
    meta/TypeMeta.cpp
    meta/UntypeMeta.cpp
    
    #   Moving this here as many more need it than simply "net"
    net/Url.cpp

    stream/Bytes.cpp
    stream/File.cpp
    stream/First.cpp
    stream/LineCol.cpp
    stream/Logger.cpp
    stream/Null.cpp
    stream/StdError.cpp
    stream/StdOutput.cpp
    stream/StdStream.cpp
    stream/Text.cpp
    
    text/Encode64.cpp
    text/misc.cpp
    text/misc32.cpp
    text/parse.cpp
    text/parse32.cpp
)

target_compile_definitions(yq_core
    PRIVATE 
        YQ__CORE__OVERRIDE 
)

target_include_directories(yq_core
    PUBLIC 
        ${TOOLBOX_BIN_DIR}
        ${YQ_TOOLBOX_API}
        ${TBB_INCLUDE_DIR}
        ${LOG4CPP_INCLUDE_DIR}
)

target_link_libraries(yq_core
    PUBLIC 
        yq_text
        ${LOG4CPP_LIBRARIES} 
        ${TBB_LIBRARIES}
        tbbmalloc_proxy
)

LinkTest(yq_core)

