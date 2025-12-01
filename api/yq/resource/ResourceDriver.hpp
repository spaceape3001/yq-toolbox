////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/Resource.hpp>
#include <yq/core/ErrorDB.hpp>
#include <yq/typedef/string_vectors.hpp>

namespace yq {

    /*! \brief Root class to all resource drivers.
    
        This is the root to all drivers.  Normally, most users won't interface
        directly with this class, they'll leverage the auto-creation via the
        add loader/infoer/saver routines.
    */
    class ResourceDriver {
        friend class Resource;
    public:
    
        //! Shortcut to help to know the basic "type" of the driver, whether it's
        //! taking URLs vs files vs whatever
        enum class Type : uint8_t {
            none    = 0,
            url,
            file,
            byte,
            stream,
            string,
            xml,
            json,
            kvdoc,
            kvtree
        };
        
        //! Type of the driver
        Type                type() const { return m_type; }
        
        //! Resource the driver loads
        const ResourceMeta&    resource() const { return m_resource; }

        //! File extensions that are valid for this driver
        constexpr const string_vector_t& extensions() const { return m_extensions; }
        
        //! Code location to where the driver was registered.
        constexpr const std::source_location& location() const { return m_location; }
        
    protected:
        ResourceDriver(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type);
        virtual ~ResourceDriver();
        
    private:
        const ResourceMeta&     m_resource;
        string_vector_t         m_extensions;
        std::source_location    m_location;
        Type                    m_type;
    };

    /*! \brief Base class for all info extraction drivers.  Normally end users will
        using the method registrations
    */
    class ResourceInfoer : public ResourceDriver {
    public:

        //! Query for resource information from the given url
        virtual ResourceInfoPtr info(const UrlView&, const ResourceInfoAPI&) const = 0;

    protected:
        friend class Resource;
        
        ResourceInfoer(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type);
        virtual ~ResourceInfoer();
    };
    
    /*! \brief Base class for all resouce loading drivers.  Normally end users will
        be using the method registrations & the loading API helpers (ie, MyResource::IO::load()).
    */
    class ResourceLoader : public ResourceDriver {
    public:

        //! Load the specified resource
        virtual ResourcePtr load(const UrlView&, const ResourceLoadAPI&) const = 0;

    protected:
        friend class Resource;

        ResourceLoader(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type);
        virtual ~ResourceLoader();
    };

    /*! \brief Base class for all resource saving drivers.  Normally end users will
        be using the method registrations & the saving API helpers (ie, MyResource::IO::save()).
    */
    class ResourceSaver : public ResourceDriver {
    public:
    
        //! Save the specific resource to the specific file
        virtual std::error_code  save(const Resource&, const UrlView&, const ResourceSaveAPI&) const = 0;
        
    protected:
        friend class Resource;

        ResourceSaver(const ResourceMeta&, const string_vector_t& exts, const std::source_location&, Type);
        virtual ~ResourceSaver();
    };
    
    namespace errors {
        using resource_saving_failed   = error_db::entry<"Unable to save resource">;
    }
}
