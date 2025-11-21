////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Tristate.hpp>
#include <yq/core/Enum.hpp>
#include <yq/color/RGBA.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/resource/Resource.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/xg/types.hpp>

#ifdef NAN
    #undef NAN
#endif

namespace yq::xg {

    /*! \brief Basic item document things
    */
    struct XGDocItem {
        YQ_ENUM(Type, , 
            //! No item type
            None    = 0,
            
            //! Document item type
            Document,
            
            //! Edge item type
            Edge,
            
            //! Node item type
            Node,
            
            //! SubGraph item type
            SubGraph,
            
            //! Box (annotation) type
            Box,
            
            //! Line (annotation) type
            Line,
            
            //! Text (annotation type)
            Text
        )

        //! Notes an "ALWAYS" node, ie, always check it (based on priority)
        Tristate                always      = Tristate::Inherit;
        
        //! Attributes
        string_any_multimap_t   attributes;
        
        //! Background color to the object
        RGBA4F                  bgcolor     = { 0., 0., 0., 0. };
        
        //! All children to the object (edges for nodes)
        std::vector<XGDocItem>  children;
        
        //! Color to the object (applied to text/border)
        RGBA4F                  color       = { 0., 0., 0., 0. };
        
        //! Whether this is a "decision" node... UI usage
        Tristate                decision    = Tristate::Inherit;
        
        //! ID for this item.  Set when the correlation is needed. (ie, nodes/edges)
        id_t                    id          = 0;
        
        //! Points for any lines/edges
        std::vector<Vector2F>   points;
        
        //! (Center) Position for shapes (ie, box, text, nodes)
        Vector2F                position    = NAN;
        
        //! Priority of this node/edge execution... unspecified will be treated as 0
        float                   priority    = NaNf;
        
        //! Size for shapes (box, text, nodes)
        Size2F                  size        = NAN;
        
        //! Text for text object, node name for nodes, file/url path for SubGraphs
        std::string             spec;

        //! Notes a start node, so check on start (based on priority)
        Tristate                start       = Tristate::Inherit;
        
        //! Target ID (for edges)
        id_t                    target      = 0;
        
        //! Item type
        Type                    type        = Type::None;
        
        XGDocItem(Type t=Type::None);
        ~XGDocItem();
    };

    class XGDocument : public Resource {
        YQ_RESOURCE_DECLARE(XGDocument, Resource)
    public:
        XGDocument();
        ~XGDocument();

        XGDocItem    content;
        
        static void init_meta();
    };
}

YQ_TYPE_DECLARE(yq::xg::XGDocItem::Type)
