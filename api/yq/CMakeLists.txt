################################################################################
##
##  YOUR QUILL
##
################################################################################

#   CORE
include(yq_core.cmake)

#   FIRST STEP
include(yq_date.cmake)
include(yq_math.cmake)
include(yq_file.cmake)
include(yq_network.cmake)

#   SECOND STEP
include(yq_asset.cmake)
include(yq_chemistry.cmake)
include(yq_color.cmake)
include(yq_process.cmake)
include(yq_sql.cmake)
include(yq_userexpr.cmake)
include(yq_xml.cmake)

#   REMAINDER
include(yq_graph.cmake)
include(yq_keyv.cmake)
include(yq_raster.cmake)
