////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/CompoundMeta.hpp>
#include <yq/meta/MetaLookup.hpp>
#include <yq/typedef/object.hpp>
#include <yq/trait/no_hidden_warning.hpp>

namespace yq {

    class Object;
    class ConstructorMeta;

    /*! \brief Represents info for an object thats intrusively bound
    */
    class ObjectMeta : public CompoundMeta {
        template <typename> friend struct MetaBinder;
        friend class Object;
    public:
    
        //! Base class
        const ObjectMeta*   base() const { return m_base; }
    
        template <typename C> class Writer;

        /*! Constructor
        
            \param[in] zName    name of the object
            \param[in] base     Base object
            \param[in] sl       Source location (defaulted)
        */
        ObjectMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());
        
        /*! Creates the object
        
            Creates the object, returns NULL if that can't occur.  
            Caller is responsible for deleting the object.
        */
        virtual Object* create() const { return nullptr; }
        
        //  TODO
        //  Object* create(std::span<const Any>) const;

        //! Vector of all object infos
        static const Vector<const ObjectMeta*>&   all();
        
        //! Finds the specified object by key
        static const ObjectMeta*        find(std::string_view);
        
        //! Finds the specified object by ID
        static const ObjectMeta*        find(id_t);
        
        // TODO
        //  const std::vector<const ConstructorMeta*>& constructors() const { return m_constructors; }

        /*! \brief  Tests for base object
        
            This tests to see if the presumed base *is* a base class to this object.
            
            \note This will return FALSE if the presumedBase *IS* this object.
            \param[in]  presumedBase    What we're assuming is a base object
            \return TRUE if presumedBase is a correct assumption, and is a base class to this object.
        */
        bool    is_base(const ObjectMeta& presumedBase) const;
        
        template <SomeObject>
        bool    is_base() const;

        bool    is_base_or_this(const ObjectMeta& presumedBase) const;

        template <SomeObject>
        bool    is_base_or_this() const;

        bool    is_this(const ObjectMeta& presumedBase) const;
        
        //! TRUE if this matches (or derived from)
        template <SomeObject>
        bool    is_this() const;
        
        /*! \brief Tests for derived object
        
            This tests to see if the presumed derived class *is* a derived class to this object.
            
            \note This will return FALSE if the presumedDerived *IS* this object
            
            \param[in] presumedDerived  What we're assuming is a derived object
            \return TRUE if presumedDerived is a correct assumpition, and is derived to this object
        */
        bool    is_derived(const ObjectMeta& presumedDerived) const;
        
        template <SomeObject>
        bool    is_derived() const;
        
        bool    is_derived_or_this(const ObjectMeta& presumedDerived) const;
        
        template <SomeObject>
        bool    is_derived_or_this() const;

        //! Count of hops to the presumed base class, negative if it's not a base
        int     hops_to_base(const ObjectMeta& presumedBase) const;

        //! Count of hops to the presumed derived class, negative if it's not a base
        int     hops_to_derived(const ObjectMeta& presumedDerived) const;
        
        
        //! Nominal size (in bytes) of the object (not including dynamic memory)
        virtual size_t          size() const;
        
        /*! \brief Derived objects
            
            These are the derived objects to this object.
            
            \param[in] all  TRUE to get all sub-derived objects
        */
        const MetaLookup<ObjectMeta>&    deriveds(bool all=false) const;

        const MetaLookup<ObjectMeta>&    deriveds(all_k) const { return m_all.derived; }
        
        const MetaLookup<ObjectMeta>&    deriveds(local_k) const { return m_local.derived; }
        
        /*! \brief Base objects
        
            These are the base objects to this object
            
            \param[in] all      TRUE to get all base objects (all the way to Object)
        */
        const MetaLookup<ObjectMeta>&    bases(bool all=false) const;

        const MetaLookup<ObjectMeta>&    bases(all_k) const { return m_all.bases; }
        
        const MetaLookup<ObjectMeta>&    bases(local_k) const { return m_local.bases; }
        
        /*! \brief Properties
        
            These are the properties on the object.
            
            \param[in] all      TRUE to get all properties on all base objects too.
        */
        const MetaLookup<PropertyMeta>&  properties(bool all=false) const;

        const MetaLookup<PropertyMeta>&  properties(all_k) const { return m_all.properties; }

        const MetaLookup<PropertyMeta>&  properties(local_k) const { return m_local.properties; }
        
        /*! \brief Methods
            
            These are the methods on the object
            
            \param[in] all      TRUE to get all the methods across all base objects too.
        */
        const MetaLookup<MethodMeta>&   methods(bool all=false) const;
        
        const MetaLookup<MethodMeta>&   methods(all_k) const { return m_all.methods; }
        
        const MetaLookup<MethodMeta>&   methods(local_k) const { return m_local.methods; }
        
        //! Finds the specified property (ALL is implied)
        const PropertyMeta*             property(std::string_view) const;
    
    protected:
        friend class PropertyMeta;
        friend class MethodMeta;
        
        /*! \brief Constructor
        
            A no-base constructor, of which there should only be one (Object itself)
            
            \param[in] zName    Name of the object
            \param[in] sl       Source location, let the default work its magic
        */
        ObjectMeta(std::string_view zName, const std::source_location& sl=std::source_location::current());
        
        //! Sweeping in all the based/deriveds/properties/methods/etc
        virtual void                    sweep_impl() override;

        ObjectMeta*     m_base; // defined/declared base
        
        //! General definitions to what it's an object
        struct D {
            //! Base classes
            MetaLookup<ObjectMeta>     bases;
            //! Derived classes
            MetaLookup<ObjectMeta>     derived;
            //! Properties
            MetaLookup<PropertyMeta>   properties;
            //! Methods
            MetaLookup<MethodMeta>     methods;
            
            void                    clear()
            {
                bases.clear();
                derived.clear();
                properties.clear();
                methods.clear();
            }
        };
        
        //! What's defined on this object
        D               m_local;
        //! What's defiend across all relevant objects
        D               m_all;

        //std::vector<const ConstructorMeta*> m_constructors;
        
        const D& def(bool all) const { return all ? m_all : m_local; }
    
    private:
        ObjectMeta(std::string_view zName, ObjectMeta* base, const std::source_location& sl);
    };


    /*! \brief Converts meta to object, if it's valid
    
        \return ObjectMeta pointer, if valid, NULL otherwise
    */
    const ObjectMeta* to_object(const Meta* m);
    
    /*! \brief Converts meta to object, if it's valid
    
        \return ObjectMeta pointer, if valid, NULL otherwise
    */
    ObjectMeta* to_object(Meta* m);
}
