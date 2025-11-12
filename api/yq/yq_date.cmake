################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_date SHARED
    date/CalendarType.cpp
    date/Date.cpp
    date/JulianDay.cpp
    date/Time.cpp
    date/Weekday.cpp
    date/dateutils.cpp
)

target_link_libraries(yq_date PUBLIC
    yq_core
)

LinkTest(yq_date)

