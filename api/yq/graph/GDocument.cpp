////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GDocument.hpp"
#include "GDocument.hxx"

#include "GBaseData.hpp"
#include "GEdgeData.hpp"
#include "GGraphData.hpp"
#include "GLineData.hpp"
#include "GNodeData.hpp"
#include "GPortData.hpp"
#include "GShapeData.hpp"
#include "GLineData.hpp"
//#include "GViewData.hpp"

#include "logging.hpp"
#include <yq/resource/ResourceMetaWriter.hpp>

YQ_RESOURCE_IMPLEMENT(yq::GDocument)

namespace yq {
    GDocument::GDocument()
    {
    }
    
    GDocument::GDocument(new_k)
    {
        graph(CREATE);
    }

    GDocument::GDocument(const GDocument& cp) : m_kind(cp.m_kind)
    {
        if(cp.m_data.empty())
            return;
        m_data.resize(cp.m_data.size(), nullptr);
        for(size_t n=0;n<cp.m_data.size();++n){
            if(!cp.m_data[n])
                continue;
            if(cp.m_data[n]->deleted) // might be a mistake...?
                continue;
            m_data[n]   = cp.m_data[n]->clone();
        }
        m_connections   = cp.m_connections;
    }

    GDocument::~GDocument()
    {
        for(auto& v : m_data){
            if(!v)
                continue;
            delete v;
        }
        m_data.clear();
    }

    template <typename T> 
    T*    GDocument::_create()
    {
        T* ret =  new T(m_data.size());
        m_data.push_back(ret);
        return ret;
    }

    template <typename T> 
    T*    GDocument::_create(gid_t i)
    {
        _expand(i);
        if(m_data[i])
            return dynamic_cast<T*>(m_data[i]);
        T*  ret = new T(i);
        m_data[i] = ret;
        return ret;
    }

    void                GDocument::_expand(gid_t i)
    {
        if(m_data.size() > i)
            return ;
        m_data.resize(i+1, nullptr);
    }

    void                GDocument::build_connection_tables()
    {
        for(const GBaseData* gb : m_data){
            if(!gb)
                continue;
            
            if(const GEdgeData* ge = dynamic_cast<const GEdgeData*>(gb)){
                GSocketCache*   src = dynamic_cast<GSocketCache*>(data(ge->source));
                GSocketCache*   tgt = dynamic_cast<GSocketCache*>(data(ge->target));
                if(src && tgt){
                    src -> out.edges << ge->id;
                    src -> out.routes[ge->target]   = ge->id;
                    
                    tgt -> in.edges << ge->id;
                    tgt -> in.routes[ge->source]    = ge->id;
                }
                
                m_connections[{ge->source,ge->target}] = ge->id;
            }
            
            if(const GPortData* gp = dynamic_cast<const GPortData*>(gb)){
                if(GPortCache* pc = dynamic_cast<GPortCache*>(data(gp->parent))){
                    pc -> ports << gp -> id;
                }
            }
        }
    }

    GDocumentPtr        GDocument::clone() const
    {
        return new GDocument(*this);
    }

    GEdgeData*          GDocument::connect(gid_t s, gid_t t, const GDocumentConnectOptions& opts) 
    {
        GEdgeData*    ge  = nullptr;
        
        if(opts.unique){
            ge  = const_cast<GEdgeData*>(connection(s, t, opts.resurrect));
            if(ge){
                ge -> deleted   = false;
                return ge;
            }
        }
        
        GSocketCache*   src = dynamic_cast<GSocketCache*>(data(s));
        GSocketCache*   tgt = dynamic_cast<GSocketCache*>(data(t));
        if(src && tgt){
            ge  = edge(CREATE);
            ge -> source    = s;
            ge -> target    = t;
            
            src -> out.edges << ge -> id;
            src -> out.routes[t] = ge -> id;
            
            tgt -> in.edges << ge -> id;
            tgt -> in.routes[s] = ge -> id;

            m_connections[{s,t}] = ge->id;
        }
if(ge){
    graphInfo << "GDocument made connection " << s << " > " << t << " edge> " << ge->id;
} else {
    graphInfo << "GDocument failed to make connection " << s << " > " << t;
}        
        
        return ge;
    }

    bool    GDocument::connected(gid_t s, gid_t t, bool deleted) const
    {
        return static_cast<bool>(connection(s,t,deleted));
    }

