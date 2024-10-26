////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/forward.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/Ref.hpp>
#include <yq/core/UniqueID.hpp>

namespace yq::post {
    class FilterInfo : public ObjectInfo {
    public:
        template <typename C> class Writer;

        FilterInfo(std::string_view zName, const ObjectInfo& base, const std::source_location& sl=std::source_location::current());
    };
    
    /*! \brief Filters posts
    
        Given the inputs of dispatchers, a filter can be more discerning than triggers.
    */
    class Filter : public Object, public RefCount, public UniqueID {
        YQ_OBJECT_INFO(FilterInfo)
        YQ_OBJECT_DECLARE(Filter, Object)
        template <typename> friend class Ref;
    public:
    
        using post_type = Post;

        static void init_info();
    
        struct Param {
            std::string_view    name;
        };

        //! Gets the name (or, if empty, the filter class name)
        std::string_view    name() const;
        
        virtual bool    accept(const Dispatcher&, const Dispatcher&, const Post&) const = 0;
    
    protected:
        Filter(const Param& p={});
        ~Filter();
        
        //! Sets the name
        void            name(std::string_view);
        
    private:
        std::string_view    m_name;
    
        //! Getter for the name property
        std::string         name_get() const;
        //! Setter for the name property
        void                name_set(const std::string&);
    };
}
