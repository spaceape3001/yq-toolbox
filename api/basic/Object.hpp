////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <basic/meta/ObjectInfo.hpp>
#include <basic/DelayInit.hpp>

namespace yq {

#define YQ_OBJECT_INFO( info )     public: using MyInfo    = info;

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


    //! Root Meta Capable Object 
    //! Serialization to/from XML is expected
    class Object {
    public:
        
        //  Bootstrapping as the macro can't be used on the Object itself
        
        /*! \brief Info for this object type
        
        Should *ALWAYS* be the most specific info for the class
        */
        using MyInfo    = ObjectInfo;
        
        /*! \brief Base Class
        
            Except for Object, all others should have a base class.
        */
        using MyBase    = void;
        
        /*! \brief Object type itself
        
            A little redundant, but can be useful
        */
        using MyObject  = Object;
        
        
        /*! \brief ObjectInfo applicaable to the derived class
        */
        virtual const ObjectInfo&   metaInfo() const = 0;
        
        /*! \brief Object Info applicable to *THIS* class
        */
        static const ObjectInfo&    staticMetaInfo();
        
        virtual ~Object(){}
    };

    template <typename Obj>
    requires std::is_base_of_v<Object, Obj>
    struct InfoBinder<Obj> {
        using Info  = typename Obj::MyInfo;    
        static constexpr const bool Defined         = true;                 
        static constexpr const bool IsObject        = true;                 
        static constexpr const bool IsCompound      = true;                 
        static constexpr const bool IsType          = false;
        static const Info& bind() { return Obj::staticMetaInfo(); } 
        static Info&       edit() { return const_cast<Info&>(Obj::staticMetaInfo()); }
    };
    
    template <typename Obj>
    struct ObjectFixer  : public Obj::MyInfo {
        ObjectFixer(std::string_view szName, typename Obj::MyBase::MyInfo& myBase, std::source_location sl=std::source_location::current()) :
            Obj::MyInfo(szName, myBase, sl)
        {
        }
        
        virtual size_t  size() const override
        {
            return sizeof(Obj);
        }
        
        virtual Obj*    create() const override
        {
            if constexpr (std::is_default_constructible_v<Obj> && !std::is_abstract_v<Obj>) {
                if(ObjectInfo::is_abstract())
                    return nullptr;
                return new Obj;
            } else
                return nullptr;
        }
        
        static DelayInit::Ctor  s_reg;
    };
    
}


#define YQ_OBJECT_IMPLEMENT(name)                                                                                   \
    const name::MyInfo&     name::staticMetaInfo()                                                                  \
    {                                                                                                               \
        static yq::ObjectFixer<name>*  s_info = new yq::ObjectFixer<name>(#name, yq::InfoBinder<MyBase>::edit());   \
        return *s_info;                                                                                             \
    }                                                                                                               \
    const name::MyInfo&     name::metaInfo() const                                                                  \
    {                                                                                                               \
        return staticMetaInfo();                                                                                    \
    }                                                                                                               \
    template <> yq::DelayInit::Ctor yq::ObjectFixer<name>::s_reg([](){ name::staticMetaInfo(); });

