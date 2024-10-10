################################################################################
##
##  YOUR QUILL
##
################################################################################

#   Goes first... everybody relies on this
include(yq_core.cmake)

#   Things that rely on core only
include(yq_date.cmake)
include(yq_math.cmake)
include(yq_file.cmake)


##  Other things...
include(yq_color.cmake)
include(yq_xml.cmake)
include(yq_keyv.cmake)
include(yq_sql.cmake)
include(yq_userexpr.cmake)


# add_subdirectory(core)

#add_subdirectory(random)

#add_subdirectory(chemistry)
#add_subdirectory(color)
#add_subdirectory(date)
#add_subdirectory(graph)
#add_subdirectory(pixel)
#add_subdirectory(sql)
#add_subdirectory(userexpr)

