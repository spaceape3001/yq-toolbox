////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>
#include <basic/trait/not_copyable.hpp>
#include <basic/trait/not_moveable.hpp>
#include <basic/Hash.hpp>
#include <basic/Map.hpp>
#include <basic/MultiMap.hpp>
#include <basic/Set.hpp>
#include <basic/Vector.hpp>

#include <basic/meta/AnyDef.hpp>

#include <source_location>

/*
    META is about runtime reflection & introspection
    
    OBJECT      -- something that has it baked in, blind copying is NOT advised?
    VALUE       -- something that doesn't have it baked in, so copying is normal?
    PROPERTY    -- something that a user can interact with, read/set, on an object/value
    METHOD      -- function (on modifier) on OBJECT or VALUE -- can be a static method (no implicit class/type parameter)
    FUNCTION    -- global method (combinding with method... parent will be "GLOBAL" with global meta object
    GLOBAL      -- global property -- combined with property
    TYPE        -- can have property/methods (even values can, in theory)
    PAGE        -- for the server
    POINTER     -- pointer/ref, assumed to be shared_ptr<T>
    ENUM        -- enumeration (implicitly value)
    FLAG        -- combination of enums (implicitly value)
    
    Also, we don't want to be duplicating data that's already in the program string table, therefore
    all "const char[]" are expected to be pre-baked constants (not from std::string's c_str())
*/


namespace yq {
    //class Any;
    
    /*
        We want flags, however, they also need to expandable in the other libraries. 
        These flags are intended to avoid needless dynamic casts, check & cast.  
        
        Do NOT rely on the numeric values, those are subject to change.
    */
    enum : uint64_t {
        TYPE            = 1ULL << 0,
        OBJECT          = 1ULL << 1,
        COMPOUND        = 1ULL << 2,
        PROPERTY        = 1ULL << 3,
        METHOD          = 1ULL << 4,
        ENUM            = 1ULL << 5,
        ARG             = 1ULL << 6,
        GLOBAL          = 1ULL << 7,
        COLLECTION      = 1ULL << 8,
        TEMPLATE        = 1ULL << 9,
        WEB             = 1ULL << 10,
        PAGE            = 1ULL << 11,
        ASSET           = 1ULL << 12,
        SHADER          = 1ULL << 13,
        TEXTURE         = 1ULL << 14,
        LOADER          = 1ULL << 15,
        CACHE           = 1ULL << 16,
        COMPILER        = 1ULL << 17,
        WIDGET          = 1ULL << 18,
        RENDERED        = 1ULL << 19,
        RENDER3D        = 1ULL << 20,
        CAMERA          = 1ULL << 21,
        PIPELINE        = 1ULL << 22,
        
        STATE           = 1ULL << 26, //!< "State" property
        STATIC          = 1ULL << 27, //!< Non-object specific (global variables, functions, etc)
        SMALL           = 1ULL << 28, //!< Small enough to fit in DataBlock
        TLS             = 1ULL << 29, //!< Thread local storage
        LESS            = 1ULL << 30, //!< Can compare
        TODO            = 1ULL << 40,
        ABSTRACT        = 1ULL << 41,

        LOCAL_ONLY      = 1ULL << 56,
        LOGIN_REQ       = 1ULL << 57,
        NO_EXPAND       = 1ULL << 58,
        POST_ANON       = 1ULL << 59,
        HAS_SUBS        = 1ULL << 60,
        DISABLE_REG     = 1ULL << 61,
        SEALED          = 1ULL << 62,
        SWEPT           = 1ULL << 63
    };
    
    //bool    is_type(const Meta&);
    //bool    is_object(const Meta&);
    //bool    is_value(const Meta&);
    //bool    is_global(const Meta&);
    //bool    is_property(const Meta&);
    //bool    is_method(const Meta&);
    //bool    is_function(const Meta&);
    //bool    is_pointer(const Meta&); 
    //bool    is_structure(const Meta&);   

    /* !\brief Root "meta" for all meta, everything else will derive from this.
    
        \note We will ASSUME SINGLE THREADED until AFTER freeze is called, so that no mutex locking is required.
    */
    class Meta : trait::not_copyable, trait::not_moveable {
    public:
    
    
            //  I mean, really, 255 ain't enough?? Even in full-on UTF-8, that's over 40 characters.
            //  This applies to tags  too BTW
        static constexpr const size_t   MAX_NAME            = 255;
        
        static constexpr const size_t   MAX_KEY             = 255;

            //  Label's a bit longer to permit formatting
        static constexpr const size_t   MAX_LABEL           = 1023;
        
