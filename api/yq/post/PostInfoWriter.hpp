////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Post.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq::post {
    /*! \brief Writer of event information
    */
    template <typename C>
    class PostInfo::Writer : public ObjectInfo::Writer<C> {
    public:
    
        //! Constructor of widget info (this is used by derived classes and this classes other constructor)
        Writer(PostInfo* pInfo) : ObjectInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        //! Constructor of widget info (this is used by the writer<T>() methods)
        Writer(PostInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        PostInfo* m_meta;
    };
}
