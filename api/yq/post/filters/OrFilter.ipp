////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OrFilter.hpp"
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
            if(f && f->passed(src, tgt, pp))
                return true;
        }
        return false;
    }
    
    void OrFilter::init_info()
    {
        auto w = writer<OrFilter>();
        w.description("An OR post filter based on other filters");
    }
}
