################################################################################
##
##  YOUR QUILL
##
################################################################################

#   CORE
include(yq_text.cmake)
include(yq_core.cmake)

if(Build_Lua)
    include(yq_lua.cmake)
endif()

#   FIRST STEP
include(yq_date.cmake)
include(yq_math.cmake)
# include(yq_post.cmake)
include(yq_file.cmake)
include(yq_net.cmake)

#   SECOND STEP
include(yq_resource.cmake)
include(yq_chemistry.cmake)
include(yq_color.cmake)
include(yq_process.cmake)
# include(yq_data.cmake)

if(Build_SQL)
    include(yq_sql.cmake)
endif()

include(yq_userexpr.cmake)
include(yq_xml.cmake)

#   REMAINDER
include(yq_graph.cmake)
include(yq_keyv.cmake)
include(yq_raster.cmake)
include(yq_xg.cmake)

