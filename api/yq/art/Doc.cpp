////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Doc.hpp"

#include <yq/art/tags.hpp>
#include <yq/art/DocMetaWriter.hpp>
#include <yq/art/Obj.hpp>

#include <yq/core/Any.hpp>
#include <yq/meta/Init.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Doc)
YQ_TYPE_IMPLEMENT(yq::art::ID)
YQ_TYPE_IMPLEMENT(yq::art::Key)
YQ_TYPE_IMPLEMENT(yq::art::Reference)

namespace yq::art {

    DocMeta::DocMeta(std::string_view zName, AbstractMeta& base, const std::source_location& sl) :
        AbstractMeta(zName, base, sl)
    {
    }

////////////////////////////////////////////////////////////////////////////////

    void Doc::init_meta()
    {
        {
            auto w  = writer<ID>();
            w.description("Cross reference identifier");
            w.casts<Reference>();
        }
        
        {
            auto w = writer<Key>();
            w.description("User defined key");
            w.casts<Reference>();
        }
        
        {
            auto w = writer<Reference>();
            w.description("Reference to something else");
        }

        {
            auto w = writer<Doc>();
            w.description("Art document");
            w.property("title", &Doc::m_title);
        }
    }

    Doc::Doc()
    {
        m_objects.push_back(nullptr);
    }
    
    Doc::~Doc()
    {
        for(auto& obj : m_zombies){
            if(obj){
                delete obj;
                obj     = nullptr;
            }
        }
        m_zombies.clear();

        for(auto& obj : m_objects){
            if(obj){
                delete obj;
                obj     = nullptr;
            }
        }
        m_objects.clear();
    }

    ID    Doc::_insert(Obj* obj)
    {
        if(!obj)
            return {};
            
        if(m_load){                     // used during loading
            m_objects[m_load]   = obj;
            return { m_load };
        }    
        
        id_t    n   = m_objects.size();
        m_objects.push_back(obj);
        return { n };
    }

    //void       Doc::bump()
    //{
        //++ m_revision.all;
        //++ m_revision.local;
    //}

    Obj*       Doc::object(ID i)
    {
        if(i.id>=m_objects.size())
            return nullptr;
        return m_objects[i.id];
    }
    
    const Obj*  Doc::object(ID i) const
    {
        if(i.id>=m_objects.size())
            return nullptr;
        return m_objects[i.id];
    }
    
    void        Doc::set_title(std::string_view t)
    {
        m_title = std::string(t);
        //bump();
    }

    bool        Doc::valid(ID i) const
    {
        return (i.id<m_objects.size()) && m_objects[i.id];
    }
    
////////////////////////////////////////////////////////////////////////////////
//  XML I/O

    void        Doc::save_to(XmlNode&x) const
    {
        Abstract::save_to(x);
    }
    
    bool        Doc::load_from(const XmlNode&x) 
    {
        bool success    =  Abstract::load_from(x);
        return success;
    }
}
