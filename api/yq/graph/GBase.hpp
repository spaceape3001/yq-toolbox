////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Ref.hpp>
#include <yq/graph/graph_types.hpp>
#include <yq/typedef/g_document.hpp>
#include <vector>

namespace yq {
    //! Root to graph things... pointer to document & ID
    class GBase {
    public:

        bool    is_edge() const;
        bool    is_deleted() const;
        bool    is_graph() const;
        bool    is_line() const;
        bool    is_node() const;
        bool    is_port() const;
        bool    is_shape() const;
        bool    is_text() const;
        //bool  is_view() const;
    
        GDocumentPtr    document();
        GDocumentCPtr   document() const;
    
        GBaseData*          data();
        const GBaseData*    data() const;
    
        std::vector<GBase>  children() const;
        size_t              children(count_k) const;
    
        constexpr gid_t   id() const { return m_id; }
    
        GBase();
        GBase(const GBase&);
        GBase(GBase&&);
        GBase(GDocumentPtr, gid_t);
        ~GBase();
        
        GBase&  operator=(const GBase&);
        GBase&  operator=(GBase&&);


        explicit operator GEdge() const;
        explicit operator GGraph() const;
        explicit operator GLine() const;
        explicit operator GNode() const;
        explicit operator GPort() const;
        explicit operator GShape() const;
        explicit operator GText() const;


        GBase       parent() const;

        operator bool() const;

    protected:
        GDocumentPtr    m_doc;
        gid_t           m_id    = 0;
    };
}
