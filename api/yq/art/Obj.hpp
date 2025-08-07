////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/forward.hpp>
#include <yq/art/keywords.hpp>
#include <yq/art/Abstract.hpp>


namespace yq::art {
    class ObjMeta : public AbstractMeta {
    public:
        template <typename> class Writer;
        ObjMeta(std::string_view zName, AbstractMeta& base, const std::source_location& sl=std::source_location::current());
        
        virtual Obj*        create(Doc&) const = 0;
        
        
    private:
    };

    template <typename> class ObjFixer;

    class Obj : public Abstract {
        YQ_OBJECT_META(ObjMeta)
        YQ_OBJECT_FIXER(ObjFixer)
        YQ_OBJECT_DECLARE(Obj, Abstract)
    public:

        static void init_meta();

        //! How many dimensions this object is... note, 3D objects *can* live within 2D documents
        //! Though 2D will need to be hosted by a "surface" in 3D
        virtual uint8_t dimensions(count_k) const { return 0; }
    
        Obj(Doc&);
        Obj(Doc&, const Obj&); // clones...
        ~Obj();
        
        ID                      id() const { return m_id; }
        ID                      parent() const { return m_parent; }
        std::span<const ID>     children() const { return m_children; }
        
        Doc&                    doc() { return m_doc; }
        const Doc&              doc() const { return m_doc; }
    
    protected:
        
        virtual void    save_to(XmlNode&) const override;
        virtual bool    load_from(const XmlNode&) override;
 
    private:
        Doc&                    m_doc;
        const ID                m_id;
        ID                      m_parent;
        std::vector<ID>         m_children;
        
    };
}
