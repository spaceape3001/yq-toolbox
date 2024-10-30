////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "NotFilter.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/FilterInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::NotFilter)

namespace yq::post {

    NotFilter::NotFilter(const FilterCPtr& inc, const Param& p) : Filter(p), m_original(inc)
    {
        assert(m_original);
    }
    
    NotFilter::~NotFilter()
    {
    }
    
    bool    NotFilter::accept(const Dispatcher&src, const Dispatcher&tgt, const Post&pp) const 
    {
        if(!m_original)   // shouldn't happen, demo...
            return false;
        return !m_original->passed(src, tgt, pp);
    }

    static void reg_not_filter()
    {
        auto w = writer<NotFilter>();
        w.description("NOT post filter (ie, negates the given filter's test)");
    }
    
    YQ_INVOKE(reg_not_filter();)
}
