////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Obj.hpp"

#include <yq/art/Doc.hpp>
#include <yq/art/ObjMetaWriter.hpp>

#include <yq/core/Any.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Obj)

namespace yq::art {
    ObjMeta::ObjMeta(std::string_view zName, AbstractMeta& base, const std::source_location& sl) : 
        AbstractMeta(zName, base, sl)
    {
    }

////////////////////////////////////////////////////////////////////////////////

    void Obj::init_meta()
    {
        {
        }
    
        {
            auto w = writer<Obj>();
            w.description("Art object");
        }
    }

    Obj::Obj(Doc& doc) : m_doc(doc), m_id(doc._insert(this))
    {
    }
    
    Obj::~Obj()
    {
    }

    void    Obj::save_to(XmlNode&x) const 
    {
        Abstract::save_to(x);
    }
    
    bool    Obj::load_from(const XmlNode&x) 
    {
        return Abstract::load_from(x);
    }

    //void    Obj::bump()
    //{
        //++m_revision.local;
        //for(ID i=m_id; Obj* p = m_doc.object(i); i = p->parent())
            //++(p->m_revision.all);
        //++m_doc.m_revision.all;
    //}

}
