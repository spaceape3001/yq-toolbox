////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OrFilter.hpp"
#include <yq/core/DelayInit.hpp>
#include <yq/post/FilterInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::OrFilter)

namespace yq::post {
    OrFilter::OrFilter(std::initializer_list<FilterCPtr> filters, const Param&p) : Filter(p), m_filters(filters.begin(), filters.end())
    {
    }
    
    OrFilter::~OrFilter()
    {
    }

    bool    OrFilter::accept(const Dispatcher&src, const Dispatcher&tgt, const Post& pp) const 
    {
        for(const FilterCPtr& f : m_filters){
            if(f && f->accept(src, tgt, pp))
                return true;
        }
        return false;
    }
    
    static void reg_or_filter()
    {
        auto w = writer<OrFilter>();
        w.description("An OR post filter based on other filters");
    }
    
    YQ_INVOKE(reg_or_filter();)
}
