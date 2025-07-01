////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Trigger.hpp>

namespace yq::post {

    /*! \brief Inverts the acceptance
    
        Got a trigger you want the opposite of?  This is your helper.
        
        \note If this trigger is BAD (null), then this will return FALSE.
    */
    class NotTrigger : public Trigger {
        YQ_OBJECT_DECLARE(NotTrigger, Trigger)
    public:
    
        using Param = Trigger::Param;
    
        NotTrigger(const TriggerCPtr&, const Param& p = {});
        ~NotTrigger();
        bool    accept(const Post&) const;
        
        static void init_meta();
    
    private:
        TriggerCPtr m_original;
    };
}
