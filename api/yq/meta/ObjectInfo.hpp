////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/CompoundInfo.hpp>
#include <yq/meta/MetaLookup.hpp>

namespace yq {

    class Object;

    /*! \brief Represents info for an object thats intrusively bound
    */
    class ObjectInfo : public CompoundInfo {
        template <typename> friend struct InfoBinder;
        friend class Object;
    public:
    
        //! Base class
        const ObjectInfo*   base() const { return m_base; }
    
        template <typename C> class Writer;

        /*! Constructor
        
            \param[in] zName    name of the object
            \param[in] base     Base object
            \param[in] sl       Source location (defaulted)
        */
        ObjectInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl=std::source_location::current());
        
        /*! Creates the object
        
            Creates the object, returns NULL if that can't occur.  
            Caller is responsible for deleting the object.
        */
        virtual Object* create() const { return nullptr; }

        //! Vector of all object infos
        static const Vector<const ObjectInfo*>&   all();
        
        //! Finds the specified object by key
        static const ObjectInfo*        find(std::string_view);
        
        //! Finds the specified object by ID
        static const ObjectInfo*        find(id_t);
        
        /*! \brief  Tests for base object
        
            This tests to see if the presumed base *is* a base class to this object.
            
            \note This will return FALSE if the presumedBase *IS* this object.
            \param[in]  presumedBase    What we're assuming is a base object
            \return TRUE if presumedBase is a correct assumption, and is a base class to this object.
        */
        bool    is_base(const ObjectInfo& presumedBase) const;
        
        /*! \brief Tests for derived object
        
            This tests to see if the presumed derived class *is* a derived class to this object.
            
            \note This will return FALSE if the presumedDerived *IS* this object
            
            \param[in] presumedDerived  What we're assuming is a derived object
            \return TRUE if presumedDerived is a correct assumpition, and is derived to this object
        */
        bool    is_derived(const ObjectInfo& presumedDerived) const;
        
        //! Nominal size (in bytes) of the object (not including dynamic memory)
        virtual size_t          size() const;
        
        /*! \brief Derived objects
            
            These are the derived objects to this object.
            
            \param[in] all  TRUE to get all sub-derived objects
        */
        const MetaLookup<ObjectInfo>&    deriveds(bool all=false) const;

        const MetaLookup<ObjectInfo>&    deriveds(all_t) const { return m_all.derived; }
        
        const MetaLookup<ObjectInfo>&    deriveds(local_t) const { return m_local.derived; }
        
        /*! \brief Base objects
        
            These are the base objects to this object
            
            \param[in] all      TRUE to get all base objects (all the way to Object)
        */
        const MetaLookup<ObjectInfo>&    bases(bool all=false) const;

        const MetaLookup<ObjectInfo>&    bases(all_t) const { return m_all.bases; }
        
        const MetaLookup<ObjectInfo>&    bases(local_t) const { return m_local.bases; }
        
        /*! \brief Properties
        
            These are the properties on the object.
            
            \param[in] all      TRUE to get all properties on all base objects too.
        */
        const MetaLookup<PropertyInfo>&  properties(bool all=false) const;

        const MetaLookup<PropertyInfo>&  properties(all_t) const { return m_all.properties; }

        const MetaLookup<PropertyInfo>&  properties(local_t) const { return m_local.properties; }
        
        /*! \brief Methods
            
            These are the methods on the object
            
            \param[in] all      TRUE to get all the methods across all base objects too.
        */
        const MetaLookup<MethodInfo>&   methods(bool all=false) const;
        
        const MetaLookup<MethodInfo>&   methods(all_t) const { return m_all.methods; }
        
        const MetaLookup<MethodInfo>&   methods(local_t) const { return m_local.methods; }
    
    protected:
        friend class PropertyInfo;
        friend class MethodInfo;
        
        /*! \brief Constructor
        
            A no-base constructor, of which there should only be one (Object itself)
            
            \param[in] zName    Name of the object
            \param[in] sl       Source location, let the default work its magic
        */
        ObjectInfo(std::string_view zName, const std::source_location& sl=std::source_location::current());
        
        //! Sweeping in all the based/deriveds/properties/methods/etc
        virtual void                    sweep_impl() override;

        ObjectInfo*     m_base; // defined/declared base
        
        //! General definitions to what it's an object
        struct D {
            //! Base classes
            MetaLookup<ObjectInfo>     bases;
            //! Derived classes
            MetaLookup<ObjectInfo>     derived;
            //! Properties
            MetaLookup<PropertyInfo>   properties;
            //! Methods
            MetaLookup<MethodInfo>     methods;
            
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
        
        const D& def(bool all) const { return all ? m_all : m_local; }
    
    private:
        ObjectInfo(std::string_view zName, ObjectInfo* base, const std::source_location& sl);
    };


    /*! \brief Converts meta to object, if it's valid
    
        \return ObjectInfo pointer, if valid, NULL otherwise
    */
    const ObjectInfo* to_object(const Meta* m);
    
    /*! \brief Converts meta to object, if it's valid
    
        \return ObjectInfo pointer, if valid, NULL otherwise
    */
    ObjectInfo* to_object(Meta* m);
}
