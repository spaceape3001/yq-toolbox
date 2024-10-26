////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Filter.hpp>
#include <concepts>

namespace yq::post {
    class Trigger;
    template <typename C>
    concept SomeTrigger = std::derived_from<C,Trigger>;

    class TriggerInfo : public FilterInfo {
    public:
        template <typename C> class Writer;

        TriggerInfo(std::string_view zName, const FilterInfo& base, const std::source_location& sl=std::source_location::current());
    };
    
    /*! \brief Triggers posts
    
        A trigger is a detector of posts, specific to it, no dispatchers considered
    */
    class Trigger : public Filter {
        YQ_OBJECT_INFO(TriggerInfo)
        YQ_OBJECT_DECLARE(Trigger, Filter)
        template <typename> friend class Ref;
    public:
    
        using Filter::Param;
        
    
        virtual bool    accept(const Post&) const = 0;
        virtual bool    accept(const Dispatcher&, const Dispatcher&, const Post&) const override final;
    
    protected:
        Trigger(const Param& p={});
        ~Trigger();
    };
}
