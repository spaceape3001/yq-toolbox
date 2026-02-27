////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GNodeObject.hpp"
#include "GNodeObjectMetaWriter.hpp"
#include "GNodeTemplate.hpp"
#include <yq/core/Logging.hpp>

#include "GNodeObject.hxx"

YQ_OBJECT_IMPLEMENT(yq::GNodeObject)

namespace yq {
    struct GNodeObjectMeta::Repo {
        MetaLookup<GNodeObjectMeta>   lut;
    };
    
    
    GNodeObjectMeta::Repo& GNodeObjectMeta::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    const GNodeObjectMeta*  GNodeObjectMeta::find(const GNode& gn)
    {
        static auto& _r    = repo();
        
        std::string_view    type    = gn.type();
        if(const GNodeObjectMeta* gm = _r.lut.find(type))
            return gm;
        GNodeTemplateCPtr p = GNodeTemplate::IO::load(type);
        if(!p)
            return nullptr;
        return _r.lut.find(p->meta);
    }
    
    const GNodeObjectMeta* GNodeObjectMeta::find(std::string_view sv)
    {
        return repo().lut.find(sv);
    }
    

    GNodeObjectMeta::GNodeObjectMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, base, sl)
    {
        repo().lut << this;
    }

    void        GNodeObjectMeta::g_write(GNodeTemplate& gnt) const
    {
        gnt.category        = std::string(category());
        gnt.color.dark      = m_colorDark;
        gnt.color.light     = m_colorLight;
        gnt.description     = std::string(description());
        
        for(auto& itr : icons())
            gnt.icons[itr.first]    = std::string(itr.second);
        
        gnt.label           = std::string(label());
        gnt.meta            = std::string(name());
        
        //  TODO PINS
        
        gnt.symbol          = m_symbol;
    }

    void        GNodeObjectMeta::g_write_key(GNodeTemplate& gnt) const
    {
        gnt.set_key(stem());
    }
    
    void        GNodeObjectMeta::g_write_url(GNodeTemplate&gnt) const
    {
        if(const char* sPath   = app_path()){
            gnt.set_url({.scheme="app", .path=sPath, .query=std::format("key={}", stem())});
        }
    }

    Url         GNodeObjectMeta::app_url() const
    {
        if(const char* sPath   = app_path()){
            return Url{.scheme="app", .path=sPath, .query=std::format("key={}", stem())};
        }
        return {};
    }

    GNodeTemplatePtr    GNodeObjectMeta::make_template() const
    {
        GNodeTemplatePtr    ret = new GNodeTemplate;
        g_write_url(*ret);
        g_write_key(*ret);
        g_write(*ret);
        
        return ret;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////

    GNodeObject::GNodeObject()
    {
    }
    
    GNodeObject::~GNodeObject()
    {
    }

    std::error_code GNodeObject::initialize(const InitAPI& api)
    {
        return {};
    }
    
    std::error_code GNodeObject::_initialize(const InitAPI& api)
    {
        if(m_node)
            return create_error<"GNodeObject already initialized">();
    
        if(!api.node)
            return create_error<"GNodeObject cannot initialize to null node">();
    
        // meta stuff and the like...
        
        m_node  = api.node;
        
        if(std::error_code ec = initialize(api); ec != std::error_code()){
            m_node  = {};
            return ec;
        }
        
        //  any thing more....?
        
        return {};
    }

    void GNodeObject::init_meta()
    {
        auto w = writer<GNodeObject>();
        w.description("Abstract Node Object");
        w.abstract();
    }
}
