////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Abstract.hpp"
#include "AbstractMetaWriter.hpp"

#include <yq/tags.hpp>
#include <yq/container/Stack.hpp>
#include <yq/core/Any.hpp>
#include <yq/xml/XmlAny.hpp>
#include <yq/xml/XmlUtils.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Abstract)

namespace yq::art {
    AbstractMeta::AbstractMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, base, sl)
    {
    }

    const AbstractMeta::Handler* AbstractMeta::handler(const Meta& m) const
    {
        return m_handlers.get(m.id(), nullptr);
    }

    bool    AbstractMeta::support_dimension(uint8_t n) const
    {
        if(n>7)
            return false;
        return static_cast<bool>(m_dimension.support & (1<<n));
    }

////////////////////////////////////////////////////////////////////////////////

    void    Abstract::handle(const Abstract* abs, const AbstractMeta* am, const Meta* m, const void*data, unsigned opts) 
    {
        struct Context {
            Abstract*           abstract;
            const AbstractMeta* absm;
            const Meta*         meta;
            void*               data;
            unsigned            options;
        };
        
        static thread_local Stack<Context*>   s_save;
        
        Context     storage;
        Context*    local   = nullptr;

        if(opts & GoBase){
            if(s_save.empty())
                return;
            local   = s_save.top();
            local->absm  = dynamic_cast<const AbstractMeta*>(local -> absm -> base());
        } else {
            if(!am || !m || !data)
                return;
            if(!abs && !(opts|NullAbstract))
                return;
            storage = { const_cast<Abstract*>(abs), am, m, const_cast<void*>(data), opts };
            local   = &storage;
        }
        
        for(; local->absm; local->absm = dynamic_cast<const AbstractMeta*>(local -> absm -> base())){
            const AbstractMeta::Handler*   dg  = local->absm->handler(*(local->meta));
            if(!dg)
                continue;
            if(dg->m_abs && !(local->options&ConstAbstract))
                continue;
            if(dg->m_data && !(local->options&ConstData))
                continue;
            if(dg->m_null ? static_cast<bool>(local->abstract) : !(local->abstract))
                continue;
            if(!(opts & GoBase))
                s_save << local;
            dg->invoke(local->abstract, local->data);
            if(!(opts & GoBase))
                s_save.pop();
        }
    }
    
    void Abstract::handle(base_k)
    {
        handle(nullptr,nullptr,nullptr,nullptr,GoBase);
    }
    
    void Abstract::init_meta()
    {
        auto w = writer<Abstract>();
        w.description("Abstract (base) class");
        w.property("key", &Abstract::m_key);        // note, this is *NOT* marked save as it's independently handled
    }
    
    //  ....................

    Abstract::Abstract()
    {
    }
    
    Abstract::~Abstract()
    {
    }
    
    void    Abstract::set_key(const std::string& v)
    {
        m_key   = v;
    }

    void    Abstract::save_to(XmlNode& x) const
    {
        if(!m_key.empty())
            write_attribute(x, "key",m_key);
            
        for(auto& a : m_attributes){
            XmlNode&    xa  = *x.create_element("attr");
            write_attribute(xa, "k", a.first);
            write_attribute(xa, "t", a.second.type().name());
            write_xml_any(xa, a.second);
        }
        
        for(const PropertyMeta* pm : metaInfo().properties(ALL).all){
            if(!pm) [[unlikely]]
                continue;
            if(pm->is_static())
                continue;
            if(!(pm->tagged(kTag_Save)))
                continue;

            const TypeMeta& pt  = pm->type();
            any_x value_x  = pm->get(this);
            if(!value_x)
                continue;
            Any value   = std::move(*value_x);
            XmlNode&    xp  = *x.create_element("prop");
            write_attribute(xp, "k", pm->name());
            if(value.type().id() != pt.id())
                write_attribute(xp, "t", value.type().name());
            write_xml_any(xp, value);
        }
    }
    
    bool    Abstract::load_from(const XmlNode& xn)
    {
        bool    success = true;
        m_key   = read_attribute(xn, "key", x_string);
        for(const XmlNode* a = xn.first_node("attr"); a; a = a->next_sibling("attr")){
            std::string k   = read_attribute(*a, "k", x_string);
            std::string t   = read_attribute(*a, "t", x_string);
            const TypeMeta* tm  = TypeMeta::find(t);
            if(!tm){
                tm  = &meta<std::string>();
                success = false;
            }
            Any v(tm);
            if(read_xml_any(*a, v) != std::error_code())
                success = false;
            m_attributes[k] = std::move(v);
        }
        
        for(const XmlNode* p = xn.first_node("prop"); p; p = p -> next_sibling("prop")){
            std::string k   = read_attribute(*p, "k", x_string);
            std::string t   = read_attribute(*p, "t", x_string);
            
            const PropertyMeta*pm   = metaInfo().properties(ALL).find(k);
            if(!pm)
                continue;
            if(!pm->tagged(kTag_Save))
                continue;
            if(pm->is_static())
                continue;
            
            bool    as_string   = false;
            
            const TypeMeta* tm  = nullptr;
            if(t.empty()){
                tm  = &pm->type();
            } else {
                tm  = TypeMeta::find(t);
                if(!tm)
                    as_string   = true;
            }
            
            if(as_string){
                success = false;
                pm -> set(this, p->value());
            } else {
                Any v(tm);
                if(read_xml_any(*p, v) != std::error_code())
                    success = false;
                pm -> set(this, v);
            }
        }
        
        return success;
    }

}
