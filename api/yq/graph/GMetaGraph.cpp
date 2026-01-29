////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GMetaGraph.hpp"
#include "GNodeTemplate.hpp"
#include <yq/resource/ResourceLibraryMetaWriter.hpp>

YQ_RESOURCE_IMPLEMENT(yq::GMetaGraph)

namespace yq {
    struct GMetaGraph::Repo {
        std::map<std::string, Url, IgCase>  kinds;
    };

    void GMetaGraph::kind_define(const std::string& s, const Url& u)
    {
        if(Meta::thread_safe_write())
            repo().kinds[s]    = u;
    }
    
    Url  GMetaGraph::kind_url(const std::string&s)
    {
        auto& r = repo();
        if(auto x = r.kinds.find(s); x != r.kinds.end())
            return x->second;
        return {};
    }
    
    GMetaGraph::Repo& GMetaGraph::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    GMetaGraph::GMetaGraph()
    {
    }
    
    GMetaGraph::~GMetaGraph()
    {
    }
        
    size_t        GMetaGraph::data_size() const 
    {
        return 0;
    }

    void    GMetaGraph::post_add(ResourcePtr rp) 
    {
        if(const GNodeTemplate* nt = dynamic_cast<const GNodeTemplate*>(rp.ptr()))
            m_nodes.push_back(nt);
    }
        
    void GMetaGraph::init_meta()
    {
        auto w = writer<GMetaGraph>();
        w.description("Library of Creatable Nodes");
        w.resource<GNodeTemplate>();
    }
}

