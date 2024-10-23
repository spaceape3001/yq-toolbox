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
        Writer(PostInfo* postInfo) : ObjectInfo::Writer<C>(postInfo), m_meta(postInfo)
        {
        }
        
        //! Constructor of widget info (this is used by the writer<T>() methods)
        Writer(PostInfo& postInfo) : Writer(&postInfo)
        {
        }

    private:
        PostInfo* m_meta;
    };
}
