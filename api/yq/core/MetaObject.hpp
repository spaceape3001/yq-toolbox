////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Object.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>
#include <yq/core/Ref.hpp>
#include <yq/core/Revision.hpp>
#include <yq/core/UniqueID.hpp>

namespace yq {

    /*! \brief Information for a meta object
    */
    class MetaObjectMeta : public ObjectMeta {
    public:
        template <typename C> class Writer;
        
        /*! \brief Constructor
            \note Intended for the meta system, but must be left public.  Manual invocation is not recommended.
            \param[in] zName    Name of the meta object
            \param[in] base     Base object
            \param[in] sl       Source location of being instantiated
        */
        MetaObjectMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());
    };

    /*! \brief Abstract Meta Object
    
        The meta object is meant in the common OOP woth reference counting, a unique ID, a revision, and the traits
        of meta, which can allow for seemless loading/saving that's outside the specific class's implementation.
        
        \note Copy & Move capabilities have been disabled
    */
    class MetaObject : public Object, public RefCount, public UniqueID, public Revision {
        YQ_OBJECT_META(MetaObjectMeta)
        YQ_OBJECT_DECLARE(MetaObject, Object)
    public:
    
        //! Our ID number, must be exposed for the meta property
        constexpr uint64_t id() const { return UniqueID::id(); }
        
        //! Our current revision number.
        uint64_t revision() const { return Revision::revision(); }
        
        static void init_meta();
        
    protected:
    
        //! Default constructor
        MetaObject();
        
        //! Copy constructor (to allow copies), but ID & revision will be different
        MetaObject(const MetaObject&);
        
        //! Default destructor
        virtual ~MetaObject();
        
    private:
        MetaObject(MetaObject&&) = delete;
        MetaObject& operator=(const MetaObject&) = delete;
        MetaObject& operator=(MetaObject&&) = delete;
    };
}
