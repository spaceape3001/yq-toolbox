////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GNode.hpp"
#include "GNodeData.hpp"
#include "GPort.hpp"
#include "GPortData.hpp"
#include "GDocument.hxx"
#include <yq/symbol/Pin.hpp>
#include <yq/text/match.hpp>

namespace yq {
    GNode::GNode() = default;
    GNode::GNode(const GNode&) = default;
    GNode::GNode(GNode&&) = default;
    GNode::GNode(GDocumentPtr doc, gid_t i) : GBase(doc, i) {}
    GNode::~GNode() = default;
    GNode& GNode::operator=(const GNode&) = default;
    GNode& GNode::operator=(GNode&&) = default;

    GNode::operator bool() const
    {
        return static_cast<bool>(data());
    }

    GPortData* GNode::_port(create_k, const std::string& key)
    {
        GNodeData*  gn  = data();
        if(!gn)
            return nullptr;

        GPortData*gp = m_doc -> port(CREATE);
        gp->key  = key;
        gp->parent   = m_id;
        gn -> ports << gp->id;
        return gp;
    }

    GNodeData*          GNode::data()
    {
        if(m_doc)
            return m_doc -> node(m_id);
        return nullptr;
    }
    
    const GNodeData*    GNode::data() const
    {
        if(m_doc)
            return m_doc -> node(m_id);
        return nullptr;
    }

    std::vector<GEdge>  GNode::edges(const GNodeEdgeSearchOptions& opts) const
    {
        std::vector<GEdge>  ret;
        if(const GNodeData* gn  = data()){
            for(gid_t g : gn->in.edges){
                if(m_doc->is_edge(g))
                    ret.push_back(GEdge(m_doc, g));
            }
            for(gid_t g : gn->out.edges){
                if(m_doc->is_edge(g))
                    ret.push_back(GEdge(m_doc, g));
            }
            if(opts.ports){
                for(gid_t p : gn->ports){
                    if(const GPortData* gp = m_doc->port(p)){
                        if(gp->input){
                            for(gid_t g : gp->in.edges){
                                if(m_doc->is_edge(g))
                                    ret.push_back(GEdge(m_doc, g));
                            }
                        }
                        if(gp->output){
                            for(gid_t g : gp->out.edges){
                                if(m_doc->is_edge(g))
                                    ret.push_back(GEdge(m_doc, g));
                            }
                        }
                    }
                }
            }
        }
        return ret;
    }

    std::vector<GEdge>  GNode::inbound(const GNodeEdgeSearchOptions& opts) const
    {
        std::vector<GEdge>  ret;
        if(const GNodeData* gn  = data()){
            for(gid_t g : gn->in.edges){
                if(m_doc->is_edge(g))
                    ret.push_back(GEdge(m_doc, g));
            }
            if(opts.ports){
                for(gid_t p : gn->ports){
                    if(const GPortData* gp = m_doc->port(p); gp && gp->input){
                        for(gid_t g : gp->in.edges){
                            if(m_doc->is_edge(g))
                                ret.push_back(GEdge(m_doc, g));
                        }
                    }
                }
            }
        }
        return ret;
    }
    
    std::vector<GEdge>  GNode::outbound(const GNodeEdgeSearchOptions& opts) const
    {
        std::vector<GEdge>  ret;
        if(const GNodeData* gn  = data()){
            for(gid_t g : gn->out.edges){
                if(m_doc->is_edge(g))
                    ret.push_back(GEdge(m_doc, g));
            }
            if(opts.ports){
                for(gid_t p : gn->ports){
                    if(const GPortData* gp = m_doc->port(p); gp && gp->output){
                        for(gid_t g : gp->out.edges){
                            if(m_doc->is_edge(g))
                                ret.push_back(GEdge(m_doc, g));
                        }
                    }
                }
            }
        }
        return ret;
    }

