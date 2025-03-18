////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/AllLocal.hpp>
#include <yq/core/Object.hpp>
#include <ys/bit/SStringMap.hpp>
#include <ys/bit/Dim.hpp>
#include <ys/bit/ID.hpp>
#include <ys/typedef/revision.hpp>
#include <ys/typedef/sobject.hpp>
#include <ys/keywords.hpp>
#include <unordered_map>

namespace yq::spatial {
    class SObject;
    class SDocument;
    struct Remapper;
    template <typename Obj> class SObjectFixer;
    
    class SObjectInfo : public ObjectInfo {
    public:
        template <typename C> class Writer;
        
        SObjectInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl=std::source_location::current());

        Object* create() const override { return nullptr; }
        virtual SObject* create(SDocument&) const = 0;
        virtual SObject* copy(SDocument&, const SObject&) const = 0;

        DimFlags    supports() const { return m_supports; }

        bool    is_0d() const;
        bool    is_1d() const;
        bool    is_2d() const;
        bool    is_3d() const;
        bool    is_4d() const;
        bool    is_5d() const;
        bool    is_6d() const;

    protected:
        DimFlags    m_supports;
    };
    
    class SObject : public Object {
        YQ_OBJECT_INFO(SObjectInfo)
        YQ_OBJECT_FIXER(SObjectFixer)
        YQ_OBJECT_DECLARE(SObject, Object)
        friend class SDocument;
    public:

        //! Attribute on THIS object
        std::string_view    attribute(const std::string&) const;
        //! Attribute (either this object or parent or document)
        std::string_view    attribute(const std::string&, all_k) const;
        void                attribute_erase(const std::string&);
        string_set_t        attribute_keys() const;
        void                attribute_set(const std::string&, const std::string&);
        void                attribute_set(const std::string&, std::string&&);
        const string_map_t& attributes() const;
        
        const std::string&  description() const { return m_description; }
        
        SDocument&          document() { return m_doc; }
        const SDocument&    document() const { return m_doc; }

        //! TRUE if this is an attribute on THIS object
        bool                is_attribute(const std::string&) const;

        constexpr ID        id() const { return m_id; }
        ID                  parent() const { return m_parent; }
        const SObject*      parent(pointer_k) const;
        SObject*            parent(pointer_k);
        const std::string&  notes() const { return m_notes; }
        const std::string&  title() const { return m_title; }
        const std::string&  uid() const { return m_uid; }

        void    set_description(const std::string&);
        void    set_notes(const std::string&);
        void    set_uid(const std::string&);
        void    set_title(const std::string&);

        static void init_info();
        
        //! Marks this item as having changed
        void    bump();
        
        revision_t  revision(all_k) const { return m_revision[ALL]; }
        revision_t  revision(local_k) const { return m_revision[LOCAL]; }
        
        SObject*    create(child_k, const SObjectInfo&);
        
        template <SomeSObject S>
        S*          create(child_k)
        {
            return static_cast<S*>(create(CHILD, meta<S>()));
        }

    protected:
    
        SObject(SDocument&);
        SObject(SDocument&, const SObject&);
        ~SObject();

        //! Remap IDs/pointers appropriately (call base class first)
        virtual void            remap(const Remapper&);

    private:
        friend class SObjectInfo;
        
        SObject(const SObject&) = delete;
        SObject(SObject&&) = delete;
        SObject& operator=(const SObject&) = delete;
        SObject& operator=(SObject&&) = delete;

        SDocument&              m_doc;
        const ID                m_id;
        SStringMap              m_attributes;
        ID                      m_parent;
        std::vector<ID>         m_children;
        std::string             m_title;
        std::string             m_description;
        std::string             m_uid;
        std::string             m_notes;
        AllLocal<revision_t>    m_revision  = {};
        
        ID::id_t        get_id() const { return m_id.id; }
        
        uint64_t        get_revision() const { return m_revision.all; }
        
        struct Repo;
        static Repo& repo();
    };
    
    struct Remapper {
        std::unordered_map<ID::id_t, ID::id_t>    data;
        ID operator()(ID) const;
    };
}
