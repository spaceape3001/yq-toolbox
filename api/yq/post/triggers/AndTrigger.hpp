////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Trigger.hpp>

namespace yq::post {

    /*! Combines multiple filters into one logical AND
    
        Whether this class is needed is debatable... as the 
        entire filter vector chain is treated as "AND".
    */
    class AndTrigger : public Trigger {
        YQ_OBJECT_DECLARE(AndTrigger, Trigger)
    public:
    
        using Param = Trigger::Param;
    
        AndTrigger(std::initializer_list<TriggerCPtr>, const Param& p = {});
        // Add overloads as necessary
        
        //AndTrigger(std::vector<TriggerCPtr>&&);
        //AndTrigger(const std::vector<TriggerCPtr>&);
        //AndTrigger(const std::span<TriggerCPtr>);
        //AndTrigger(const std::span<const TriggerCPtr>);

        ~AndTrigger();
        bool    accept(const Post&) const override;
    
    private:
        std::vector<TriggerCPtr> m_triggers;
    };
}
