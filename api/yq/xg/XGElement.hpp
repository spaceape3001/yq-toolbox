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
#include <yq/graph/GNode.hpp>
#include <yq/graph/GNodeObject.hpp>
#include <yq/xg/types.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/xg/XGNodeType.hpp>
//#include <yq/typedef/xg_manifest.hpp>
#include <yq/typedef/g_node_template.hpp>
#include <yq/typedef/g_meta_graph.hpp>

namespace yq {
    class XGUnit;
    struct XGDocNode;
    class GNode;
    struct XGUnitOptions;
    class XGLogic;
    class XGRuntime;
    
    class XGElementMeta : public GNodeObjectMeta {
    public:
        template <typename> class Writer;
        
        XGElementMeta(std::string_view zName, GNodeObjectMeta& base, const std::source_location& sl=std::source_location::current());
        
        const RGBA4F&       bgcolor() const { return m_bgcolor; }
        const RGBA4F&       color() const { return m_color; }
        
        XGNodeType          node_type() const { return m_nodeType; }
        
        std::string_view    symbol_spec() const { return m_symbol; }
        
        //! Default priority for elements of this type
        double              priority() const { return m_priority; }
        
        //! All XG Element meta
        static const std::vector<const XGElementMeta*>& all();
        
        //! Finds the specified XG element meta by name.  Key & Stem lookups are used
        static const XGElementMeta* find(std::string_view);
        
        //! Create a meta graph based on all registered XG elements
        static GMetaGraphPtr    create_manifest();
        
        //GNodeTemplatePtr        create_meta_node() const;
        
        //! used by the Graph meta
        virtual const char* app_path() const override;
        
    private:
        std::string_view    m_symbol;
        RGBA4F              m_bgcolor       = kInvalidColor;
        RGBA4F              m_color         = kInvalidColor;
        XGNodeType          m_nodeType      = XGNodeType::Unspecified;
        double              m_priority      = NaN;
        
        struct Repo;
        static Repo&    repo();
    };

    class XGElement : public GNodeObject, public UniqueID {
        YQ_OBJECT_META(XGElementMeta)
        YQ_OBJECT_DECLARE(XGElement, GNodeObject)
    public:
    
        virtual xg_result_t         execute(XGContext&);    // extend this one
        
        gid_t                       id() const;
        double                      priority() const;
        
        //! Might want some wait condition handling...  (will, if it becomes an issue)
        
        static void init_meta();
        
    protected:
        XGElement();
        virtual ~XGElement();
    
        /*! \brief Initializes the element from the node
        
            This will be called *AFTER* all meta-capable properties
            are set from the node's data.  (Thus, should hopefully 
            be minimal.)
        */
        virtual std::error_code     initialize(const InitAPI&) override;
        
        //const auto& logic_results() const { return m_results; }
        //const auto& logic_nodes() const { return m_logics; }

    private:
        friend class XGUnit;
        friend class XGRuntime;
        //friend class XGLogic;
        
        //virtual xg_result_t         execute_(XGContext&, const XGUnitOptions&);
        
        //std::error_code             _initialize(const GNode&);
        
        //  some attribute overrides (here and/or in the graph node object)
        
        std::vector<xg_execute_t>   m_next;     //< General "NEXT"
        //std::vector<xg_execute_t>   m_logics;   //< Conditional connections (TBD)
        //std::vector<xg_result_t>    m_results;  //< Logical results
        double                      m_priority      = NaN;                     // will be used
    };
}
