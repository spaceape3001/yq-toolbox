////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGBA.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/color.hpp>
#include <yq/typedef/any_maps.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/xg/types.hpp>

namespace yq::xg {
    struct XGDocBase {
        //! Attributes
        string_any_multimap_t   attributes;
        
        //! Color to the object (applied to text/border)
        //! Note... moving to color spec....
        RGBA4F                  color       = { 0., 0., 0., 0. };
        

        //! ID for this item.  Set when the correlation is needed. (ie, nodes/edges)
        id_t                    id          = 0;

        XGDocBase();
        XGDocBase(const XGDocBase&);
        XGDocBase(XGDocBase&&);
        ~XGDocBase();
        XGDocBase& operator=(const XGDocBase&);
        XGDocBase& operator=(XGDocBase&&);
        bool    operator==(const XGDocBase&) const;
    };
}