            //! No manifestos disguised as descriptions please
        static constexpr const size_t   MAX_DESCRIPTION     = 4095;
        
    
        //! Meta ID type
        using id_t                      = unsigned int;
        
        //! Our flags
        using options_t                 = uint64_t;
        
        static const Vector<const Meta*>&   all();
        static const Meta*                  lookup(id_t);
        
        //! Forces the initialization of the meta
        static void                         init();     // starts/triggers the initialization (can be repeated)
        //! Locks/freezes the meta system (init is called a final time)
        static void                         freeze();
        
        //! Rather than using mutexes, we assert/check the read is being done thread-safe & acceptable
        static bool                         thread_safe_read();
        //! Rather than using mutexes, we assert/check the write is being done thread-safe & acceptable
        static bool                         thread_safe_write();
        
        //! TRUE if we've not been frozen (modifications are rejected after this)
        static bool                         unlocked();


        /*! \brief Any relevant aliases
        */
        const Set<std::string_view>&    aliases() const { return m_aliases; }
        
        //! \brief Vector of child-meta (could include pointers)
        const Vector<const Meta*>&      children() const { return m_children; }
        
        const std::string_view&         description() const { return m_description; }
        
        //! \brief Flags for this class
        uint64_t                        flags() const { return m_flags; }
        
        //! Generic type of this item
        virtual const char*             generic() const { return "Meta"; }

        //  TODO
        bool                            has_tag(std::string_view) const;

        //! \brief Our ID number
        id_t                            id() const { return m_id; }
        
        bool                            is_object() const { return (m_flags & OBJECT) != 0; }
        bool                            is_type() const { return (m_flags & TYPE) != 0; }
        
        std::string_view                label() const { return m_label; }

        std::string_view                name() const { return m_name; }
        std::string_view                name_stem() const { return m_stem; }
        
        
        //  MAY BE NULL
        const Meta*                     parent() const { return m_parent; }

        //! \brief Source location of this definition
        const std::source_location& source() const { return m_source; }
        
        //  TODO
        const Any&                  tag(std::string_view) const;
        
        //! \brief Marked as "TODO" on this object (reminder for future work)
        bool                            todo() const { return (m_flags&TODO) != 0; }
        

            // used during the creation....
        class Writer;
        
        template <typename T>
        struct LUC;

    protected:
        friend class ArgInfo;
        friend class CompoundInfo;
        friend class GlobalInfo;
        friend class MethodInfo;
        friend class ObjectInfo;
        friend class PropertyInfo;
        friend class TypeInfo;
    
        //! Used by the constructor's default to auto-assign an ID
        static constexpr const id_t AUTO_ID = ~(id_t) 0;
        explicit Meta(std::string_view, const std::source_location&, id_t i=AUTO_ID);
        explicit Meta(std::string_view, Meta* parent, const std::source_location&, id_t i=AUTO_ID);
        virtual ~Meta();    // do NOT delete... C++ won't let it be deleted
        
            // called after each init... repopulate property maps/vectors/etc (do not append, rebuild)
        void                            sweep();
        virtual void                    sweep_impl() {}
        static void                     sweep_all();
        
        
        void    set_option(options_t v) { m_flags |= v; }
        void    set_options(options_t v) { m_flags |= v; }
        void    set_name(std::string_view v);
        
        
    private:
        using TagMap    = Map<std::string_view, Any, IgCase>;
    
        TagMap                          m_tags;
        Set<std::string_view>           m_aliases;
        std::string_view                m_description;
        std::string_view                m_label;
        std::string_view                m_name;
        std::string_view                m_stem;
        Vector<const Meta*>             m_children;
        const Meta*                     m_parent    = nullptr;
        std::source_location            m_source;
        options_t                       m_flags     = 0;
        id_t                            m_id        = AUTO_ID;
        
        struct Repo;
        static Repo&    repo();
        
    };

    template <typename T>
    struct Meta::LUC {
        //   CONDITION is still valid, however, we can't use it w/o compiler issues
        //static_assert( std::is_base_of_v<Meta, T>, "T must derive from Meta!");
        using MM    = MultiMap<std::string_view, const T*, IgCase>;
        Vector<const T*>            all;
        MM                          lut;
        StringViewSet               keys;
        
        LUC& operator<<(const T* p)
        {
            all << p;
            lut.insert(p->name(), p);
            keys << p->name();
            return *this;
        }
        
        LUC&    operator += (const LUC& b)
        {
            all += b.all;
            lut += b.lut;
            keys += b.keys;
            return *this;
        }
        
        void    add_mapping(std::string_view k, const T* d)
        {
            lut.insert(k,d);
            keys += k;
        }
    };
}

