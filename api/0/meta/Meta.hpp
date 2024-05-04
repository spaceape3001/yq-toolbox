////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>
#include <0/trait/not_copyable.hpp>
#include <0/trait/not_moveable.hpp>
#include <0/basic/BitArray.hpp>
#include <0/basic/Hash.hpp>
#include <0/basic/Map.hpp>
#include <0/basic/MultiMap.hpp>
#include <0/basic/Set.hpp>
#include <0/basic/Vector.hpp>

#include <0/meta/AnyDef.hpp>

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
    class Meta : not_copyable, not_moveable {
    public:
    
        /*! \brief Meta flags
        
            These are the flags that can be set on the meta. 
        */
        enum class Flag {

            ABSTRACT,       //!< It's abstract (ie can't be created)
            ARG,            //!< It's an argument (ArgInfo)
            ASSET,          //!< It's an asset (AssetInfo)
            ASSOCIATION,    //!< It's an association
            CAMERA,         //!< It's a camera (CameraInfo)
            CACHE,          //!< It's a cache
            COLLECTION,     //!< It's a collection (TypeInfo)
            COMPILER,       //!< It's a compiler
            COMPOUND,       //!< It's a compound/struct (CompoundInfo)
            CONST,          //!< Method/property is CONSTANT/READONLY
            CONSTRAINT,     //!< It's a constraint
            D0,             //!< Item has zero dimensional attributes (or is a 0-dimensional object)
            D1,             //!< Item has one dimensional attributes (or is a 1-dimensional object)
            D2,             //!< Item has two dimensional attributes (or is a 2-dimensional object)
            D3,             //!< Item has three dimensional attributes (or is a 3-dimensional object)
            D4,             //!< Item has four dimensional attributes (or is 4-dimensional object)
            D5,             //!< Item has five dimensional attributes (or is 5-dimensional object)
            D6,             //!< Item has six dimensional attributes (or is a 6-dimensional object)
            DISABLE_REG,    
            DOODLE,         //!< It's a doodle object
            ENUM,           //!< It's an enumeration (Enum)
            EVENT,          //!< It's an event
            EXECUTE,        //!< Execute permission/capabilty
            GENERATOR,      //!< It's a generator (GeneratorInfo)
            GLOBAL,         //!< It's a global (GlobalInfo)
            HAS_SUBS,       
            IMGUI,          //!< ImGUI api enabled/similar usage
            INPUT,          //!< It's flagged as input (graphs)
            LESS,           //!< Can compare
            LOADER,         //!< A loader
            LOCAL_ONLY,     //!< Local only permission
            LOGIN_REQ,      //!< Login required
            MENU_BAR,       //!< Item has a menu bar (EditorInfo)
            METHOD,         //!< It's a method/function (MethodInfo)
            MOTION,         //!< It's a motion item
            NODE,           //!< It's a node
            NO_EXPAND,      //!< Do not expand
            OBJECT,         //!< Meta has ObjectInfo
            OUTPUT,         //!< It's flagged as output (graphs)
            PAGE,           //!< A (web) page
            PIN,            //!< It's a pin
            PIPELINE,       //!< It's a pipeline (PipelineInfo)
            POST_ANON,      //!< Allow for anonymouse posting (ie, login url)
            PHYSICAL,       //!< Physical doodle item
            PROPERTY,       //!< Meta has PropertyInfo
            RENDER3D,       //!< It's a 3D render (Render3DInfo)
            RENDERED,       //!< It's a rendered (RenderedInfo)
            SEALED,         //!< Registration sealed (WebPage)
            SHADER,         //!< Meta has ShaderInfo
            SMALL,          //!< Small enough to fit in DataBlock (typeinfo)
            SPACE,          //!< Item is a space item
            STATE,          //!< "State" property
            STATIC,         //!< Non-object specific (global variables, functions, etc)
            SWEPT,          //!< Meta internal
            TEMPLATE,       //!< It's a template-based thing
            TEXTURE,        //!< Meta has TextureInfo
            TLS,            //!< Thread local storage
            TODO,           //!< It's "TODO" later
            TYPE,           //!< Meta has TypeInfo
            VULKAN,         //!< Vulkan api enabled
            WEB,            //!< Web related
            WIDGET,         //!< It's a widget (WidgetInfo)
            XFG,            //!< Executive Flow Graph

            NEXT_DEFINED_FLAG     //<! Use for custom flag values after this
        };
        
    
    
    
    
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
        
        using options_t                 = std::initializer_list<Flag>;
        
        
        static const std::vector<const Meta*>&  all();
        static const Meta*                      lookup(id_t);
        
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
        const std::set<std::string_view>&    aliases() const { return m_aliases; }
        
        //! \brief Vector of child-meta (could include pointers)
        const std::vector<const Meta*>&      children() const { return m_children; }
        
        void                            clear(Flag);
        
        const std::string_view&         description() const { return m_description; }
        
        //! \brief Flags for this class
        const auto&                     flags() const { return m_flags; }
        

        //! Generic type of this item
        virtual const char*             generic() const { return "Meta"; }

        bool                            has(Flag) const;
        //  TODO
        bool                            has_tag(std::string_view) const;

        //! \brief Our ID number
        id_t                            id() const { return m_id; }
        
        bool                            is_1d() const;
        bool                            is_2d() const;
        bool                            is_3d() const;
        bool                            is_4d() const;
        bool                            is_5d() const;
        bool                            is_6d() const;
        
        //! TRUE if the object is deemed abstract (uncreatable)
        bool                            is_abstract() const;

        bool                            is_argument() const;
        
        bool                            is_asset() const;

        bool                            is_camera() const;

        bool                            is_collection() const;

        bool                            is_compound() const;

        //! TRUE if this is a const method/property/etc
        bool                            is_const() const;

        bool                            is_execute() const;

        bool                            is_expansion_disabled() const;

        bool                            is_global() const;
        
        bool                            is_imgui() const;
        
        bool                            is_input() const;
        
        bool                            is_loader() const;
        
        bool                            is_login_required() const;
        
        bool                            is_method() const;
        
        
        bool                            is_node() const;

        bool                            is_object() const;

        bool                            is_output() const;
        
        bool                            is_pin() const;
        
        bool                            is_pipeline() const;
        
        bool                            is_property() const;
        
        bool                            is_render3d() const;

        bool                            is_rendered() const;

        bool                            is_sealed() const;

        bool                            is_shader() const;
        
        //! TRUE if this type is marked as small (ie, a datablock in size or smaller)
        bool                            is_small() const;

        //! TRUE if this is marked as state.
        //! 
        //! A state property is one that needs to be saved/loaded to properly recreate the object.
        bool                            is_state() const;
        
                //! TRUE if this is a global/static variabels
        //!
        //! A global or static is one that lives outside a particular object, but is instead defined singularly
        //! For the entire application
        bool                            is_static() const;
        
        bool                            is_template() const;

        //! \brief Marked as "TODO" on this object (reminder for future work)
        bool                            is_todo() const;
        bool                            is_type() const;
        
        bool                            is_vulkan() const;
        
        bool                            is_widget() const;
        bool                            is_xfg() const;
        
        std::string_view                label() const { return m_label; }

        std::string_view                name() const { return m_name; }
        std::string_view                name_stem() const { return m_stem; }
        
        
        //  MAY BE NULL
        const Meta*                     parent() const { return m_parent; }

        void    set(Flag);
        void    set(std::initializer_list<Flag>);

        //! \brief Source location of this definition
        const std::source_location&     source() const { return m_source; }
        
        //  TODO
        const Any&                      tag(std::string_view) const;
        
        

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
        
        void    set_name(std::string_view v);
        
        virtual void                add_alias(std::string_view);
        
    private:
        using TagMap    = std::map<std::string_view, Any, IgCase>;
    
        std::map<std::string_view, Any, IgCase> m_tags;
        std::set<std::string_view>              m_aliases;
        std::string_view                        m_description;
        std::string_view                        m_label;
        std::string_view                        m_name;
        std::string_view                        m_stem;
        std::vector<const Meta*>                m_children;
        const Meta*                             m_parent    = nullptr;
        std::source_location                    m_source;
        BitArray<uint64_t, 2>                   m_flags;
        id_t                                    m_id        = AUTO_ID;
        
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

