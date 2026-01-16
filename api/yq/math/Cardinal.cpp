////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Cardinal.hpp"
#include <yq/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::Cardinal)

namespace yq {
    static void reg_cardinal()
    {
        auto w = writer<Cardinal>();
        w.description("Cardinal direction");
    }
    
    YQ_INVOKE(reg_cardinal();)

    bool    is_edge(Cardinal v)
    {
        switch(v){
        case Cardinal::Unknown:
        case Cardinal::Center:
            return false;
        case Cardinal::NW:
        case Cardinal::NNW:
        case Cardinal::North:
        case Cardinal::NNE:
        case Cardinal::NE:
        case Cardinal::ENE:
        case Cardinal::East:
        case Cardinal::ESE:
        case Cardinal::SE:
        case Cardinal::SSE:
        case Cardinal::South:
        case Cardinal::SSW:
        case Cardinal::SW:
        case Cardinal::WSW:
        case Cardinal::West:
        case Cardinal::WNW:
            return true;
        default:
            return false;
        }
    }

    bool    is_horizontal(Cardinal v)
    {
        switch(v){
        case Cardinal::Unknown:
        case Cardinal::Center:
            return false;
        case Cardinal::NW:
        case Cardinal::NNW:
        case Cardinal::North:
        case Cardinal::NNE:
        case Cardinal::NE:
            return true;
        case Cardinal::ENE:
        case Cardinal::East:
        case Cardinal::ESE:
            return false;
        case Cardinal::SE:
        case Cardinal::SSE:
        case Cardinal::South:
        case Cardinal::SSW:
        case Cardinal::SW:
            return true;
        case Cardinal::WSW:
        case Cardinal::West:
            return false;
        case Cardinal::WNW:
            return true;
        default:
            return false;
        }
    }

    bool    is_north(Cardinal v)
    {
        switch(v){
        case Cardinal::Unknown:
        case Cardinal::Center:
            return false;
        case Cardinal::NW:
        case Cardinal::NNW:
        case Cardinal::North:
        case Cardinal::NNE:
        case Cardinal::NE:
        case Cardinal::ENE:
            return true;
        case Cardinal::East:
        case Cardinal::ESE:
        case Cardinal::SE:
        case Cardinal::SSE:
        case Cardinal::South:
        case Cardinal::SSW:
        case Cardinal::SW:
        case Cardinal::WSW:
        case Cardinal::West:
            return false;
        case Cardinal::WNW:
            return true;
        default:
            return false;
        }
    }
    
    bool    is_south(Cardinal v)
    {
        switch(v){
        case Cardinal::Unknown:
        case Cardinal::Center:
        case Cardinal::NW:
        case Cardinal::NNW:
        case Cardinal::North:
        case Cardinal::NNE:
        case Cardinal::NE:
        case Cardinal::ENE:
        case Cardinal::East:
            return false;
        case Cardinal::ESE:
        case Cardinal::SE:
        case Cardinal::SSE:
        case Cardinal::South:
        case Cardinal::SSW:
        case Cardinal::SW:
        case Cardinal::WSW:
            return true;
        case Cardinal::West:
        case Cardinal::WNW:
        default:
            return false;
        }
    }
    
    bool    is_east(Cardinal v)
    {
        switch(v){
        case Cardinal::Unknown:
        case Cardinal::Center:
        case Cardinal::NW:
        case Cardinal::NNW:
        case Cardinal::North:
            return false;
        case Cardinal::NNE:
        case Cardinal::NE:
        case Cardinal::ENE:
        case Cardinal::East:
        case Cardinal::ESE:
        case Cardinal::SE:
        case Cardinal::SSE:
            return true;
        case Cardinal::South:
        case Cardinal::SSW:
        case Cardinal::SW:
        case Cardinal::WSW:
        case Cardinal::West:
        case Cardinal::WNW:
        default:
            return false;
        }
    }
    
    bool    is_west(Cardinal v)
    {
        switch(v){
        case Cardinal::Unknown:
        case Cardinal::Center:
            return false;
        case Cardinal::NW:
        case Cardinal::NNW:
            return true;
        case Cardinal::North:
        case Cardinal::NNE:
        case Cardinal::NE:
        case Cardinal::ENE:
        case Cardinal::East:
        case Cardinal::ESE:
        case Cardinal::SE:
        case Cardinal::SSE:
        case Cardinal::South:
            return false;
        case Cardinal::SW:
        case Cardinal::SSW:
        case Cardinal::WSW:
        case Cardinal::West:
        case Cardinal::WNW:
            return true;
        default:
            return false;
        }
    }
    
    bool                is_vertical(Cardinal v)
    {
        switch(v){
        case Cardinal::Unknown:
        case Cardinal::Center:
            return false;
        case Cardinal::NW:
            return true;
        case Cardinal::NNW:
        case Cardinal::North:
        case Cardinal::NNE:
            return false;
        case Cardinal::NE:
        case Cardinal::ENE:
        case Cardinal::East:
        case Cardinal::ESE:
        case Cardinal::SE:
            return true;
        case Cardinal::SSE:
        case Cardinal::South:
        case Cardinal::SSW:
            return false;
        case Cardinal::SW:
        case Cardinal::WSW:
        case Cardinal::West:
        case Cardinal::WNW:
            return true;
        default:
            return false;
        }
    }

    std::string_view    key_for(Cardinal v)
    {
        switch(v){
        case Cardinal::Unknown:
            return "Unknown";
        case Cardinal::Center:
            return "Center";
        case Cardinal::NW:
            return "NW";
        case Cardinal::NNW:
            return "NNW";
        case Cardinal::North:
            return "North";
        case Cardinal::NNE:
            return "NNE";
        case Cardinal::NE:
            return "NE";
        case Cardinal::ENE:
            return "ENE";
        case Cardinal::East:
            return "East";
        case Cardinal::ESE:
            return "ESE";
        case Cardinal::SE:
            return "SE";
        case Cardinal::SSE:
            return "SSE";
        case Cardinal::South:
            return "South";
        case Cardinal::SSW:
            return "SSW";
        case Cardinal::SW:
            return "SW";
        case Cardinal::WSW:
            return "WSW";
        case Cardinal::West:
            return "West";
        case Cardinal::WNW:
            return "WNW";
        default:
            return "???";
        }
    }

    std::string_view    pretty_for(Cardinal v)
    {
        switch(v){
        case Cardinal::Unknown:
            return "Unknown";
        case Cardinal::Center:
            return "Center";
        case Cardinal::NW:
            return "Northwest";
        case Cardinal::NNW:
            return "North by Northwest";
        case Cardinal::North:
            return "North";
        case Cardinal::NNE:
            return "North by Northeast";
        case Cardinal::NE:
            return "Northeast";
        case Cardinal::ENE:
            return "East by Northeast";
        case Cardinal::East:
            return "East";
        case Cardinal::ESE:
            return "East by Southeast";
        case Cardinal::SE:
            return "Southeast";
        case Cardinal::SSE:
            return "South by Southeast";
        case Cardinal::South:
            return "South";
        case Cardinal::SSW:
            return "South by Southwest";
        case Cardinal::SW:
            return "Southwest";
        case Cardinal::WSW:
            return "West by Southwest";
        case Cardinal::West:
            return "West";
        case Cardinal::WNW:
            return "West by Northwest";
        default:
            return "???";
        }
    }
}
