////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PostClassFilter.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/FilterInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::GenericPostClassFilter)

namespace yq::post {
    GenericPostClassFilter::GenericPostClassFilter(const PostInfo& info, const Param& p) : Filter(p), m_postInfo(info)
    {
    }
    
    GenericPostClassFilter::~GenericPostClassFilter()
    {
    }
    
    bool    GenericPostClassFilter::accept(const Dispatcher&, const Dispatcher&, const Post&p) const 
    {
        return m_postInfo.is_derived(p.metaInfo());
    }

    static void reg_generic_post_filter()
    {
        auto w = writer<GenericPostClassFilter>();
        w.description("Filter based on the post type");
    }
    
    YQ_INVOKE(reg_generic_post_filter();)
}
