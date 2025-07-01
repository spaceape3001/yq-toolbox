////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MetaBinder.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/typedef/object.hpp>

namespace yq {

/*! \brief Macro to override the info

    This overrides the "MyInfo" for a class (& base) to be the new type.
*/
#define YQ_OBJECT_INFO( info )      public: using MyInfo    = info;

/*! \brief Macro to override the fixer

    This overrides the "MyFixer" for a class (& base) to be the new type.
*/
#define YQ_OBJECT_FIXER( fixer )     public: template <typename T> using MyFixer    = fixer<T>;

#define YQ_OBJECT_BASE( base )      public: using MyBase    = base;

#define YQ_OBJECT_DECLARE_BASELESS( cls )               \
public:                                                 \
    using MyObject = cls;                               \
    virtual const MyInfo& metaInfo() const override;    \
    static const MyInfo&  staticMetaInfo();

/*! \brief Declares an object type

    Only criteria is that the info is now considered intrinsiic, there's a virtual 
    method called metaInfo() return const& to object info or derived.  
    (The implementation macro will define the metaInfo() method.)

    \note   MUST BE USED AT GLOBAL SCOPE (NO NAMESPACES)
*/
#define YQ_OBJECT_DECLARE( cls, base )                  \
    YQ_OBJECT_BASE(base)                                \
    YQ_OBJECT_DECLARE_BASELESS(cls)

    template <typename Obj>
    struct ObjectFixer;
    
    //! Root Meta Capable Object 
    //! Serialization to/from XML is expected
    class Object {
    public:
        
        //  Bootstrapping as the macro can't be used on the Object itself
        
        /*! \brief Info for this object type
        
        Should *ALWAYS* be the most specific info for the class
        */
        using MyInfo        = ObjectMeta;
        
        /*! \brief Base Class
        
            Except for Object, all others should have a base class.
        */
        using MyBase        = void;
        
        /*! \brief Object type itself
        
            A little redundant, but can be useful
        */
        using MyObject      = Object;
        
        template <typename T>
        using MyFixer       = ObjectFixer<T>;
        
        
        /*! \brief ObjectMeta applicaable to the derived class
        */
        virtual const ObjectMeta&   metaInfo() const = 0;
        
        /*! \brief Object Info applicable to *THIS* class
        */
        static const ObjectMeta&    staticMetaInfo();
        
        //! Destructor, virtual given the nature of this base class
        virtual ~Object(){}
        
        static void init_meta();
    };

    template <typename Obj>
    requires std::is_base_of_v<Object, Obj>
    struct MetaBinder<Obj> {
        using Info  = typename Obj::MyInfo;    
        static constexpr const bool Defined         = true;                 
        static constexpr const bool IsObject        = true;                 
        static constexpr const bool IsCompound      = true;                 
        static constexpr const bool IsType          = false;
        static constexpr const bool IsTachyon       = false;                 
        static constexpr const bool IsInterface     = false;                 
        static const Info& bind() { return Obj::staticMetaInfo(); } 
        static Info&       edit() { return const_cast<Info&>(Obj::staticMetaInfo()); }
    };

    template <SomeObject T>
    auto writer(unsafe_k)
    {
        return typename T::MyInfo::template Writer<T>( const_cast<typename T::MyInfo&>( T::staticMetaInfo()));
    }

    template <SomeObject Obj>
    bool    ObjectMeta::is_base() const
    {
        return is_base(meta<Obj>());
    }

    template <SomeObject Obj>
    bool    ObjectMeta::is_base_or_this() const
    {
        return is_base_or_this(meta<Obj>());
    }

    template <SomeObject Obj>
    bool    ObjectMeta::is_derived() const
    {
        return is_derived(meta<Obj>());
    }

    template <SomeObject Obj>
    bool    ObjectMeta::is_derived_or_this() const
    {
        return is_derived_or_this(meta<Obj>());
    }

    template <SomeObject Obj>
    bool    ObjectMeta::is_this() const
    {
        return is_this(meta<Obj>());
    }
}

/*! \brief IMPLEMENTS meta for the specified object

    This is the macro that is required to IMPLEMENT the meta for an object.  
    \note Undefined linker errors will result if this macro isn't used in a SOURCE file.
*/
#define YQ_OBJECT_IMPLEMENT(name)                                                                                   \
    const name::MyInfo&     name::staticMetaInfo()                                                                  \
    {                                                                                                               \
        static name::MyFixer<name>*  s_info = new name::MyFixer<name>(#name, yq::MetaBinder<MyBase>::edit());   \
        return *s_info;                                                                                             \
    }                                                                                                               \
    const name::MyInfo&     name::metaInfo() const                                                                  \
    {                                                                                                               \
        return staticMetaInfo();                                                                                    \
    }                                                                                                               \
    template <> yq::DelayInit::Ctor yq::ObjectFixer<name>::s_reg([](){ name::staticMetaInfo(); });

/*! \brief Force a info binding declaration

    This is useful when there's a diamond pattern forming, to resolve that YES, this 
    is a known meta-object
*/
#define YQ_OBJECT_FORCE(...)                                            \
    namespace yq {                                                      \
        template <>                                                     \
        struct MetaBinder<__VA_ARGS__>  : public std::true_type {       \
            using Info = __VA_ARGS__::MyInfo;                           \
            static constexpr const bool Defined         = true;         \
            static constexpr const bool IsObject        = true;         \
            static constexpr const bool IsType          = false;        \
            static constexpr const bool IsCompound      = true;         \
            static constexpr const bool IsInterface     = false;        \
            static constexpr const bool IsProxy         = false;        \
            static constexpr const bool IsTachyon       = false;        \
            static const Info&   bind() { return edit(); }              \
            static Info&         edit()  { return const_cast<Info&>(__VA_ARGS__::staticMetaInfo()); } \                                \
        };                                                              \
    } 
