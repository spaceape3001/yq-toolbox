////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/graph_types.hpp>
#include <yq/container/Set.hpp>
#include <yq/container/MultiMap.hpp>
#include <yq/core/Tristate.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/vector/Vector2.hpp>

namespace yq {

    /*! \brief Base Data
    
        Base to the data classes... just enough complexity in the data
        structure that we can't go for simpleness.  It's point is to 
        render & import into whatever clever graph-like problem.
    */
    struct GBaseData {
        const gid_t     id;
        
        //! We won't be deleting at runtime, so this will be the marker
        bool            deleted = false;
        
        //! Hidden (inherit defers to parent, root graph will be visible)
        Tristate        hidden  = Tristate::Inherit;
        gid_t           parent  = 0;
        
        //! For rendering
        double          z       = 0.;
        
        //  attributes/properties... TODO
        
        GBaseData(gid_t _id);
        GBaseData(const GBaseData&);
        virtual ~GBaseData();
        virtual GBaseData*  clone() const = 0;

        virtual bool    is_edge() const { return false; }
        virtual bool    is_graph() const { return false; }
        virtual bool    is_line() const { return false; }
        virtual bool    is_node() const { return false; }
        virtual bool    is_port() const { return false; }
        virtual bool    is_shape() const { return false; }
        virtual bool    is_text() const { return false; }
        virtual bool    is_view() const { return false; }
    };
    
#ifdef NAN
#undef NAN
#endif

    struct GPosSizeData {
        Vector2D                position    = NAN;
        Size2D                  size        = NAN;
        
        GPosSizeData();
        GPosSizeData(const GPosSizeData&);
        ~GPosSizeData();
    };
    
    struct GSocketDir {
        Set<gid_t>              edges;
        Map<gid_t,gid_t>        routes;
        
        bool    has_edge(gid_t) const;
        bool    has_route(gid_t) const;
        
        //! Route to ID (note, implies unique edges)
        gid_t   route(gid_t) const;
        
        GSocketDir();
        ~GSocketDir();
    };

    struct GSocketCache {
        GSocketDir              in;     //!< inbound
        GSocketDir              out;    //!< outbound
        
        GSocketCache();
        virtual ~GSocketCache();  // virtual to allow dynamic casts to work
    };

    
    struct GPortCache {
        Set<gid_t>      ports;
        
        bool    has_port(gid_t) const;
        
        GPortCache();
        virtual ~GPortCache();  // virtual to allow dynamic casting to work
    };
}
