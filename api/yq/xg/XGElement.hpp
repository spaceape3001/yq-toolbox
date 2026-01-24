////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGBA.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/Tristate.hpp>
#include <yq/core/UniqueID.hpp>
#include <yq/graph/GNodeObject.hpp>
#include <yq/xg/types.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/xg/XGNodeType.hpp>
//#include <yq/typedef/xg_manifest.hpp>
#include <yq/typedef/g_node_template.hpp>
#include <yq/typedef/g_meta_graph.hpp>

namespace yq {
    class XGRuntime;
    struct XGDocNode;
    
    
    class XGElementMeta : public GNodeObjectMeta {
    public:
        template <typename> class Writer;
        
        XGElementMeta(std::string_view zName, GNodeObjectMeta& base, const std::source_location& sl=std::source_location::current());
        
        const RGBA4F&       bgcolor() const { return m_bgcolor; }
        const RGBA4F&       color() const { return m_color; }
        
        XGNodeType          node_type() const { return m_nodeType; }
        
        std::string_view    symbol_spec() const { return m_symbol; }
        
        //! Lets user know this is a *decision* type of element
        float               priority() const { return m_priority; }
        
        static const std::vector<const XGElementMeta*>& all();
        
        static const XGElementMeta* find(std::string_view);
        static const XGElementMeta* find_stem(std::string_view);
        
        static GMetaGraphPtr    create_manifest();
        
        //GNodeTemplatePtr        create_meta_node() const;
        
    private:
        std::string_view    m_symbol;
        RGBA4F              m_bgcolor       = kInvalidColor;
        RGBA4F              m_color         = kInvalidColor;
        XGNodeType          m_nodeType      = XGNodeType::Unspecified;
        float               m_priority      = NaNf;
        
        struct Repo;
        static Repo&    repo();
    };

    class XGElement : public GNodeObject, public UniqueID {
        YQ_OBJECT_META(XGElementMeta)
        YQ_OBJECT_DECLARE(XGElement, GNodeObject)
    public:
    
        virtual xg_result_t         execute(XGContext&);
        
        // Type of the node
        XGNodeType                  node_type() const;
        
        xg_priority_t               priority() const;
        
        //! Might want some wait condition handling...  (will, if it becomes an issue)
        
        static void init_meta();
        
    protected:
        XGElement();
        virtual ~XGElement();
    
        virtual bool    initialize(const XGDocNode&);
    
    private:
        friend class XGRuntime;
        
        std::vector<xg_execute_t>   m_next;
        XGNodeType                  m_nodeType      = XGNodeType::Unspecified;
        xg_priority_t               m_priority      = NaNf;
    };
}
