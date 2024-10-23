////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Event.hpp>
#include <yq/post/PostInfoWriter.hpp>

namespace yq::post {
    /*! \brief Writer of event information
    */
    template <typename C>
    class EventInfo::Writer : public PostInfo::Writer<C> {
    public:
    
        //! Constructor of widget info (this is used by derived classes and this classes other constructor)
        Writer(EventInfo* eventInfo) : PostInfo::Writer<C>(eventInfo), m_meta(eventInfo)
        {
        }
        
        //! Constructor of widget info (this is used by the writer<T>() methods)
        Writer(EventInfo& eventInfo) : Writer(&eventInfo)
        {
        }

    private:
        EventInfo* m_meta;
    };
}
