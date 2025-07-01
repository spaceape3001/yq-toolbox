////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#error "Obsolete, do not include"

/*
    This (the post library) is being removed SOON, however, 
    it's kept around as reference
*/


#include <yq/post/forward.hpp>
#include <yq/core/Flags.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/Ref.hpp>
#include <yq/core/UniqueID.hpp>
#include <variant>

namespace yq::post {
    //! Flags to encapsulate how the filter mismatches
    using FilterResult      = std::variant<bool,MismatchFlags>;
    
    class FilterMeta : public ObjectMeta {
    public:
        template <typename C> class Writer;
        
        FilterMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());
        
        //! \note This can be NULL (and valid as such)
        const ObjectMeta*   sender_info() const { return m_sender; }

        //! \note This can be NULL (and valid as such)
        const ObjectMeta*   receiver_info() const { return m_receiver; }
        
        //! \note NULL means it's generic post, not refined
        const PostInfo*     post_info() const { return m_postInfo; }
        
    protected:
        const ObjectMeta*   m_sender        = nullptr;
        const ObjectMeta*   m_receiver      = nullptr;
        const PostInfo*     m_postInfo      = nullptr;

        friend class Filter;
        virtual FilterResult      accept(const Filter&, const Dispatcher&, const Dispatcher&, const Post&) const = 0;
    };
    
    /*! \brief Filters posts
    
        Given the inputs of dispatchers, a filter can be more discerning than triggers.
    */
    class Filter : public Object, public RefCount, public UniqueID {
    public:
        template <typename> class Fixer;

    private:
        YQ_OBJECT_META(FilterMeta)
        YQ_OBJECT_FIXER(Fixer)
        YQ_OBJECT_DECLARE(Filter, Object)
        template <typename> friend class Ref;
    public:
    
        using post_type = Post;

        static void init_meta();
    
        using MismatchConfig = std::variant<std::monostate, bool, MismatchPolicy, MismatchFlags>;
    
        struct Param {
            std::string_view    name;
            
            //! Tolerable mismatches
            //! 
            //! A tolerable mismatch turns rejection into acceptance.  
            //! If there is a mismatch, the filter's acceptance will *NOT* be called.
            
            MismatchConfig      mismatches;
        };
        
        /*! \fn bool accept(const Dispatcher&src, const Dispatcher&tgt, const Post&pp) const;
        
            \brief This is your acceptance function, define it, implement it
            \param[in] src  Reference to the "sending" dispatcher
            \param[in] tgt  Reference to the "receiving" dispatcher
            \param[in] pp   The post
            \return TRUE to accept the match (FALSE rejects)
        */
        
        //! Gets the name (or, if empty, the filter class name)
        std::string_view    name() const;
         
        //! Gets the mismatch flags
        MismatchFlags   mismatch() const { return m_mismatch; }
        
        //!     Calls the accept (filter) function, accounts for mismatch
        bool            passed(const Dispatcher&, const Dispatcher&, const Post&) const;
        
        //!     Calls the accept (filter) function, returns the result
        FilterResult    check(const Dispatcher&, const Dispatcher&, const Post&) const;
    
    protected:
        Filter(const Param& p={});
        ~Filter();
        
        //! Sets the name
        void            name(std::string_view);
        
        
    private:    
        friend class Trigger;
        
        std::string_view    m_name;
        
        //! Permissible mismatch
        MismatchFlags       m_mismatch  = {};
    
        //! Getter for the name property
        std::string         name_get() const;
        //! Setter for the name property
        void                name_set(const std::string&);
    };
}
