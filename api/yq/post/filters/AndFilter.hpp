////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/post/Filter.hpp>

namespace yq::post {

    /*! Combines multiple filters into one logical AND
    
        Whether this class is needed is debatable... as the 
        entire filter vector chain is treated as "AND".
    */
    class AndFilter : public Filter {
        YQ_OBJECT_DECLARE(AndFilter, Filter)
    public:
    
        using Param = Filter::Param;
    
        AndFilter(std::initializer_list<FilterCPtr>, const Param& p = {});
        // Add overloads as necessary
        
        //AndFilter(std::vector<FilterCPtr>&&);
        //AndFilter(const std::vector<FilterCPtr>&);
        //AndFilter(const std::span<FilterCPtr>);
        //AndFilter(const std::span<const FilterCPtr>);

        ~AndFilter();
        bool    accept(const Dispatcher&, const Dispatcher&, const Post&) const;
        
        static void init_meta();
    
    private:
        std::vector<FilterCPtr> m_filters;
    };
}
