////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/InfoBinder.hpp>
#include <yq/meta/ObjectInfo.hpp>
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

/*! \brief Declares an object type

    Only criteria is that the info is now considered intrinsiic, there's a virtual 
    method called metaInfo() return const& to object info or derived.  
    (The implementation macro will define the metaInfo() method.)

    \note   MUST BE USED AT GLOBAL SCOPE (NO NAMESPACES)
*/
#define YQ_OBJECT_DECLARE( cls, base )                  \
public:                                                 \
    using MyBase   = base;                              \
    using MyObject = cls;                               \
    virtual const MyInfo& metaInfo() const override;    \
    static const MyInfo&  staticMetaInfo();

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
        using MyInfo        = ObjectInfo;
        
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
        
        
        /*! \brief ObjectInfo applicaable to the derived class
        */
        virtual const ObjectInfo&   metaInfo() const = 0;
        
        /*! \brief Object Info applicable to *THIS* class
        */
        static const ObjectInfo&    staticMetaInfo();
        
        //! Destructor, virtual given the nature of this base class
        virtual ~Object(){}
        
        static void init_info();
    };

    template <typename Obj>
    requires std::is_base_of_v<Object, Obj>
    struct InfoBinder<Obj> {
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

}

/*! \brief IMPLEMENTS meta for the specified object

    This is the macro that is required to IMPLEMENT the meta for an object.  
    \note Undefined linker errors will result if this macro isn't used in a SOURCE file.
*/
#define YQ_OBJECT_IMPLEMENT(name)                                                                                   \
    const name::MyInfo&     name::staticMetaInfo()                                                                  \
    {                                                                                                               \
        static name::MyFixer<name>*  s_info = new name::MyFixer<name>(#name, yq::InfoBinder<MyBase>::edit());   \
        return *s_info;                                                                                             \
    }                                                                                                               \
    const name::MyInfo&     name::metaInfo() const                                                                  \
    {                                                                                                               \
        return staticMetaInfo();                                                                                    \
    }                                                                                                               \
    template <> yq::DelayInit::Ctor yq::ObjectFixer<name>::s_reg([](){ name::staticMetaInfo(); });

