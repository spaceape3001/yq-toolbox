////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Filter.hpp>
#include <yq/post/Post.hpp>

namespace yq::post {
    class GenericPostClassFilter : public Filter {
        YQ_OBJECT_DECLARE(GenericPostClassFilter, Filter)
    public:
    
        using Param = Filter::Param;
    
        GenericPostClassFilter(const PostInfo&, const Param& p = {});
        ~GenericPostClassFilter();
        bool    accept(const Dispatcher&, const Dispatcher&, const Post&) const override;
    
    private:
        const PostInfo&     m_postInfo;
    };
    
    template <SomePost P>
    class PostClass : public GenericPostClassFilter {
    public:
        PostClass(const Param& p = {}) : GenericPostClassFilter(meta<P>(), p) {}
    };
}