    const GEdgeData*    GDocument::connection(gid_t s, gid_t t, bool deleted) const
    {
        gid_t   eid = m_connections.get({s,t},0);
        const GEdgeData* ge = dynamic_cast<const GEdgeData*>(data(eid, deleted));
        if(ge && (deleted || !ge->deleted))
            return ge;
        return nullptr;
    }


    GBaseData*          GDocument::data(gid_t i, bool deleted)
    {
        if(i>=m_data.size())
            return nullptr;
        if(m_data[i] && m_data[i]->deleted && !deleted)
            return nullptr;
        return m_data[i];
    }
    
    const GBaseData*    GDocument::data(gid_t i, bool deleted) const
    {
        if(i>=m_data.size())
            return nullptr;
        if(m_data[i] && m_data[i]->deleted && !deleted)
            return nullptr;
        return m_data[i];
    }
    
    GEdgeData*          GDocument::edge(create_k)
    {
        return _create<GEdgeData>();
    }
    
    GEdgeData*          GDocument::edge(create_k, gid_t i)
    {
        return _create<GEdgeData>(i);
    }

    GEdgeData*          GDocument::edge(gid_t i, bool deleted)
    {
        if(GBaseData*d = data(i,deleted); d->is_edge())
            return static_cast<GEdgeData*>(d);
        return nullptr;
    }
    
    const GEdgeData*    GDocument::edge(gid_t i, bool deleted) const
    {
        if(const GBaseData*d = data(i, deleted); d->is_edge())
            return static_cast<const GEdgeData*>(d);
        return nullptr;
    }

    size_t              GDocument::edges(count_k) const
    {
        size_t  ret = 0;
        edges(FOR, [&](const GEdgeData&){ ++ret; });
        return ret;
    }

    GGraphData*         GDocument::graph(create_k)
    {
        return _create<GGraphData>();
    }
    
    GGraphData*         GDocument::graph(create_k, gid_t i)
    {
        return _create<GGraphData>(i);
    }

    GGraphData*         GDocument::graph(gid_t i, bool deleted)
    {
        if(GBaseData*d = data(i, deleted); d->is_graph())
            return static_cast<GGraphData*>(d);
        return nullptr;
    }
    
    const GGraphData*   GDocument::graph(gid_t i, bool deleted) const
    {
        if(const GBaseData*d = data(i, deleted); d->is_graph())
            return static_cast<const GGraphData*>(d);
        return nullptr;
    }

    size_t              GDocument::graphs(count_k) const
    {
        size_t  ret = 0;
        graphs(FOR, [&](const GGraphData&){ ++ret; });
        return ret;
    }

    bool    GDocument::is_edge(gid_t i, bool deleted) const
    {
        if(const GBaseData* d = data(i,deleted))
            return d -> is_edge();
        return false;
    }
    
    bool    GDocument::is_graph(gid_t i, bool deleted) const
    {
        if(const GBaseData* d = data(i,deleted))
            return d -> is_graph();
        return false;
    }
    
    bool    GDocument::is_line(gid_t i, bool deleted) const
    {
        if(const GBaseData* d = data(i,deleted))
            return d -> is_line();
        return false;
    }
    
    bool    GDocument::is_node(gid_t i, bool deleted) const
    {
        if(const GBaseData* d = data(i,deleted))
            return d -> is_node();
        return false;
    }
    
    bool    GDocument::is_port(gid_t i, bool deleted) const
    {
        if(const GBaseData* d = data(i,deleted))
            return d -> is_port();
        return false;
    }
    
    bool    GDocument::is_shape(gid_t i, bool deleted) const
    {
        if(const GBaseData* d = data(i,deleted))
            return d -> is_shape();
        return false;
    }
    
    bool    GDocument::is_text(gid_t i, bool deleted) const
    {
        if(const GBaseData* d = data(i,deleted))
            return d -> is_text();
        return false;
    }
    
    void    GDocument::kind(set_k, std::string_view v)
    {
        m_kind  = std::string(v);
    }
    
    GLineData*          GDocument::line(create_k)
    {
        return _create<GLineData>();
    }
    
    GLineData*          GDocument::line(create_k, gid_t i)
    {
        return _create<GLineData>(i);
    }

    GLineData*          GDocument::line(gid_t i, bool deleted)
    {
        if(GBaseData*d = data(i, deleted); d->is_line())
            return static_cast<GLineData*>(d);
        return nullptr;
    }
    
