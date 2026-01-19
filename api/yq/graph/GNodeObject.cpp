////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GNodeObject.hpp"
#include "GNodeObjectMetaWriter.hpp"
#include "GNodeTemplate.hpp"

YQ_OBJECT_IMPLEMENT(yq::GNodeObject)

namespace yq {
    GNodeObjectMeta::GNodeObjectMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, base, sl)
    {
    }

    void        GNodeObjectMeta::g_write(GNodeTemplate& gnt) const
    {
        gnt.category        = std::string(category());
        gnt.color.dark      = m_colorDark;
        gnt.color.light     = m_colorLight;
        gnt.description     = std::string(description());
        
        for(auto& itr : icons()){
            auto ux     = to_url_view(itr.second);
            if(!ux.good)
                continue;
            gnt.icons[itr.first]    = copy(ux.value);
        }
        
        gnt.label           = std::string(label());
        
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
    
    void GNodeObject::init_meta()
    {
        auto w = writer<GNodeObject>();
        w.description("Abstract Node Object");
        w.abstract();
    }
}
