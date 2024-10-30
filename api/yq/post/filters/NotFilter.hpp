////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Filter.hpp>

namespace yq::post {

    /*! \brief Inverts the acceptance
    
        Got a filter you want the opposite of?  This is your helper.
        
        \note If this filter is BAD (null), then this will return FALSE.
    */
    class NotFilter : public Filter {
        YQ_OBJECT_DECLARE(NotFilter, Filter)
    public:
    
        using Param = Filter::Param;
    
        NotFilter(const FilterCPtr&, const Param& p = {});
        ~NotFilter();
        bool    accept(const Dispatcher&, const Dispatcher&, const Post&) const;
    
    private:
        FilterCPtr m_original;
    };
}
