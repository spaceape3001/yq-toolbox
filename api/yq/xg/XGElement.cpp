////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGElement.hpp"
#include "XGElementMetaWriter.hpp"
#include "XGDocNode.hpp"
#include "XGManifest.hpp"
#include "XGNodeMeta.hpp"

YQ_OBJECT_IMPLEMENT(yq::XGElement)

namespace yq {
    void XGElement::init_meta()
    {
        auto w = writer<XGElement>();
        w.description("Executive Graph Element");
    }

    XGElement::XGElement()
    {
    }
    
    XGElement::~XGElement()
    {
    }

    xg_result_t    XGElement::execute(XGContext&)
    {
        return {};
    }

    bool    XGElement::initialize(const XGDocNode&dn)
    {
        m_nodeType  = dn.node_type;
        m_priority  = dn.priority;
        return true;
    }
    
    XGNodeType  XGElement::node_type() const
    {
        if(m_nodeType != XGNodeType::Unspecified)
            return m_nodeType;
        return metaInfo().node_type();
    }

    ////////////////////////////////////////////////////////////////////////////

    struct XGElementMeta::Repo {
        MetaLookup<XGElementMeta>   elements;
    };
    
    const std::vector<const XGElementMeta*>& XGElementMeta::all()
    {
        return repo().elements.all;
    }

    XGManifestPtr   XGElementMeta::create_manifest()
    {
        XGManifestPtr ret = new XGManifest;
        for(const XGElementMeta* xm : repo().elements.all){
            if(!xm) [[unlikely]] /* VERY HIGHLY unlikely */
                continue;
            if(xm -> is_abstract())
                continue;
            
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
        }
        return ret;
    }

    XGElementMeta::Repo&    XGElementMeta::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    XGElementMeta::XGElementMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) : 
        ObjectMeta(zName, base, sl)
    {
        repo().elements << this;
    }
}
