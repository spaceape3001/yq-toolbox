////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/DelayInit.hpp>
#include <yq/core/Ref.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/meta/CompoundMetaDynamic.hpp>
#include <yq/meta/UnsafePropGetter.hpp>
#include <yq/meta/UnsafePropSetter.hpp>

namespace yq {
    template <typename C>
    class ObjectMeta::Writer : public CompoundMeta::Dynamic<C> {
    public:
    
        using CompoundMeta::Dynamic<C>::property;
    

        /*! \brief Defines a property
        
            This defines a property for the type/object
        
            \tparam T       type
            \param pointer          Pointer to class/type member
            \param[in] isReadOnly   Set to TRUE to make this read-only property
        */
        template <typename C2, typename T>
        PropertyMeta::Writer<T>     property(unsafe_k, std::string_view szName, T (C2::*pointer), bool isReadOnly=false, const std::source_location& sl=std::source_location::current())
        {
            assert(pointer);
            PropertyMeta*ret  = new PropertyMeta(szName, sl, meta<T>(), m_meta);
            ret -> set(Flag::STATE);
            new UIPM_PropGetter<C,C2,T>(ret, sl, pointer);
            if(!isReadOnly)
                new UIPM_PropSetter<C,C2,T>(ret, sl, pointer);
            return PropertyMeta::Writer<T>{ret};
        }
        
        template <typename C2, typename T>
        PropertyMeta::Writer<T>     property(unsafe_k, std::string_view szName, read_only_k, T (C2::*pointer), const std::source_location& sl=std::source_location::current())
        {
            return property(UNSAFE, szName, pointer, true, sl);
        }
    
        /*! \brief Sets the base object (if not already set)
        */
        template <typename B>
        Writer&     base()
        {
            static_assert( std::is_base_of_v<B, C>, "T must derive from B!" );
            ObjectMeta*     obj = static_cast<ObjectMeta*>(Meta::Writer::m_meta);
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
        
        Writer(ObjectMeta* obj) : CompoundMeta::Dynamic<C>(obj), m_meta(obj)
        {
            assert(obj);
            if constexpr ( std::is_abstract_v<C> ){
                Meta::Writer::m_meta -> set(Flag::ABSTRACT);
            }
            
        }
        
        Writer(ObjectMeta& obj) : Writer(&obj)
        {
        }
        
    private:
        ObjectMeta*  m_meta = nullptr;
    };

    /*! \brief Final type-specific info class
    
        This is the final, derived class for the specific info system for the specified object.  
        It's ultimate purpose is to make sure the template object can be created (if it's capable)
    */
    template <typename Obj>
    struct ObjectFixer  : public Obj::MyMeta, public DelayInit {
        ObjectFixer(std::string_view szName, typename Obj::MyBase::MyMeta& myBase, std::source_location sl=std::source_location::current()) :
            Obj::MyMeta(szName, myBase, sl)
        {
            if constexpr ( std::is_abstract_v<Obj> ){
                Meta::set(Meta::Flag::ABSTRACT);
            }
            if constexpr ( std::is_base_of_v<Refable,Obj>){
                Meta::set(Meta::Flag::REFABLE);
            }
        }
        
        virtual void initialize() override
        {
            if constexpr (!std::is_same_v<typename Obj::MyBase, void>){
                if constexpr (&Obj::init_meta != &Obj::MyBase::init_meta){
                    Obj::init_meta();
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
                if(ObjectMeta::is_abstract())
                    return nullptr;
                return new Obj;
            } else
                return nullptr;
        }
        
        static DelayInit::Ctor  s_reg;
    };
}


