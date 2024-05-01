////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Object.hpp>
#include <0/meta/ObjectInfo.hpp>
#include <0/meta/ObjectInfoWriter.hpp>
#include <0/basic/Ref.hpp>
#include <0/basic/Revision.hpp>
#include <0/basic/UniqueID.hpp>

namespace yq {

    /*! \brief Information for a meta object
    */
    class MetaObjectInfo : public ObjectInfo {
    public:
        template <typename C> class Writer;
        
        /*! \brief Constructor
            \note Intended for the meta system, but must be left public.  Manual invocation is not recommended.
            \param[in] zName    Name of the meta object
            \param[in] base     Base object
            \param[in] sl       Source location of being instantiated
        */
        MetaObjectInfo(std::string_view zName, const ObjectInfo& base, const std::source_location& sl=std::source_location::current());
    };

    /*! \brief Abstract Meta Object
    
        The meta object is meant in the common OOP woth reference counting, a unique ID, a revision, and the traits
        of meta, which can allow for seemless loading/saving that's outside the specific class's implementation.
        
        \note Copy & Move capabilities have been disabled
    */
    class MetaObject : public Object, public RefCount, public UniqueID, public Revision {
        YQ_OBJECT_INFO(MetaObjectInfo)
        YQ_OBJECT_DECLARE(MetaObject, Object)
    public:
    
        //! Our ID number, must be exposed for the meta property
        uint64_t id() const { return UniqueID::id(); }
        
        //! Our current revision number.
        uint64_t revision() const { return Revision::revision(); }
        
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

    /*! \brief Writer of meta object's meta
    
        This is using during initialization by the methods writing to meta, presenting a writable
        API to modify/set the meta properties, methods, etc.
    */
    template <typename C>
    class MetaObjectInfo::Writer : public ObjectInfo::Writer<C> {
    public:
        Writer(MetaObjectInfo* metaObjInfo) : ObjectInfo::Writer<C>(metaObjInfo)
        {
        }
        
        Writer(MetaObjectInfo& metaObjInfo) : Writer(&metaObjInfo)
        {
        }
    };
}
