////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/forward.hpp>
#include <yq/art/keywords.hpp>
#include <yq/art/Abstract.hpp>
#include <yq/core/AllLocal.hpp>
#include <yq/core/Ref.hpp>
#include <filesystem>

namespace yq::art {
    class DocMeta : public AbstractMeta {
    public:
        template <typename> class Writer;
        
        DocMeta(std::string_view zName, AbstractMeta& base, const std::source_location& sl=std::source_location::current());
    };
    
    template <typename> class DocFixer;

    //! This is a drawing or something....
    class Doc : public Abstract, public RefCount {
        YQ_OBJECT_META(DocMeta);
        YQ_OBJECT_FIXER(DocFixer)
        YQ_OBJECT_DECLARE(Doc, Abstract)
    public:
    
        static void init_meta();
    
        //! Filepath that we were loaded from
        //! \note Empty for something that's newly created
        const std::filesystem::path&    file() const { return m_file; }
        
        
            //////////////////////////////////////////////////////
            //  GETTERS

        std::string_view    title() const { return m_title; }
        
            //////////////////////////////////////////////////////
            //  SETTERS
        
        void                set_title(std::string_view);
        
            //////////////////////////////////////////////////////
            //  OBJECTS

        //! Used when you need a *specific* pointer for temporary use
        //! \note this isn't guarded, so document/objects can be erased
        Obj*                object(ID);

        //! Used when you need a *specific* pointer for temporary use
        //! \note this isn't guarded, so document/objects can be erased
        const Obj*          object(ID) const;

        bool                valid(ID) const;

            //////////////////////////////////////////////////////
            //  IO

        static DocPtr       load_xml(const std::filesystem::path&);
        static DocPtr       load_xml(const XmlDocument&);
        static DocPtr       load_xml(const ByteArray&);
        bool                save_xml(const std::filesystem::path&) const;
        bool                save_xml(XmlDocument&) const;
        bool                save_xml(ByteArray&) const;
        
    protected:
    
        virtual void        save_to(XmlNode&) const override;
        virtual bool        load_from(const XmlNode&) override;

    public:         Doc();
    protected:      virtual ~Doc();

    private:
        friend class Obj;
        ID                      _insert(Obj*);
        
        std::vector<Obj*>           m_objects;
        std::vector<Obj*>           m_zombies;    //! Erased objects, but retained until the document is destroyed
        std::filesystem::path       m_file;
        std::string                 m_title;
        id_t                        m_load  = 0;

        //  Will likely add "include"/"reference" files (later)

        
        Doc(const Doc&) = delete;
        Doc(Doc&&) = delete;
        Doc& operator=(const Doc&) = delete;
        Doc& operator=(Doc&&) = delete;
    };

}
