################################################################################
##
##  YOUR QUILL
##
################################################################################

#   ART is a visual/geometric description.  A lot of interpretation will
#   be deferred.

#   Fiftieth try the charm????
#   Want a dirt simple visual language

#   Note, we *might* move this into the toolbox... thinking about it....
#   (ie...sketching it up right now in the doodle repo)

#   Mean

add_library(yq_art SHARED
    art/Abstract.cpp
    art/Doc.cpp
    art/Obj.cpp
    art/Point.cpp
    art/Shape.cpp

    art/vertex.cpp


    

    #art/Abstract.cpp
    #art/Canvas.cpp
    #art/Doc.cpp
    #art/DocXML.cpp
    #art/Grid.cpp
    #art/Instance.cpp
    #art/Obj.cpp
    #art/PaintDevice.cpp
    #art/Painter.cpp
    #art/Shape.cpp
    #art/Surface.cpp
    #art/Terrain.cpp

    #art/paint/PaintDevice.cpp
    #art/point/Point.cpp
)

target_link_libraries(yq_art
    PUBLIC
        yq_core
        yq_file
        yq_math
        yq_xml
)


LinkTest(yq_art)

        #   Two letters are being assigned for dimension/coordinate systems
    #   0D is zero dimensional (almost useless TBH)

    #   1D is pure one dimensional
   
    #   1Y is mainly 1D dimension with a second (minor) coordinate
    #   So 1D & 1D is supported
    
    #   1Z is mainly 1D dimension with a second/third (minor) coordinates 
    #   (note Y will be considered to be of greater importance than Z)
    
    #   2C is three dimensional cylindrical coordinates, its z is considered minor (like 2Z)
    
    #   2D is pure two dimensions
    #   2G is three dimensional geodetic coordinates where Z (altitude) is considered minor
    
    #   2P is pure two dimensions with polar coordinates
    
    #   2S is spherical coordinates (z is either minor or not present)
    
    #   2Z is three dimensions with the z considered "minor" ... so think a plat map
    
    #   3C is three dimensional cylindrical coordinates
    
    
    #   3G  is three dimensional geodetic coordinates
    
    
    #   3S  is spherical coordinates
