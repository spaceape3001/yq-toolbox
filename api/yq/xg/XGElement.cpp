////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGElement.hpp"
#include "XGElementMetaWriter.hpp"
#include "XGDocNode.hpp"
//#include "XGManifest.hpp"
//#include "XGNodeMeta.hpp"
#include <yq/graph/GMetaGraph.hpp>
#include <yq/graph/GNodeTemplate.hpp>
#include <yq/resource/Resource.hxx>
#include <format>

#include <yq/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::XGNodeType)
YQ_OBJECT_IMPLEMENT(yq::XGElement)

namespace yq {
    static constexpr const char *szXGElementMetaPath    = "/xg/element/meta";
    static constexpr const char *szXGMetaGraphPath      = "/xg/metagraph";

    static GNodeTemplatePtr    makeMetaNode(const UrlView& url, const ResourceLoadAPI&)
    {
        std::string     name    = first_query_parameter(url.query, "key");
        if(name.empty())
            return {};
        const XGElementMeta* em = XGElementMeta::find(name);
        if(!em)
            return {};
        return em->make_template();
    }
    
    static GMetaGraphPtr        makeXGMetaGraph(const UrlView&, const ResourceLoadAPI&)
    {
        return XGElementMeta::create_manifest();
    }

    void XGElement::init_meta()
    {
        {
            auto w = writer<XGElement>();
            w.abstract();
            w.description("Executive Graph Element");
            GNodeTemplate::IO::add_loader({.yqpath=szXGElementMetaPath}, makeMetaNode);
            GMetaGraph::IO::add_loader({.yqpath=szXGMetaGraphPath}, makeXGMetaGraph);
            GMetaGraph::kind_define("executive", { .scheme="app", .path=szXGMetaGraphPath});
        }
        {
            auto w = writer<XGNodeType>();
            w.description("Executive Graph Node Type");
        }
    }

    XGElement::XGElement()
    {
    }
    
    XGElement::~XGElement()
    {
    }

    //std::error_code XGElement::_initialize(const GNode& gn)
    //{
        ////  meta stuff here
        
        //return initialize(gn);
    //}

    //xg_result_t    XGElement::execute_(XGContext&ctx, const XGUnitOptions&)
    //{
        //return execute(ctx);
    //}

    xg_result_t    XGElement::execute(XGContext&)
    {
        return {};
    }

    gid_t            XGElement::id() const
    {
        return m_node.id();
    }

    std::error_code  XGElement::initialize(const InitAPI&dn)
    {
        //m_nodeType  = dn.node_type;
        //m_priority  = dn.priority;
        return {};
    }

    double          XGElement::priority() const
    {
        if(!is_nan(m_priority))
            return m_priority;
        return metaInfo().priority();
    }

    ////////////////////////////////////////////////////////////////////////////

    struct XGElementMeta::Repo {
        MetaLookup<XGElementMeta>   elements;
    };
    
    const std::vector<const XGElementMeta*>& XGElementMeta::all()
    {
        return repo().elements.all;
    }

    const char* XGElementMeta::app_path() const 
    {
        return szXGElementMetaPath;
    }
    
    #if 0

    GNodeTemplatePtr        XGElementMeta::create_meta_node() const
    {
        GNodeTemplatePtr    ret = new GNodeTemplate;
        ret -> set_url({ .scheme="app", .path=szXGElementMetaPath, .query=std::format("key={}", stem())});
        ret -> set_key(stem());
        ret -> category     = std::string(category());
        //ret -> color.dark
        //ret -> color.light
        ret -> description  = std::string(description());
        ret -> label        = label();

        //auto ux             = to_url(symbol());
        
        //ret -> symbol       = to_
        
        return ret;
    }
    #endif

    GMetaGraphPtr   XGElementMeta::create_manifest()
    {
        GMetaGraphPtr ret = new GMetaGraph;
        for(const XGElementMeta* xm : repo().elements.all){
            if(!xm) [[unlikely]] /* VERY HIGHLY unlikely */
                continue;
            if(xm -> is_abstract())
                continue;
                
            if(auto x  = xm -> make_template())
                ret -> add(x);
            
            #if 0
            ret -> m_nodes.push_back(xm->make_template());
            
            XGNodeMeta  node;
            node.bgcolor        = xm -> bgcolor();
            node.category       = std::string(xm -> category());
            node.color          = xm -> color();
            node.description    = std::string(xm -> description());
            for(auto& itr : xm -> icons())
                node.icons[itr.first]   = std::string(itr.second);
            node.label          = std::string(xm -> label());
            node.node_type      = xm -> node_type();
            node.spec_type      = XGSpecType::Meta;
            node.spec_data      = std::string(xm -> name());
            node.symbol         = std::string(xm -> symbol_spec());
            ret -> m_nodes.push_back(std::move(node));
            #endif
        }
        return ret;
    }

    const XGElementMeta* XGElementMeta::find(std::string_view k)
    {
        return repo().elements.find(k);
    }

    XGElementMeta::Repo&    XGElementMeta::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    XGElementMeta::XGElementMeta(std::string_view zName, GNodeObjectMeta& base, const std::source_location& sl) : 
        GNodeObjectMeta(zName, base, sl)
    {
        repo().elements << this;
    }
}
