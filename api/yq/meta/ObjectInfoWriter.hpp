////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/DelayInit.hpp>
#include <yq/meta/ObjectInfo.hpp>
#include <yq/meta/CompoundInfoDynamic.hpp>

namespace yq {
    template <typename C>
    class ObjectInfo::Writer : public CompoundInfo::Dynamic<C> {
    public:
    
        /*! \brief Sets the base object (if not already set)
        */
        template <typename B>
        Writer&     base()
        {
            static_assert( std::is_base_of_v<B, C>, "T must derive from B!" );
            ObjectInfo*     obj = static_cast<ObjectInfo*>(Meta::Writer::m_meta);
            assert(!obj->m_base);
            obj->m_base = &meta<B>();
            return *this; 
        }
        
        Writer&     abstract()
        {
            if(Meta::Writer::m_meta)
                Meta::Writer::m_meta -> set(Flag::ABSTRACT);
            return *this;
        }
        
        Writer(ObjectInfo* obj) : CompoundInfo::Dynamic<C>(obj) 
        {
            assert(obj);
            if constexpr ( std::is_abstract_v<C> ){
                Meta::Writer::m_meta -> set(Flag::ABSTRACT);
            }
            
        }
        
        Writer(ObjectInfo& obj) : Writer(&obj)
        {
        }
    };

    /*! \brief Final type-specific info class
    
        This is the final, derived class for the specific info system for the specified object.  
        It's ultimate purpose is to make sure the template object can be created (if it's capable)
    */
    template <typename Obj>
    struct ObjectFixer  : public Obj::MyInfo, public DelayInit {
        ObjectFixer(std::string_view szName, typename Obj::MyBase::MyInfo& myBase, std::source_location sl=std::source_location::current()) :
            Obj::MyInfo(szName, myBase, sl)
        {
            if constexpr ( std::is_abstract_v<Obj> ){
                Meta::set(Meta::Flag::ABSTRACT);
            }
        }
        
        virtual void initialize() override
        {
            if constexpr (!std::is_same_v<typename Obj::MyBase, void>){
                if constexpr (&Obj::init_info != &Obj::MyBase::init_info){
                    Obj::init_info();
                }
            }
        }
        
        
        //! Got the type, rig the size up
        virtual size_t  size() const override
        {
            return sizeof(Obj);
        }
        
        //! Create the object (if legal)
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


