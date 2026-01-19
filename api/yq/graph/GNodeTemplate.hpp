////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGB.hpp>
#include <yq/color/RGBA.hpp>
#include <yq/math/Range.hpp>
#include <yq/resource/Resource.hpp>
#include <yq/typedef/any_maps.hpp>
#include <yq/typedef/icon_map.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/g_node_template.hpp>

namespace yq {

    struct GPinTemplate {
        //! Where it attaches to on the symbol
        std::string     attach;
        
        //! Count {0,0} implies unlimited, and {N,0} implies N...unlimited
        RangeU          count       = {1, 1};  
        
        //! Description
        std::string     description;
        
        //! Our label (overrides prog text)
        std::string     label;

        //! TRUE if this is an input pin
        bool            input   = true;
        
        //! TRUE if this is an output pin
        bool            output  = true;
    };

    struct GEdgeTemplate {
        bool    bidirectional = false;
    };

    /*! \brief Graph Node Description
    
        This isn't a node itself, but the type of the node.
        (ie... a conditional IF, or a command, or a summation or a person on family tree)
        
        Point is, want a generic graph editor to be able to do an icon & render it.
        
        \note a Meta node might be an extract for a subgraph, a consolidated node, etc...
    */
    class GNodeTemplate : public Resource {
        YQ_RESOURCE_DECLARE(GNodeTemplate, Resource)
    public:
    
        // ! Generic attributes/overrides/etc (TBD/TODO)
        //string_any_map_t            attributes;
    
        //! Category we should be listed under
        std::string                 category;
        
        struct {
            color_spec  dark, light;    // used for dark/light themes (expect ImGui to use dark, while Qt uses light)
        }                           color;
        
        //! Description
        std::string     description;

        // Outbound edges (TODO)
        //std::vector<GEdgeTemplate>  edges;
        
        // Graph type... XG, DFG, etc
        // std::string              family;
        
        //! Any/all icons.  SVG should be [0]
        icon_spec_map_t              icons;
        
        // Idea is to have some inheritance (later)
        //std::vector<Url>            inherits;
        
        //! What should be displayed (name, key, url) will be used as backups)
        std::string                 label;
        
        //! Logical Pins/Ports
        std::vector<GPinTemplate>   pins;
        
        //! Our symbol (specification)
        // \note As tempting as Url is here...don't, fouls with the resource system
        std::string                 symbol; 
        
        
        GNodeTemplate();
        ~GNodeTemplate();
        
        size_t data_size() const override;
        
        static void init_meta();
    };
}
