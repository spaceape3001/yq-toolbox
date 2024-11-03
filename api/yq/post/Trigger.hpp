////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Filter.hpp>
#include <concepts>

namespace yq::post {
    class TriggerInfo : public FilterInfo {
    public:
        template <typename C> class Writer;

        TriggerInfo(std::string_view zName, FilterInfo& base, const std::source_location& sl=std::source_location::current());
    
    protected:
        friend class Trigger;
        using FilterInfo::accept;
        virtual FilterResult accept(const Trigger&, const Post&) const = 0;
    };
    
    /*! \brief Triggers posts
    
        A trigger is a detector of posts, specific to it, no dispatchers considered
    */
    class Trigger : public Filter {
    public:
        template <typename> class Fixer;
    private:
        YQ_OBJECT_INFO(TriggerInfo)
        YQ_OBJECT_FIXER(Fixer)
        YQ_OBJECT_DECLARE(Trigger, Filter)
        template <typename> friend class Ref;
    public:
    
        friend class PBX;
        using Filter::Param;
        
        /*! \fn bool accept(const Post&pp) const;
        
            \brief This is your acceptance function, define it, implement it
            \param[in] src  Reference to the "sending" dispatcher
            \param[in] tgt  Reference to the "receiving" dispatcher
            \param[in] pp   The post
            \return TRUE to accept the match (FALSE rejects)
        */
    
        //!     Calls the accept (filter) function
        bool            passed(const Post&) const;
        FilterResult    check(const Post&) const;
        
        MismatchPolicy  mismatch() const;
        
        static void init_info();

    protected:
        Trigger(const Param& p={});
        ~Trigger();
    };
}