    GPort   GNode::port(const std::string& key) const
    {
        const GNodeData*  gn  = data();
        if(!gn)
            return {};
        for(gid_t p : gn -> ports){
            if(const GPortData* gp = m_doc->port(p)){
                if(is_similar(key, gp->key))
                    return GPort(m_doc, p);
            }
        }
        return {};
    }
    
    GPort   GNode::port(in_k, const std::string& key) const
    {
        const GNodeData*  gn  = data();
        if(!gn)
            return {};
        for(gid_t p : gn -> ports){
            if(const GPortData* gp = m_doc->port(p)){
                if(gp -> input && is_similar(key, gp->key))
                    return GPort(m_doc, p);
            }
        }
        return {};
    }
    
    GPort   GNode::port(out_k, const std::string& key) const
    {
        const GNodeData*  gn  = data();
        if(!gn)
            return {};
        for(gid_t p : gn -> ports){
            if(const GPortData* gp = m_doc->port(p)){
                if(gp -> output && is_similar(key, gp->key))
                    return GPort(m_doc, p);
            }
        }
        return {};
    }

    GPort   GNode::port(create_k, const std::string& key)
    {
        if(GPortData* gp = _port(CREATE, key))
            return GPort(m_doc, gp->id);
        return {};
    }

    GPort               GNode::port(create_k, const symbol::PinBase&pb, const std::string& key)
    {
        if(GPortData* gp = _port(CREATE, key)){
            switch(pb.flow){
            case symbol::PinFlow::Bi:
                gp -> input = true;
                gp -> output = true;
                break;
            case symbol::PinFlow::In:
                gp -> input = true;
                gp -> output = false;
                break;
            case symbol::PinFlow::Out:
                gp -> input = false;
                gp -> output    = true;
                break;
            case symbol::PinFlow::NC:
                gp -> input = false;
                gp -> output = false;
                break;
            }
        
            return GPort(m_doc, gp->id);
        }
        return {};
    }

    std::vector<GPort>  GNode::ports() const
    {
        std::vector<GPort>  ret;
        if(const GNodeData* gn = data()){
            for(gid_t g : gn->ports){
                if(m_doc -> is_port(g))
                    ret.push_back(GPort(m_doc, g));
            }
        }
        return ret;
    }
    
    size_t              GNode::ports(count_k) const
    {
        size_t ret = 0;
        if(const GNodeData* gn = data()){
            for(gid_t g : gn->ports){
                if(m_doc -> is_port(g))
                    ++ret;
            }
        }
        return ret;
    }

    Vector2D  GNode::position() const
    {
        if(const GNodeData* gn = data())
            return gn -> position;
        return NAN;
    }
    
    void      GNode::position(set_k, const Vector2D&v)
    {
        if(GNodeData* gn = data())
            gn -> position  = v;
    }

    Size2D  GNode::size() const
    {
        if(const GNodeData* gn = data())
            return gn -> size;
        return NAN;
    }
    
    void    GNode::size(set_k, const Size2D&v)
    {
        if(GNodeData* gn = data())
            gn -> size  = v;
    }
    
    symbol::TransformMode    GNode::transform() const
    {
        if(const GNodeData* gn = data())
            return gn -> transform;
        return symbol::TransformMode();
    }
    
    void                    GNode::transform(set_k, symbol::TransformMode v)
    {
        if(GNodeData* gn = data())
            gn -> transform  = v;
    }

    std::string_view    GNode::type() const
    {
        if(const GNodeData* gn = data()){
            return gn -> type;
        } else
            return {};
    }

    ////////////////////////////////////////////////////////////////////////////

    GNodeData::GNodeData(gid_t _id) : GBaseData(_id) {}
    
    GNodeData::GNodeData(const GNodeData& cp )  = default;
    GNodeData::~GNodeData() = default;
    
    GBaseData*  GNodeData::clone() const 
    { 
        return new GNodeData(*this); 
    }
}
