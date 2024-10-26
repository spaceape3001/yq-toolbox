////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Trigger.hpp>
#include <yq/post/FilterInfoWriter.hpp>

namespace yq::post {
    /*! \brief Writer of event information
    */
    template <typename C>
    class TriggerInfo::Writer : public FilterInfo::Writer<C> {
    public:
    
        //! Constructor of widget info (this is used by derived classes and this classes other constructor)
        Writer(TriggerInfo* pInfo) : FilterInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        //! Constructor of widget info (this is used by the writer<T>() methods)
        Writer(TriggerInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        TriggerInfo* m_meta;
    };
}