    const GLineData*    GDocument::line(gid_t i, bool deleted) const
    {
        if(const GBaseData*d = data(i, deleted); d->is_line())
            return static_cast<const GLineData*>(d);
        return nullptr;
    }

    size_t              GDocument::lines(count_k) const
    {
        size_t  ret = 0;
        lines(FOR, [&](const GLineData&){ ++ret; });
        return ret;
    }


    GNodeData*          GDocument::node(create_k)
    {
        return _create<GNodeData>();
    }
    
    GNodeData*          GDocument::node(create_k, gid_t i)
    {
        return _create<GNodeData>(i);
    }

    GNodeData*          GDocument::node(gid_t i, bool deleted)
    {
        if(GBaseData*d = data(i, deleted); d->is_node())
            return static_cast<GNodeData*>(d);
        return nullptr;
    }
    
    const GNodeData*    GDocument::node(gid_t i, bool deleted) const
    {
        if(const GBaseData*d = data(i, deleted); d->is_node())
            return static_cast<const GNodeData*>(d);
        return nullptr;
    }

    size_t              GDocument::nodes(count_k) const
    {
        size_t  ret = 0;
        nodes(FOR, [&](const GNodeData&){ ++ret; });
        return ret;
    }


    GPortData*          GDocument::port(create_k)
    {
        return _create<GPortData>();
    }
    
    GPortData*          GDocument::port(create_k, gid_t i)
    {
        return _create<GPortData>(i);
    }

    GPortData*          GDocument::port(gid_t i, bool deleted)
    {
        if(GBaseData*d = data(i, deleted); d->is_port())
            return static_cast<GPortData*>(d);
        return nullptr;
    }
    
    const GPortData*    GDocument::port(gid_t i, bool deleted) const
    {
        if(const GBaseData*d = data(i, deleted); d->is_port())
            return static_cast<const GPortData*>(d);
        return nullptr;
    }

    size_t              GDocument::ports(count_k) const
    {
        size_t  ret = 0;
        ports(FOR, [&](const GPortData&){ ++ret; });
        return ret;
    }

    
    void                GDocument::reserve(gid_t i)
    {
        if(m_data.capacity() > i)
            return ;
        //i   = i ^ (i << 1);   // get clever
        m_data.reserve(i+1);
    }

    GShapeData*         GDocument::shape(create_k)
    {
        return _create<GShapeData>();
    }
    
    GShapeData*         GDocument::shape(create_k, gid_t i)
    {
        return _create<GShapeData>(i);
    }

    GShapeData*         GDocument::shape(gid_t i, bool deleted)
    {
        if(GBaseData*d = data(i, deleted); d->is_shape())
            return static_cast<GShapeData*>(d);
        return nullptr;
    }

    const GShapeData*   GDocument::shape(gid_t i, bool deleted) const
    {
        if(const GBaseData*d = data(i, deleted); d->is_shape())
            return static_cast<const GShapeData*>(d);
        return nullptr;
    }

    size_t              GDocument::shapes(count_k) const
    {
        size_t  ret = 0;
        shapes(FOR, [&](const GShapeData&){ ++ret; });
        return ret;
    }


    GTextData*          GDocument::text(create_k)
    {
        return _create<GTextData>();
    }
    
    GTextData*          GDocument::text(create_k, gid_t i)
    {
        return _create<GTextData>(i);
    }
    
    GTextData*          GDocument::text(gid_t i, bool deleted)
    {
        if(GBaseData*d = data(i, deleted); d->is_text())
            return static_cast<GTextData*>(d);
        return nullptr;
    }
    
    const GTextData*    GDocument::text(gid_t i, bool deleted) const
    {
        if(const GBaseData*d = data(i, deleted); d->is_text())
            return static_cast<const GTextData*>(d);
        return nullptr;
    }

    size_t              GDocument::texts(count_k) const
    {
        size_t  ret = 0;
        texts(FOR, [&](const GTextData&){ ++ret; });
        return ret;
    }

    //GViewData*          _view(create_k);
    //GViewData*          _view(gid_t);
    //const GViewData*    _view(gid_t) const;
        
    void GDocument::init_meta()
    {
        auto w = writer<GDocument>();
        w.description("Graph Document (data)");
        w.property("kind", &GDocument::m_kind);
    }
}
