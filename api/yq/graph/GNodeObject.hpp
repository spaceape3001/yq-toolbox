////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGB.hpp>
#include <yq/color/RGBA.hpp>
#include <yq/core/Object.hpp>
#include <yq/net/Url.hpp>
#include <yq/typedef/color.hpp>
#include <yq/typedef/g_node_template.hpp>
#include <yq/graph/GNode.hpp>

namespace yq {
    class GraphEngine;
    class GNodeObject;
    
    class GNodeObjectMeta : public ObjectMeta {
    public:
    
        template <typename> struct Writer;
        GNodeObjectMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());
        
        virtual const char* app_path() const { return nullptr; }
        
        const color_spec&   color_dark() const { return m_colorDark; }
        const color_spec&   color_light() const { return m_colorLight; }
        const std::string&  symbol() const { return m_symbol; }
        
        virtual Url         app_url() const;
        
        /*! \brief Creates a node template from the node's description
        
            If necessary, override.  If you do, the url/key need to be
            set manually.  (the write key/url do this, with the url one dependent on
            the app path not returning nullptr)
        */
        virtual GNodeTemplatePtr    make_template() const;
        
        static const GNodeObjectMeta*  find(std::string_view);
        static const GNodeObjectMeta*  find(const GNode&);
        
    protected:
    
        // writes all it can *EXCEPT* the URL/KEY
        void        g_write(GNodeTemplate&) const;
        void        g_write_key(GNodeTemplate&) const;
        void        g_write_url(GNodeTemplate&) const;
        
    private:
        color_spec      m_colorDark, m_colorLight;
        std::string     m_symbol;
        
        // TODO: Pins
        // TODO: Dynamic pins (based on function/string)
        
        struct Repo;
        static Repo& repo();
    };

    /*! \brief Root for Nodes
    
        "Graph" nodes that have code behind them.
        
        \note Not required for the graph editor to work, still, nice to give 
        the users some code points to execute
    */
    class GNodeObject : public Object {
        YQ_OBJECT_META(GNodeObjectMeta)
        YQ_OBJECT_DECLARE(GNodeObject, Object)
    public:
    
        GNodeObject();
        virtual ~GNodeObject();
        
        static void init_meta();
        
    protected:
        struct InitAPI;
        friend class GraphEngine;
        
        GNode       m_node;
        
        virtual std::error_code initialize(const InitAPI&);
        
        //  does meta stuff (as necessary)
        std::error_code     _initialize(const InitAPI&);
    };
}
