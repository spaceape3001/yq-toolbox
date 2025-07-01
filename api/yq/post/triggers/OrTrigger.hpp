////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Trigger.hpp>

namespace yq::post {

    /*! \brief "OR" trigger of multiple triggers
    
        Takes in a list of triggers, and creates an "or" for them.  
        
        \note No valid triggers means this trigger will REJECT all queries.
    */
    class OrTrigger : public Trigger {
        YQ_OBJECT_DECLARE(OrTrigger, Trigger)
    public:
    
        using Param = Trigger::Param;
    
        OrTrigger(std::initializer_list<TriggerCPtr>, const Param& p = {});
        // Add overloads as necessary
        
        //OrTrigger(std::vector<TriggerCPtr>&&);
        //OrTrigger(const std::vector<TriggerCPtr>&);
        //OrTrigger(const std::span<TriggerCPtr>);
        //OrTrigger(const std::span<const TriggerCPtr>);

        ~OrTrigger();
        bool    accept(const Post&) const;
    
        static void init_meta();

    private:
        std::vector<TriggerCPtr> m_triggers;
    };
}
