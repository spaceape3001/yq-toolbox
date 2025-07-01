////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AndFilter.hpp"
#include <yq/post/FilterInfoWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::AndFilter)

namespace yq::post {
    AndFilter::AndFilter(std::initializer_list<FilterCPtr> filters, const Param&p) : Filter(p), m_filters(filters.begin(), filters.end())
    {
    }
    
    AndFilter::~AndFilter()
    {
    }

    bool    AndFilter::accept(const Dispatcher&src, const Dispatcher&tgt, const Post& pp) const 
    {
        for(const FilterCPtr& f : m_filters){
            if(f && !f->passed(src, tgt, pp))
                return false;
        }
        return true;
    }
    
    void AndFilter::init_meta()
    {
        auto w = writer<AndFilter>();
        w.description("An AND post filter based on other filters");
    }
}
