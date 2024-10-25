////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Filter.hpp>

namespace yq::post {

    /*! \brief "OR" filter of multiple filters
    
        Takes in a list of filters, and creates an "or" for them.  
        
        \note No valid filters means this filter will REJECT all queries.
    */
    class OrFilter : public Filter {
        YQ_OBJECT_DECLARE(OrFilter, Filter)
    public:
    
        using Param = Filter::Param;
    
        OrFilter(std::initializer_list<FilterCPtr>, const Param& p = {});
        // Add overloads as necessary
        
        //OrFilter(std::vector<FilterCPtr>&&);
        //OrFilter(const std::vector<FilterCPtr>&);
        //OrFilter(const std::span<FilterCPtr>);
        //OrFilter(const std::span<const FilterCPtr>);

        ~OrFilter();
        bool    accept(const Dispatcher&, const Dispatcher&, const Post&) const override;
    
    private:
        std::vector<FilterCPtr> m_filters;
    };
}
